1¡¢About HiProInfo
HiProInfo is used for MAC&ID programming in the process of production.
Here order:fc:48:ef:c9:35:36\0sn\0MAGICNUM=deviceinfo\0LENGTH=xxxxxxxx\0OUI=xxxxxxxx\0HW=xxxxxxxx\0;you can get these values using HI_UNF_PDM_GetDeviceInfo api.

2¡¢HiProInfo operating instructions
	0) Configure BurnConfig.ini
	
	1£©Select the serial port.
	
	
	2£©Choose a rule. When a single burning operation is finished, the Mac address and serial number for the next board will be changed according to the rule.
	remove:If users use scanner to input the Mac address, please turn the rule to "Remove".(Scan the address and Press ENTER to continue when a single burning operation finished)
	increase/decrease:If "increase" rule, please type in <String> and <Number> fields.
	Example: if the value of <String> field is "Hisi2012" and the value of <Number> field is "00000001", then the serial number will be "Hisi201200000001".Next time it will be "Hisi201200000002"
	
	3£©Input the Mac address for the board. Once finishing, it will be saved and loaded automatically. A simple guide is shown beside the input box control.


	4£©Click the "Burn" button to perform a single burning operation. Then£¬a tip will be displayed in the console window. Please turn on the board, or restart the board when it's on already.
	

3¡¢Notes	
	1. Most of the time a burning operation will be done soon, and there will be a large number of lines displayed in the console window. If the user operates the application in the wrong way, or the application gives no response after user clicking "Burn" button, please restart HiProInfo application and try again.
	
	2. "Enter" key may help you not use the mouse.
	
	5. In order to support CA boards, users must provide two files named "BurnConfig.ini" (with the IsCA parameter set to 1) and "ProgrammerforCA.bin". "ProgrammerforCA.bin" file is not needed when burning NON-CA boards, and if users provide "BurnConfig.ini" file, the IsCA parameter must be set to 0.
