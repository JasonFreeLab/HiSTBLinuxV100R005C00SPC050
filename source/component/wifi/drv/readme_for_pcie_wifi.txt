软件约束：

./device/hisilicon/Hi3798MV200/BoardConfig.mk中使能 WiFi+Bluetooth combo module时，
如下编译开关只准将一个配置为y，其余必须配置为n
# RTL8723BU
BOARD_BLUETOOTH_WIFI_DEVICE_RTL8723BU := n
# RTL8822BU
BOARD_BLUETOOTH_WIFI_DEVICE_RTL8822BU := n
# RTL8822BEH
BOARD_BLUETOOTH_WIFI_DEVICE_RTL8822BEH := n
# MT7662TU
BOARD_BLUETOOTH_WIFI_DEVICE_MT7662TU := n
# MT7662TE
BOARD_BLUETOOTH_WIFI_DEVICE_MT7662TE := y
# AP6356S
BOARD_BLUETOOTH_WIFI_DEVICE_AP6356S := n
# QCA6174
BOARD_BLUETOOTH_WIFI_DEVICE_QCA6174 := n

硬件约束：

1、boot中combo phy配为PCIE，复用配为UART

2、根据PCIE Reset管脚选择的GPIO接口，修改.\device\hisilicon\bigfish\sdk\source\kernel\linux-3.18.y\drivers\hisilicon\clk\hi3798mv2x\clk-hipcie.c
   （如果采用的gpio口为gpio4_3，同海思DMP单板相同，则不需要更改）

#ifdef TESTBOARD
        /* PCIe reset and release,use GPIO4_3 */
        if (!pcie_host0_regbase) {
                pcie_host0_regbase = ioremap_nocache(GPIO4_BASE + 0x400, 0x20);
                if (!pcie_host0_regbase) {
                        printk("ioremap xhci host0 failed.\n");
                        return -1;
                }
        }
        reg=readl(pcie_host0_regbase);
        reg |= 0x1<<3;
        writel(reg, pcie_host0_regbase);//Set GPIO4_3 to output mode
        mdelay(10);

        if (pcie_host0_regbase) {
                iounmap(pcie_host0_regbase);
                pcie_host0_regbase = NULL;
        }

        if (!pcie_host0_regbase) {
                pcie_host0_regbase = ioremap_nocache(GPIO4_BASE + 0x20, 0x20);
                if (!pcie_host0_regbase) {
                        printk("ioremap xhci host0 failed.\n");
                        return -1;
                }
        }

        writel(0x00, pcie_host0_regbase);//Set GPIO4_3 output low to reset PCIe EP
        mdelay(10);

        writel(0x08, pcie_host0_regbase);//Set GPIO4_3 output High to release reset
        mdelay(10);

        if (pcie_host0_regbase) {
                iounmap(pcie_host0_regbase);
                pcie_host0_regbase = NULL;
        }
#endif

3、请根据BT_EN管脚选择的GPIO接口修改相关GPIO接口控制代码
   （（如果采用的gpio口为gpio5_4，同海思DMP单板相同，则不需要更改））

a、RTL8822BEH修改如下部分：

.\device\hisilicon\bigfish\bluetooth\rtkbt\rtk_rfkill\rtk_rfkill.c中如下部分：

	bt_reset = of_get_gpio_flags(rtk119x_bt_node, 0, NULL); 	// get gpio number from device tree
	//根据选择的GPIO口修改，默认使用的为GPIO5_4
	bt_reset = 44 ; //GPIO5_4 = 5*8+4 = 44

b、QCA6174修改如下部分：

.\device\hisilicon\bigfish\bluetooth\qca6174\libbtvendor\libbt-vendor\src\bt_vendor_qcom.c

#define QCA6174_BT_EN 5*8+4  //根据选择的GPIO口修改，默认使用的为GPIO5_4

c、MT7662TE不需要修改

4、根据蓝牙接的串口号，修改串口节点（默认ttyAMA1，UART2）

a、RTL8822BEH修改如下部分：

//如果使用UART3，则将下面的ttyAMA1改为ttyAMA2
.\device\hisilicon\bigfish\bluetooth\rtkbt\system\etc\bluetooth\uart\rtkbt.conf中
#Indicate USB or UART driver bluetooth
BtDeviceNode=/dev/ttyAMA1
\device\hisilicon\bigfish\bluetooth\qca6174\libbtvendor\libbt-vendor\include\vnd_generic.txt中
BLUETOOTH_UART_DEVICE_PORT = "/dev/ttyAMA1"

b、QCA6174修改如下部分：

//如果使用UART3，则将下面的ttyAMA1改为ttyAMA2
./device/hisilicon/bigfish/bluetooth/qca6174/libbtvendor/libbt-vendor/include/hci_uart.h:25:#define BLUETOOTH_UART_DEVICE_PORT "/dev/ttyAMA1"
./device/hisilicon/bigfish/bluetooth/qca6174/libbtvendor/libbt-vendor/include/hci_smd.h:30:#define APPS_RIVA_BT_ACL_CH  "/dev/ttyAMA1"
./device/hisilicon/bigfish/bluetooth/qca6174/libbtvendor/libbt-vendor/include/hci_smd.h:31:#define APPS_RIVA_BT_CMD_CH  "/dev/ttyAMA1"
./device/hisilicon/bigfish/bluetooth/qca6174/libbtvendor/libbt-vendor/include/vnd_generic.txt:1:BLUETOOTH_UART_DEVICE_PORT = "/dev/ttyAMA1"

c、MT7662TE蓝牙为USB接口，不需要修改

5、修改串口权限：

修改如下文件对应串口节点权限
//如果使用UART3，则将下面的ttyAMA1改为ttyAMA2
.\device\hisilicon\bigfish\etc\ueventd.bigfish.telecom.rc
#for UART Bluetooth
/dev/ttyAMA1 0660 bluetooth net_bt_stack

.\device\hisilicon\bigfish\etc\ueventd.bigfish.default.rc
#for UART Bluetooth
/dev/ttyAMA1 0660 bluetooth net_bt_stack

.\device\hisilicon\bigfish\etc\ueventd.bigfish.rc
#for UART Bluetooth
/dev/ttyAMA1 0660 bluetooth net_bt_stack
