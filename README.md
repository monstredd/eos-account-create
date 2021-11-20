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

send  0.06 EOS to the account accountspapa with memo [AccountName]-[PublicKey] account will be automatically registered.

wrong Publickey，wrong AccountName and AccountName already exists, transfer will be failed.

CN：

从signupeoseos开源代码修改而来；

https://github.com/DeBankDeFi/signupeoseo

删除质押的cpu和net；

支持eoscdt 1.8版本编译；

注册eos账户最便宜的方式，除了EOS系统收取的费用，没有额外费用，无盈利目的；

设置为仅使用 0.06 eos 注册一个 eos 帐户。（但取决于 ram 价格，现在 0.06 eos 就足够了）；

在eos账户上设置合约，发送超过0.06 EOS到备注的账户[AccountName]-[PublicKey]账户将自动注册。超出的金额将出现在您新注册的账户中；

EOS主网上合约 https://bloks.io/account/accountspapa

发送 0.06 EOS 到账户 accountpapa 按以下格式备注 [用户名]-[公钥] 账户将被自动注册。

如果发送的金额超过0.06 EOS，多余的金额会出现在你新注册的账号里，为了防止弄丢私钥等操作失误的损失，超过10EOS的转账将不会成功。

不符合规则的公钥和账号名，以及账户名已经存在，转账将失败。
