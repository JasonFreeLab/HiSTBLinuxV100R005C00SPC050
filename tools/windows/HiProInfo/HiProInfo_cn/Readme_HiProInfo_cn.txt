1、HiProInfo简介
HiProInfo用于生产环节MAC、ID、OUI、HW以及共享分区信息的烧写。
HiProInfo的排列格式遵循fc:48:ef:c9:35:36\0sn\0MAGICNUM=deviceinfo\0LENGTH=xxxxxxxx\0OUI=xxxxxxxx\0HW=xxxxxxxx\0;其中MAC必须放在deviceinfo分区头，sn的长度不定，OUI/HW顺序不定，格式形式一定，允许自定义添加；deviceinfo分区可以通过SDK提供的接口HI_UNF_PDM_GetDeviceInfo获取相应的值。


2、HiProInfo操作指导
	0）根据量产要烧写的内容进行BurnConfig.ini
	
	1）选择串口号	 
	
	2）选择变化规则；
	烧写成功后会遵照规则对上面填写的Mac地址及序列号等进行自动更新，以免去手动修改的麻烦。
	清空（remove）：选择清空，每次都需要重新手动输入或扫描枪输入；
	递增（increase）/递减（decrease）：表示MAC和序列号都遵循递增或递减规律，如：<string>输入Hisi2012，<number>输入00000001，遵循生成规则拼接成最终sn号(Hisi201200000001)，写入flash的SN区域；下个单板连接后，工具会自动输入：Hisi201200000002 
	
	3）输入要烧写的Mac地址、序列号等，工具打开后焦点会置于Mac处，回车焦点会自动移动，以便于下次输入、烧写(提示成功后扫描，回车即可)。
	
	4）点击"Burn"按钮开始烧写：这时候在信息输出窗口中会有提示，烧写已启动，请给单板上电或在已上电的情况下重启单板。
	
3、注意事项
	1、正常情况下，点击"Burn"按钮之后会很快烧写完毕，信息输出窗口会有连续信息输出，如果遇到操作错误或环境异常导致点击"Burn"按钮之后程序没反应的情况，请重启程序，重新操作。

	2、当前烧完的Mac地址，并将焦点置于Mac地址输入框，以便于下次输入、烧写(提示成功后扫描，回车即可)。
	
	3、关于高安CA不能烧写的问题工具端已做了兼容性修改更新，但必须附带BurnConfig.ini(其内配置项IsCA配置为1)和ProgrammerforCA.bin（由客户提供有烧录命令的boot版本，文件名必须改为ProgrammerforCA.bin）两个文件。其它烧写不需要ProgrammerforCA.bin文件，BurnConfig.ini文件必须将其内配置项IsCA配置为0。
