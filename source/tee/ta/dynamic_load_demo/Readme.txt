1 编译：
（1）增加c源文件，并在Makefile里面添加编译，如sample hisi_demo_task.c
（2）在当前目录输入命令  make， 生成的文件在 out目录下，包括elf 的ta文件和增加了头部信息的(uuid).bin文件，其中 (uuid).bin用于动态加载，elf文件可用于静态加载。

2 去编译
在当前目录输入命令  make clean

3 配置ta属性
在 manifest.txt 里面按照既定的格式添加 ta的属性，包括uuid，ta名字，Session属性，stack等

4 目录说明
include ：包含一些基本头文件，包括gp标准头文件，安全存储头文件，time头文件等
lib ：包含ta的链接库，如果有需要可自行添加，并在ta.mak里面添加链接关系
out： 编译输出目录
script：包含ta的编译相关脚本
toolchains： 编译ta的工具链

5、公共ta.mak包含了公共的头文件，其他第三方ta需要包含特殊模块的头文件，需要在Makefile里面自行添加