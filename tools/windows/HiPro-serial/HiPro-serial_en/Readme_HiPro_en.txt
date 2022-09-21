1. About HiPro-serial£º
HiPro-serial is used for bare board programming in the process of production,at the same time it can connect no more than eight devices.
2. HiPro-serial operating instructions
	This paper introduces the base operation of HiPro-serial, please refer to Mass Production Burning User Guide.pdf for detailed operation guide.
	2.1. Preparation£¨for R&D engineer£©
	1) Compile program HiPro-serial required according reference material£¬ please refer to Mass Production Burning User Guide.pdf released with SDK;
	2) Config BurnConfig.ini to select whether inculde programming Mac and ID;
	3) Purchase specified U disk(refer to Charter 3 related content),format with fat32,and put the image named usb_update.bin you want to programming;usb_update.bin needed by HiPro-serial can be made by HiTool;
	4) Purchase specified usb hub and usb-serial cable(refer to Charter 3 related content);
	5) Pack related file and materials to production line;
	
	2.2 Guide for production line
	1) Connect PC and usb hub£¬and then connect the usb-serial cable
	2) Open HiPro-serial.exe in the HiPro-serial directory from RD engineer,and click the Start button;
	3) Insert U disk to the device that you want to program,plug in the serial/power cable, and then turn on the power switch;
	4) enter MAC/ID(Optional);
	5) Wait until ¡°¡Ì¡± appearing(meaning normal completion status),then you can disconnect the power normally;if "¡Á" appearing(meaning abnormal status),then you can try again to replug in u disk and cables;if the problem persist,then you can close HiPro-serial and send serial logs back to R&D;
	6) Switch to the next device£¬and repeate 3¡«5 operations, after normal completion of one device programming(It's suggested that you should mark the cables to avoid confusion);

3¡¢Notes
	3.1 U disk specified models: Kingston DataTraveler 4G USB 2.0(with more than 4G disk is formatted as a 4G partition to use and U disk just only with the upgrade package file).

	3.2 USB HUB with power, Recommended Model: SSK USB HUB SHU01

	3.3 USB to serial cable,Recommended Model:Z-Tek


	
	
	
	
	
