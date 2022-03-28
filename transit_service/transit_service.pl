use strict;
use warnings;

my $wallet_name = "";    #钱包名称
my $pwd_file = "";       #钱包密码文件名称
my $bridge_account = ""; #中转账号

my $pos =  $ARGV[0];     #启动值要选择最近已经确认的区块中没有注册完成的编号。
my $offset = $ARGV[1];   #填1 返回一条记录。

#$pos++;

while()
{
my $gmt_datestring = gmtime();
print "\nGMT TIME IS：$gmt_datestring\n";

my @get_actions  = `cleos get actions $bridge_account $pos $offset --full --console 2>&1`;

#print @get_actions;
print "get the pos NUM: $pos \n";
print "**********\n";
print $get_actions[0];
print $get_actions[1];
print "**********\n";

 if( $get_actions[0] =~ /\?\D+(\d+).+eosio\.token::transfer/ )  #如果碰到是正在打包等待完全确认的。
 {
    print "$pos unconfirmed\n";
    sleep (10);
    redo;
 }
 elsif($get_actions[0] =~ /#\D+(\d+).+eosio\.token::transfer/)  #如果碰到的是已经确认的。
 { 
      print "Enter the registration process\n"; #进入注册流程
      if($get_actions[1]=~ /"from":"(.+)","to":"(.+)","quantity":"(.+)\s+EOS","memo":"(.*)"/)  #匹配转入金额和备注
      {
        if ($1 eq $bridge_account) #如果是自己账户转出的，跳过，编号+1；
        {
         print "NUM: $pos skip your own account transfer out\n";
         sleep (5);
         $pos++;
         redo;
        }
        elsif($3 >= 0.1) # 如果转入金额不够，无法注册。
        {
     	print "enough to create account\n";
    	print "reicive : $3 ,memo : $4 \n";
        
        my $send = $3 - 0.04 ;   #转到账号注册合约的金额 
        my $memo = process_memo($4); #处理memo

     	print "send $send \n";
	    print "memo after processed : $memo\n";
	    `cat $pwd_file |cleos wallet unlock -n $wallet_name`;
         while()
         {
    	  my @reg_back = `cleos transfer $bridge_account accountspapa "$send EOS" "$memo" -x 180  2>&1`;  #注册
          if ($reg_back[0] =~ /Error\s+3080004|3080002|3081001/ ) #cpu或者net资源不足错误,或者deadline
          {
            print "reg back first line : $reg_back[0] \n";
            print "power up the $bridge_account\n";
            my @powerup_back =`cleos push action eosio powerup '["$bridge_account","$bridge_account","1","111460","535717152","0.0100 EOS"]' -p $bridge_account\@active 2>&1`;
            print "power up result: \n";
            print @powerup_back;
	    sleep(10);
          }
          elsif($reg_back[0] =~ /Error\s+3080006/ ) #  Transaction took too long
          {
            print "reg back: \n";
            print @reg_back;
            sleep(10);
          }
          elsif($reg_back[0] =~ /Error\s+3050001/) #账号已经被注册，则使用随机号注册,如果随机账号也被注册，不会跳出循环，会继续尝试生成新的，直到注册成功。
          {
           print "The account has been registered by someone else, and a random account will be used\n";
           my $random_account = random_account_generation();
           $memo =~ s/^.{12}/$random_account/ ;
           print "random : $memo \n";
           sleep(10);
          }
	  elsif($reg_back[0] =~ /Error/ ) #  其他错误，重新尝试注册
          {
            print "reg back: \n";
            print @reg_back;
            sleep(10);
          }
          else
          {
             print "reg back: \n";
             print @reg_back;
             last;
          }
         }
       }
       else
       {
         print "NUM: $pos didn't send enough EOS to create a account\n";
       }
      }
      else
      {
       print "NUM: $pos unknow text 1 regular match failed\n";
      }
      sleep (5);
      $pos++;   
 }
 elsif($get_actions[0] =~ /seq\s+when/) #如果编号不存在,保持现有编号继续循环。
 {
   print "num not exist\n";
   sleep (60);
   redo;
 }
 else
 {
     print "NUM: $pos unknow text 0 regular match failed\n";
     print @get_actions;
     sleep (60);
 }

}

#处理memo
sub process_memo
{
  my $memo_return;
  my $r_account;
  if ($_[0] =~ /^\s*(\w+)-(EOS\w+)\s*/) #标准模式 账号名-EOS前缀公钥
  { 
    print "moudle 1\n";
    my $temp_string = $1;
    $temp_string =~ tr/A-Z/a-z/;
    # print length($temp_string);
    if (length($temp_string) != 12)
    {
    $temp_string = random_account_generation();
    }
    elsif($temp_string =~/0|6|7|8|9/)
    {
    $temp_string = random_account_generation();
    }
    return "$temp_string-$2"; #返回去掉前后空格 
  }
  elsif ($_[0] =~ /^\s*(EOS.+)\s*/) # EOS前缀公钥
  {
    print "moudle 2\n";
    $r_account = random_account_generation();
    $memo_return = "$r_account-$1"; 
    return $memo_return;
  }
  elsif($_[0] =~ /^\s*(\w+)-(\w+)\s*/) #  账号名-无EOS前缀公钥
  {
   print "moudle 3\n";
    my $temp_string = $1;
    my $temp_pubkey = $2;
    $temp_string =~ tr/A-Z/a-z/;
    # print length($temp_string);
    if (length($temp_string) != 12)
    {       
    $temp_string = random_account_generation();
    }
    elsif($temp_string =~/0|6|7|8|9/)
    {
    $temp_string = random_account_generation();
    }

   $memo_return = "$temp_string-EOS$temp_pubkey";

   return $memo_return; 
  }
  elsif($_[0] !~ /^\s*EOS/ and $_[0] =~ /^\s*(\w{50})\s*$/) # 无前缀公钥
  {
   print "moudle 4\n";
   $r_account = random_account_generation();
   my $pub_key = $1;
   # $pub_key =~ s/^\s+|\s+$//g; #去除前后空格
   $memo_return = "$r_account-EOS$pub_key";
   return $memo_return;
  }
  else
  {
    print "no moudles match\n"; #以上4个模式都不匹配
    return $_[0];
  }
}

#生成随机账号
sub random_account_generation   
{
 my @char_array = ('a'..'z',1..5);
 my $r_account = join '', map{ $char_array[int rand @char_array] } 0..11;
 return $r_account;
}

