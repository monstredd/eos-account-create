# eos-account-create

EN:

Modified from the signupeoseos open source codes;

https://github.com/DeBankDeFi/signupeoseos

Delete the pledge cpu and net;

support eoscdt 1.8 version compilation;

The cheapest way to register an eos account.Except for the system fee, there are no additional costs;

set only 0.06 eos register an eos account.(but depends on ram price,0.06 eos is enough now);

set the code on an eos account,send more than 0.06 EOS to the account with memo [AccountName]-[PublicKey] account will be automatically registered.The excess amount will appear in your newly registered account;

contract on EOS main net https://bloks.io/account/accountspapa

send  0.06 EOS to the account accountspapa with memo [12 letters AccountName]-[PublicKey] account will be automatically registered.

wrong Publickey，wrong AccountName and AccountName already exists, transfer will be failed.

Users who successfully register using this method will receive an airdrop of NPP (names papa) tokens.

You need to claim the tokens yourself, and those who can't get it for a long time will be cleared.

https://bloks.io/account/eosnamespapa?tab=Actions&account=eosnamespapa

Use the newly registered account login and click CLAIM

Fill in the name of the account that will receive the airdrop in the first box, that is, the newly registered account.

Fill the second with  "4, NPP"

There are a total of 21 million NPPs, and each new account can receive 100 airdrops. When the circulation reaches 10 million, the number of airdrops will begin to decrease linearly.

###############################################################################

Because most cryptocurrency exchanges and centralized wallets prohibit withdrawing EOS to smart contract accounts, the registration service cannot be used, so a transfer service has been established.

That is, the exchange withdraws the currency to the transfer account of the non-smart contract, and the transfer account sends the demand to the registration contract.

Transfer account address: https://bloks.io/account/accountsmama

Send 0.1 EOS to the account accountsmama. Note that the memo account will be automatically registered in the following 4 formats (less than 0.1eos, greater than 10eos, remarks that do not follow the format are wrong, the public key and account number of the remarks do not meet the rules, which will cause registration failure and funds Inconvenient to retrieve it, it is recommended to use only 0.1EOS)

(Transit services need to maintain nodes, and accounts need to consume main network resources, so they are slightly more expensive than smart contract registration)

Because some exchanges and centralized wallets have restrictions on transfer memo, the transfer service is compatible with 4 formats of remarks.

Format 1: [12-letter account number]-[public key starting with EOS]

Format 2: [Public key at the beginning of EOS]

Format 3: [12-letter account number]-[public key without EOS begin]

Format 4: [public key without EOS begin]

#public key without 'EOS' begin, that is, the remaining string after deleting the 'EOS' at the beginning of the EOS public key

If there are remarks in the above 4 formats that are prohibited by the exchange, please contact me and I will open up a new method.

Formats 1 and 3 If the account name already exists, it will be automatically registered as a random name account. If it does not exist, it will be registered as required.

Formats 2 and 4 are automatically registered as random name accounts.

EOS public key and private key pair should be generated using the built-in generators of major brand wallets, or generated by a community-approved generation method. Do not trust phishing websites. Smart contract direct registration and transit registration will use the public key you provide to register and will not touch your private key. If the private key is accidentally leaked, please change your public key and private key pair in time. It is strongly recommended to use the public key of the hardware wallet for registration.

Transfer registration is a centralized method. Generally, the registration will be successful after the block is fully confirmed (the block is irreversible). If the public key is provided incorrectly, the account cannot be retrieved.

The transfer service is not decentralized, and it is inevitable that there will be a small probability that the node will crash, and the network will be damaged. If you have any questions, please contact me in time https://t.me/eosmonstre

Because of the relevance of eos account registration and generation, the use of exchange withdrawal registration can break the relevance of the account to achieve the purpose of protecting privacy.

Breaking the account’s relevance does not mean it's an anonymous account, but only protects your privacy to a certain extent. (You can be found by tracing the source of registered capital).

The anonymous registration function is under development...


CN：

从signupeoseos开源代码修改而来；

https://github.com/DeBankDeFi/signupeoseo

删除质押的cpu和net；

支持eoscdt 1.8版本编译；

注册eos账户最便宜的方式，除了EOS系统收取的费用，没有额外费用，无盈利目的；

设置为仅使用 0.06 eos 注册一个 eos 帐户。（但取决于 ram 价格，现在 0.06 eos 就足够了）；

在eos账户上设置合约，发送超过0.06 EOS到备注的账户[AccountName]-[PublicKey]账户将自动注册。超出的金额将出现在您新注册的账户中；

EOS主网上合约 https://bloks.io/account/accountspapa

发送 0.06 EOS 到账户 accountspapa 按以下格式备注memo [12位用户名]-[公钥] 账户将被自动注册。

如果发送的金额超过0.06 EOS，多余的金额会出现在你新注册的账号里，为了防止弄丢私钥等操作失误的损失，超过10EOS的转账将不会成功。

不符合规则的公钥和账号名，以及账户名已经存在，转账将失败。

成功使用此方法注册的用户，将得到NPP（names papa） 通证的空投。

需要自行去代币合约领取，长期不领取的将被清除。

https://bloks.io/account/eosnamespapa?tab=Actions&account=eosnamespapa

使用新注册的号登陆，点击claim

第一个框填入  接收空投的账号名，也就是新注册的账号。

第二个填入    4,NPP

NPP总共2100万枚，每个新账户可以领100枚空投，当发行量达到1000万枚时候，空投数量将开始线性减少。

###############################################################################

因为大部分加密货币交易所和中心化钱包禁止向智能合约账户提币，导致注册服务无法使用，所以建立了中转服务。

即交易所提币到非智能合约的中转账户，中转账户再将需求发送到注册合约。

中转账户地址 ： https://bloks.io/account/accountsmama

发送 0.1 EOS 到账户 accountsmama 按以下4种格式备注memo账户将被自动注册（小于0.1eos，大于10eos，不按格式的备注错误，备注的公钥和账号不符合规则，会导致注册失败，和资金不便找回，建议只使用0.1EOS）

（中转服务需要维持节点，账号需要消耗主网资源，所以比智能合约注册略贵）

因为一些交易所和中心化钱包对于转账memo的限制，中转服务兼容4种格式的备注。

格式1： [12位字母账号]-[EOS开头的公钥] 

格式2： [EOS开头的公钥]

格式3： [12位字母账号]-[无EOS开头公钥]           

格式4： [无EOS开头公钥]                      

#无EOS开头公钥，即将EOS公钥开头的EOS删除以后剩下的字符串

如果有交易所禁止以上4种格式的备注，请与我联系，我将再开辟新的办法。

格式 1和3  如果账号名已经存在 则自动注册为随机名字账号，不存在，则按需求注册。

格式 2和4  自动注册为随机名字账号。

EOS公钥，私钥对请使用各大品牌钱包内置生成器生成，或者社区认可的生成方式生成，切勿相信钓鱼网站。 智能合约直接注册和中转注册，将使用你提供的公钥注册，不会碰触你的私钥。如果私钥不慎泄露，请及时更换您的公钥和私钥对。强烈推荐使用硬件钱包的公钥进行注册。

中转注册为中心化的方式，一般情况下，在区块完全确认（区块不可逆）以后就会注册成功，如果公钥提供错误，将无法找回账户。

中转服务不是去中心化的，不可避免有小概率，节点当机，网络损坏导致无法注册的问题。如果有问题，请及时和我联系 https://t.me/eosmonstre

因为eos账号注册和生成的关联性，使用交易所提币注册可以破除账号的关联性，以到达保护隐私的目的。

破除关联的账号并不等于匿名账号，只是在一定限度上保护你的隐私。（可以追溯注册资金来源而找到你）。

匿名注册功能正在开发中...

