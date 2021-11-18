#include <signupeoseos.hpp>


namespace eosio {

void signupeoseos::transfer(name from, name to, asset quantity, string memo) {
    if (from == get_self() || to != get_self()) {
        return;
    }
    
    check(quantity.is_valid(), "Invalid token transfer");
    check(quantity.amount > 0, "Quantity must be positive");
    check(quantity.amount <= 300000, "In order to avoid asset loss caused by using wrong public key, the maximum amount is 30 eos");

    memo.erase(memo.begin(), find_if(memo.begin(), memo.end(), [](int ch) {
        return !isspace(ch);
    }));
    memo.erase(find_if(memo.rbegin(), memo.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), memo.end());

    auto separator_pos = memo.find(' ');
    if (separator_pos == string::npos) {
        separator_pos = memo.find('-');
    }
    check(separator_pos != string::npos, "Account name and other command must be separated with space or minuses");

    string account_name_str = memo.substr(0, separator_pos);
    check(account_name_str.length() == 12, "Length of account name should be 12");
    name new_account_name = name(account_name_str.c_str());

    string public_key_str = memo.substr(separator_pos + 1);
    check(public_key_str.length() == 53, "Length of publik key should be 53");

    string pubkey_prefix("EOS");
    auto result = mismatch(pubkey_prefix.begin(), pubkey_prefix.end(), public_key_str.begin());
    check(result.first == pubkey_prefix.end(), "Public key should be prefix with EOS");
    auto base58substr = public_key_str.substr(pubkey_prefix.length());

    vector<unsigned char> vch;
    check(decode_base58(base58substr, vch), "Decode pubkey failed");
    check(vch.size() == 37, "Invalid public key");

    array<unsigned char,33> pubkey_data;
    copy_n(vch.begin(), 33, pubkey_data.begin());

    capi_checksum160 check_pubkey;
    ripemd160(reinterpret_cast<char *>(pubkey_data.data()), 33, &check_pubkey);
    check(memcmp(&check_pubkey.hash, &vch.end()[-4], 4) == 0, "invalid public key");

    asset buy_ram = asset(600, symbol("EOS", 4));
    check(quantity > buy_ram, "Not enough balance to buy ram");

    signup_public_key pubkey = {
        .type = 0,
        .data = pubkey_data,
    };

    key_weight pubkey_weight = {
        .key = pubkey,
        .weight = 1,
    };

    authority owner = authority{
        .threshold = 1,
        .keys = {pubkey_weight},
        .accounts = {},
        .waits = {}
    };

    authority active = authority{
        .threshold = 1,
        .keys = {pubkey_weight},
        .accounts = {},
        .waits = {}
    };

    newaccount new_account = newaccount{
        .creator = get_self(),
        .name = new_account_name,
        .owner = owner,
        .active = active
    };

print  (new_account.name,"\n");

  action{
            permission_level{ get_self(), "active"_n },
            "eosio"_n,
            "newaccount"_n,
            new_account
    }.send();

    action{
            permission_level{ get_self(), "active"_n },
            "eosio"_n,
            "buyram"_n,
            std::make_tuple(get_self(), new_account_name, buy_ram)
    }.send();

    auto spare = quantity - buy_ram ;
    action{
          permission_level{ get_self(), "active"_n },
          "eosio.token"_n,
          "transfer"_n,
          std::make_tuple(get_self(), new_account_name, spare ,std::string(""))
     }.send();
}

}