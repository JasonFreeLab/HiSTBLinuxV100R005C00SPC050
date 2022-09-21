1.tsplay demo
   executable program£ºsample_ca_tsplay
   source code:sample_ca_tsplay.c 
   introduction: this demo show the following functions
                 1> loading clear CW or loading encrypted CWPK and encrypted CWs onto the chipset
                 2> processing of a scrambled transport stream and rendering the descrambled and decoded video on a display
                 The video data can be output through CVBS YPBPR or HDMI interface.
   usage: sample_ca_tsplay cw_key_config.ini tsfile
   if there is more than one program in the tsfile, you can select program by number.
   The cw_key_config.ini may contain keywords below:
    #For use clear cw or encrypted cw, YES or NO
    ENCRYPTCW = "YES"

    #Which keyladder use to descramber
    KLADTYPE = "CSA2"

    #Keyladder algorithm TDES or AES
    KLADALG  = "AES"
    
    #Encrypted cwpk
    SESSIONKEY1 = "A8E17FA05F9E47FF16110B594F7C17F6"
    SESSIONKEY2 = ""

    #Encrypted cw
    ENCRYPTEDODDKEY = "12C0B61BD7A5B5627AD87BE6959A61E6"
    ENCRYPTEDEVENKEY  = "09262CC117D861A84924ACBD113E6E81"

    #Clear cw    
    CLEARODDKEY       = "FE172C41A2E1D457"
    CLEAREVENKEY      = "D42282781D2872B7"

2.dvbplay demo
   executable program£ºsample_ca_dvbplay
   source code:sample_ca_dvbplay.c 
   introduction:this demo show the following functions
                 1> loading clear CW or loading encrypted CWPK and encrypted CWs onto the chipset
                 2> processing of a scrambled transport stream and rendering the descrambled and decoded video on a display
                 The video data can be output through CVBS YPBPR or HDMI interface.
   usage: sample_ca_dvbplay cw_key_config.ini freq
   The cw_key_config.ini may contain keywords below:
   #For use clear cw or encrypted cw, YES or NO
   ENCRYPTCW = "YES"

   #Which keyladder use to descramber
   KLADTYPE = "CSA2"

   #Keyladder algorithm TDES or AES
   KLADALG  = "AES"
    
   #Encrypted cwpk
   SESSIONKEY1 = "A8E17FA05F9E47FF16110B594F7C17F6"
   SESSIONKEY2 = ""

   #Encrypted cw
   ENCRYPTEDODDKEY = "12C0B61BD7A5B5627AD87BE6959A61E6"
   ENCRYPTEDEVENKEY  = "09262CC117D861A84924ACBD113E6E81"

   #Clear cw    
   CLEARODDKEY       = "FE172C41A2E1D457"
   CLEAREVENKEY      = "D42282781D2872B7"      
     
3.encrypt demo
   executable program£ºsample_ca_crypto
   source code:sample_ca_crypto.c 
   introduction:this demo show the following functions
                1> encrypting data user keyladder.
   usage: sample_ca_crypto crypto_key_config.ini
   The crypto_key_config.ini may contain keywords below:
   #For encrypt or decrypt
    #Which keyladder to use for encrypt or decrypt.
    KLADTYPE = "MISC"

    #The keyladder algorithm, AES or TDES, mode is fix to ECB
    KLADALG  = "TDES"

    #Encrypt or decrypt algorithm, the valid algorithm is AES, TDES
    Algorithm= "AES"

    #The Mode value is for AES and TDES
    #The valid Mode for AES is ECB,CBC
    #The valid Mode for TDES is ECB,CBC
    Mode= "CBC"

    #Data to be encrypted
    PLAINTTEXT   = "1234567800000000000000000000000000000000000000000000000000000000"

    #Keyladder session keys
    SESSIONKEY1  = "1f0e0d0c0b0a09080706050403020100"
    SESSIONKEY2  = "2f0e0d0c0b0a09080706050403020100"
    SESSIONKEY3  = "3f0e0d0c0b0a09080706050403020100"
    SESSIONKEY4  = "4f0e0d0c0b0a09080706050403020100"

    #Content key
    CONTENTKEY   = "0f0e0d0c0b0a09080706050403020100"
   
4.RSAkey demo
executable program: sample_ca_writeRSAkey
source code:sample_ca_writeRSAkey.c
introduction: show how to set RSAkey
usage: sample_ca_writeRSAkey 


5.Set OTP fuse
executable program: sample_ca_set_otp_fuse
source code:sample_ca_set_otp_fuse.c
introduction: set OTP fuse
usage: sample_ca_set_otp_fuse name value

6.Get OTP fuse
executable program: sample_ca_get_otp_fuse
source code:sample_ca_get_otp_fuse.c
introduction: show how to get otp fuse status
usage: sample_ca_get_otp_fuse

7.encrypt boot demo
executable program: sample_ca_blpk
source code:sample_ca_blpk.c
introduction: show how to encrypt boot and burn it to flash
usage: sample_ca_blpk

/******* cx function begin ********/
8.PVR record
executable program: sample_ca_pvrrec
source code:sample_ca_pvr_rec.c 
introduction:this demo show the PVR recording
usage: sample_ca_pvrrec
pvrrec file_path freq [SymbolRate] [qamtype] [vo_format]
      file_path: path of the recorded file. You do not need to enter the file name, because the file name is automatically generated based on the audio/video packet IDs (PIDs).
      The fields SymbolRate, qamtype, and vo_format are optional.
      The default value of SymbolRate is 6875.
      The value of qamtype is 16, 32, 64, 128, 256, or 512. The default value is 64QAM.
      The value vo_format is 1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50. The default value is 1080i_60.
      
      Notes£º When running this sample ,user can enter 
      1. 'r' to stop the recording and start new  recording again.
      2. 'f' to create a test fingerprint which will be saved in the CA private file.
      2. 'm' to create a test maturity rating which will be saved in CA private file.
      
9.PVR play
executable program: sample_ca_pvrplay
source code:sample_ca_pvr_play.c 
introduction:this demo show the PVR playing
usage: sample_ca_pvrplay
sample_ca_pvrplay file_name [vo_format]
      file_name: name of the file to be played, including the storage path
      The value vo_format is 1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50. The default value is 1080i_60.

10.PVR timeshift
executable program: sample_ca_pvrtimeshift
source code:sample_ca_pvr_timeshift.c 
introduction:this demo show the PVR record and play with timeshift
Usage: sample_ca_pvrtimeshift file_path freq [SymbolRate] [qamtype] [vo_format]
      file_path: Path of the replayed file. The file name is not required because it is generated automatically based on the audio and video pid.
      SymbolRate, qamtype, and vo_format are optional.
      The default value of SymbolRate is 6875.
      The value of qamtype should be in the range of 16|32|[64]|128|256|512. The default value is 64 QAM.
      The value of vo_format should be in the range of 1080P_60|1080P_50|1080i_60|[1080i_50]|720P_60|720P_50. The default value is 1080i_50.

      After time shift is started, the command line interface is displayed, on which the following operations are allowed.
         l: live play
         n: normal play
         p: pause/play
         f: fast forward (4x)
         s: slow forward (4x)
         r: fast rewind (4x)
         h: help
         a: start a new recording again
         q: quit
/******* cx function end ********/
