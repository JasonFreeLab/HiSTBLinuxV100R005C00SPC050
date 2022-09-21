
说明
1.本工具是CASignTool.exe签名工具的linux版本
2.本工具使用cfg文本导入配置信息(文件名可更改)
3.目前工具不支持各种路径中存在空格
4.使用方式如下：

  1>./CASignTool 0 ../cfg/Signboot_config.cfg
  仅签名Key区：
  如果三个Key文件路径，仅填写了Root_private_key_file和External_public_key_file或者Root_private_key_file和BootFile的二者之一，工具会仅签名Key区，BootFile的输入可以是fastboot.bin或者keyarea.bin

  制作未签名的安全Boot：
  不设置ROOT_RSA_Private_Key，设置external priv key，external pub key，生成各区镜像和除Key区以外其他区签名
  
  签名除Key区以外的所有区：
  不设置ROOT_RSA_Private_Key和external pub key，仅设置external priv key，生成其他区域的镜像及签名
  
  签名所有区
  从Signboot_config.cfg读入chiptype, key file, cfg.bin, msid, version, inputdir, outputdir 等信息，签名镜像生成在OutputFileDir参数设置的目录。
  
  可用-k -b -r -o等选项配置对应的key文件、boot表格、源文件、输出文件的路径
  
  2>./CASignTool 1 ../cfg/merge_config.cfg
  合并各区文件为最终的boot
  从merge_config.cfg读入chiptype, 已签名 bin 文件, inputdir, outputdir 等信息，合成final boot生成在OutputFileDir参数设置的目录。

  可用 -r -o等选项配置对应的源文件、输出文件的路径

  3>./CASignTool 2 -K KeyFilePath -R srcFilePath -O outputFilePath [-h 1|2] [-ss sectionsize] [-ys 1|0]
  非BOOT镜像common方式签名。
  参数-K指定签名非BOOT镜像所需的签名密钥，-R指定被签名的镜像所在路径，-O指定输出文件所在目录，-h指定签名方式，1为sha1，2为sha256，如果不指定，则默认为sha256，-ss指定分段签名的分段大小，例如按1MB大小分段签名，则指定为-ss 1，如果不指定或指定为0，则不分段签名，-ys指定文件系统，为1则为yaffs文件系统，为0或不指定则默认为NONE.

  可用-k -r -o等选项配置对应的key文件、源文件、输出文件的路径

  4>   ./CASignTool 3 special_merge_config.cfg -m m -K KeyFilePath -r srcDirPath -O destFilePath
   或者./CASignTool 3 special_single_config.cfg -m s -K KeyFilePath -r srcDirPath -o destDirPath
  非boot镜像special方式签名。
  
  合并模式
  在配置文件中，ImageNumber参数为需要签名的镜像数，增加一个签名镜像，增加ImageXXX,OffsetofImageXXX。XXX为索引数，依次增加。在命令行参数中用-m指定签名模式，指定为m即合并模式，-K指定签名密钥所在路径，-r指定被签名镜像所在的路径，-O指定合并出的签名镜像所在的路径
  
  单一批量签模式
  在配置文件中，ImageNumber参数为需要签名的镜像数，增加一个签名镜像，增加ImageXXX。XXX为索引数，依次增加。在命令行参数中用-m指定签名模式，指定为s即单一模式，-K指定签名密钥所在路径，-r指定被签名镜像所在的路径，-o指定合并出的签名镜像所在的目录
      
  5>./CASignTool 4 crypto_config.cfg [-it t/b -ot t/b] [-K KeyFilePath] -R srcFilePath -O destFilePath
  非boot镜像加密和解密。
  从crypto_config.cfg读入AES Key和IV向量等信息。参数-K指定RSA，sha1和sha2签名所需的密钥所在路径，-R指定输入文件所在路径，-O指定输出文件所在路径。
    说明： 需要根据需要配置crypto_config.cfg中的参数，比如AES加密，一定需要配置加密算法Algorithm，加密模式Mode，加密私钥Key，和IV向量，同时，加解密操作需要用-it指定输入文件的格式，用-ot指定输出文件的格式，t代表txt，b代表bin.

  6>./CASignTool 7 ../cfg/verifyboot.cfg
  验证Finalboot。
  从verifyboot.cfg读入Finalboot镜像、root pub key、msid、version、msidmask、versionmask、是否为加密镜像、加密密钥等信息，验证FinalBoot是否为正确生成。

  7>./CASignTool 8 eValue keyDestPath
  生成RSA密钥。
  输入素数eValue，以及密钥生成目录keyDestPath。创建的密钥生成到密钥生成目录
   
5.输入文件，输出文件名可在cfg文件里面配置

6.boot镜像签名时，支持的芯片包括Hi3798CV200,Hi3798MV100,Hi3716MV420,Hi3716MV410,Hi3796MV100,Hi3796MV200,Hi3798MV200,Hi3716DV110,可在cfg文件中配置，非boot镜像其他与芯片无关。
7.cfg文件自动去除以#开头的注释行
8.其他问题请另外咨询
