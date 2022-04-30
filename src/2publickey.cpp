#include <signupeoseos.hpp>

namespace eosio {

void signupeoseos::transfer(name from, name to, asset quantity, string memo) {
    if (from == get_self() || to != get_self()) {
        return;
    }
    
    check(quantity.is_valid(), "Invalid token transfer");
    check(quantity.amount > 0, "Quantity must be positive");
   // check(quantity.amount <= 100000, "In order to avoid asset loss caused by using wrong public key, the maximum amount is 10 eos");
    
    asset buy_ram = asset(600, symbol("EOS", 4));
    asset buy_ram_1 = asset(550, symbol("EOS", 4));
    asset buy_ram_2 = asset(50, symbol("EOS", 4));
 
    check(quantity >= buy_ram, "Not enough balance to buy ram");

    memo.erase(memo.begin(), find_if(memo.begin(), memo.end(), [](int ch) {
        return !isspace(ch);
    }));
    memo.erase(find_if(memo.rbegin(), memo.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), memo.end());

    auto separator_pos_owner = memo.find(' ');
    if (separator_pos_owner == string::npos) {
        separator_pos_owner = memo.find('-');
    }
    check(separator_pos_owner != string::npos, "Account name and other command must be separated with space or minuses");

    auto separator_pos_active = memo.find(' ',separator_pos_owner+1);
    if (separator_pos_active == string::npos) {
        separator_pos_active = memo.find('-',separator_pos_owner+1);
    }
    //check(separator_pos_active != string::npos, "Account name and other command must be separated with space or minuses");
    
    //check account name if 12 char
    string account_name_str = memo.substr(0, separator_pos_owner);
    check(account_name_str.length() == 12, "Length of account name should be 12");
    name new_account_name = name(account_name_str.c_str());


     //check owner public key
    string owner_public_key_str = memo.substr(separator_pos_owner + 1,separator_pos_active - 13);
    check(owner_public_key_str.length() == 53, "Length of owner publik key should be 53");

    string pubkey_prefix("EOS");
    
    auto owner_result = mismatch(pubkey_prefix.begin(), pubkey_prefix.end(), owner_public_key_str.begin());
    check(owner_result.first == pubkey_prefix.end(), "Owner public key should be prefix with EOS");
    auto o_base58substr = owner_public_key_str.substr(pubkey_prefix.length());

    vector<unsigned char> o_vch;
    check(decode_base58(o_base58substr, o_vch), "Decode owner pubkey failed");
    check(o_vch.size() == 37, "Invalid owner public key");

    array<unsigned char,33> owner_pubkey_data;
    copy_n(o_vch.begin(), 33, owner_pubkey_data.begin());

    capi_checksum160 check_owner_pubkey;
    ripemd160(reinterpret_cast<char *>(owner_pubkey_data.data()), 33, &check_owner_pubkey);
    check(memcmp(&check_owner_pubkey.hash, &o_vch.end()[-4], 4) == 0, "invalid owner public key");

    signup_public_key owner_pubkey = {
        .type = 0,
        .data = owner_pubkey_data,
    };

    key_weight owner_pubkey_weight = {
        .key = owner_pubkey,
        .weight = 1,
    };

    signup_public_key active_pubkey = {
        .type = 0,
        .data = owner_pubkey_data,
    };

    key_weight active_pubkey_weight = {
        .key = active_pubkey,
        .weight = 1,
    };

    if(separator_pos_active != string::npos)
    {
    //check active public_key
    string active_public_key_str = memo.substr(separator_pos_active + 1);
    check(active_public_key_str.length() == 53, "Length of active publik key should be 53");
    
    auto active_result = mismatch(pubkey_prefix.begin(), pubkey_prefix.end(), active_public_key_str.begin());
    check(active_result.first == pubkey_prefix.end(), "Active public key should be prefix with EOS");
    auto a_base58substr = active_public_key_str.substr(pubkey_prefix.length());

    vector<unsigned char> a_vch;
    check(decode_base58(a_base58substr, a_vch), "Decode active pubkey failed");
    check(a_vch.size() == 37, "Invalid active public key");

    array<unsigned char,33> active_pubkey_data;
    copy_n(a_vch.begin(), 33, active_pubkey_data.begin());

    capi_checksum160 check_active_pubkey;
    ripemd160(reinterpret_cast<char *>(active_pubkey_data.data()), 33, &check_active_pubkey);
    check(memcmp(&check_active_pubkey.hash, &a_vch.end()[-4], 4) == 0, "invalid active public key");

       active_pubkey = {
        .type = 0,
        .data = active_pubkey_data,
       };

       active_pubkey_weight = {
        .key = active_pubkey,
        .weight = 1,
       };
    }


    authority owner = authority{
        .threshold = 1,
        .keys = {owner_pubkey_weight},
        .accounts = {},
        .waits = {}
    };

    authority active = authority{
        .threshold = 1,
        .keys = {active_pubkey_weight},
        .accounts = {},
        .waits = {}
    };

    newaccount new_account = newaccount{
        .creator = get_self(),
        .name = new_account_name,
        .owner = owner,
        .active = active
    };

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
            std::make_tuple(get_self(), new_account_name, buy_ram_1)
    }.send();
    
    action{
            permission_level{ get_self(), "active"_n },
            "eosio"_n,
            "buyram"_n,
            std::make_tuple(get_self(), "eosnamespapa"_n, buy_ram_2)
    }.send();

    
    if (quantity > buy_ram)
    {
    auto spare = quantity - buy_ram ;
    action{
          permission_level{ get_self(), "active"_n },
          "eosio.token"_n,
          "transfer"_n,
          std::make_tuple(get_self(), new_account_name, spare ,std::string("eos will be $1077"))
     }.send();
     }

   // action{
     //      permission_level{ get_self(), "active"_n },
     //       "eosnamespapa"_n,
    //        "list"_n,
    //        std::make_tuple(from,new_account_name)
            //std::make_tuple(from)
   // }.send(); 
}

}
