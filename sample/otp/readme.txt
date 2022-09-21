1.  Get customerkey demo
    executable sample_otp_getcustomerkey
    source code: sample_otp_getcustomerkey.c
    introduction: print customerkey on debug screen.
    usage: sample_otp_getcustomerkey

2.  Get HDCPkey lock flag demo
    executable sample_otp_gethdcprootkeylockflag
    source code: sample_otp_gethdcprootkeylockflag.c
    introduction: show hdcprootkey is lock or not
    usage: sample_otp_gethdcprootkeylockflag

3.  Get privdata demo
    executable sample_otp_getstbprivatedata
    source code: sample_otp_getstbprivatedata.c
    introduction: print stb privatedata on debug screen.
    usage: sample_otp_getstbprivatedata

4.  Get STBRootkey lock flag demo
    executable sample_otp_getstbrootkeylockflag
    source code: sample_otp_getstbrootkeylockflag.c
    introduction: show stbrootkey is lock or not
    usage: sample_otp_getstbrootkeylockflag

5.  Lock HDCPRootkey demo
    executable sample_otp_lockhdcprootkey
    source code: sample_otp_lockhdcprootkey.c
    introduction: set hdcprootkey lock flag
    usage: sample_otp_lockhdcprootkey

6.  Lock STBRootkey demo
    executable sample_otp_lockstbrootkey
    source code: sample_otp_lockstbrootkey.c
    introduction: set stbrootkey lock flag
    usage: sample_otp_lockstbrootkey

7.  Set Customerkey demo
    executable sample_otp_setcustomerkey
    source code: sample_otp_setcustomerkey.c
    introduction: set customerkey to otp
    usage: sample_otp_setcustomerkey

8.  Set HDCPRootkey demo
    executable sample_otp_sethdcprootkey
    source code: sample_otp_sethdcprootkey.c
    introduction: set hdcprootkey to otp
    usage: sample_otp_sethdcprootkey

9.  Set stb private data demo
    executable sample_otp_setstbprivatedata
    source code: sample_otp_setstbprivatedata.c
    introduction: set stb private data to otp
    usage: sample_otp_setstbprivatedata

10. Set STBRootkey demo
    executable sample_otp_setstbrootkey
    source code: sample_otp_setstbrootkey.c
    introduction: set stbrootkey to otp
    usage: sample_otp_setstbrootkey

11. lock idword demo
    executable sample_otp_lockidword
    source code: sample_otp_lockidword.c
    introduction:
    1. burn to nomal chipset
    usage: ./sample_otp_lockidword 0
    2. burn to secure chipset
    usage: ./sample_otp_lockidword 1
    3. get idword lock flag
    usage: ./sample_otp_lockidword 2

12.Set SCS activation demo
    executable sample_otp_setscsenable
    source code: sample_otp_setscsenable.c
    introduction: set secure boot activation
    usage: ./sample_otp_setscsenable
    
13.Get SCS activation demo
    executable sample_otp_getscsstatus
    source code: sample_otp_getscsstatus.c
    introduction: show secure boot is enable or disable
    usage: ./sample_otp_getscsstatus
