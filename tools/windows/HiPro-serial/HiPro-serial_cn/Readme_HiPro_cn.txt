1 HiPro-serial简介：
HiPro-serial主要用于生产环节批量on board烧写；支持裸片烧写，一次最多8个设备联机烧写。

2 HiPro-serial操作指导
本文仅提供简单的操作流程，HiPro-serial详细用法及量产烧录方法，请参考SDK文档：《量产烧写 使用指南》！
2.1 准备工作；（由研发工程师完成）
	1、编译工具所需的program.bin；详见《量产烧写 使用指南》
	2、通过BurnConfig.ini配置是否需要同时烧写MAC与ID（详见ini文件的注释）；
	3、选购指定型号U盘（获取的途径可以参考本文的注意事项），U盘格式化为fat32，内根目录下放固定文件名的usb_update.bin升级包镜像，usb_update.bin可以通过HiTool中HiBurn工具制作HiPro-serial镜像来生成；
	4、选购指定型号的USB HUB及USB转串口线（获取的途径可以参考本文的注意事项）；
	5、重新把HiPro-serial打包及相关设备提供给厂线。

2.2 厂线操作指导：
	1、PC连接USB HUB，再连接USB转串口线，固定此环境；
	2、解压HiPro-serial，打开HiPro-serial.exe执行文件,点击开始按钮；
	3、设备上插入U盘，再插上串口线，连接电源线，打开电源开关；
	4、输入MAC/ID（可选）；
	5、等待烧写过程，当出现"烧写正常完成"状态时（√），表示该单板烧写过程正常结束，可以正常断开电源。但出现"异常"状态时（×），表示该单板烧写过程出错，如果出现异常，查看串口编号，关闭HiPro-serial把HiPro-serial目录下对应串口日志发回研发。
	6、切换下个设备进行3～6同样的操作。（建议可以根据HiPro-serial上面的串口号进行标识，以免混淆。）

3 注意事项：
3.1 U盘 指定型号：Kingston DataTraveler 4G USB 2.0，如果用4G以上的盘，需格式化成一个4G分区来使用。U盘只放升级包文件。
	可以获取的U盘的途径：深圳华强电子世界4楼，Q4B135就是新华强，老板叫黄兆春 18898659618
	http://item.taobao.com/item.htm?spm=a1z10.3.0.72.uPOvap&id=9009181350&

3.2 USB HUB使用带电源的HUB，推荐型号：SSK
	飚王 SSK 积木 UBS分线器 USB集线器 USB HUB 带电源 SHU01
	http://detail.tmall.com/item.htm?spm=a230r.1.10.88&id=14491968034
 
3.3 USB转串口线（USB） 推荐型号：力特（Z-TEK）

