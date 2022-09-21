plcipher sample:
   executable program£ºsample_plcipher
   source code:sample_plcipher.c
   introduction: this sample show the following functions
         1> init the plcipher module
         2> create the plcpher channel
         3> get the default atrribute of the plcipher channel
         4> set the atrribute of the plcipher channel
         5> encrypt the clear ts stream
         6> destroy the plcipher channel
         7> deinit the plcipher module
     The encrypted ts stream can be output into an ts file.

     notice: if the arguments doesn't contain the pids, it will encrypt all pids in the ts, and this sample support max 5 pids to be encrypted.

  usage: sample_plcipher configfile file_to_encrypt file_encrypted pid1 pid2 pid3 pid4 pid5
    examples:
       ./sample_plcipher ./cw_key_config.ini ./plain.ts ./encrypted.ts 0x20 0x21

   The cw_key_config.ini may contain keywords below:
  #######################################################
  #Which plcipher use to encrypt
  CWKEYTYPE = "AES_CBC"
  #CWKEYTYPE = "AES_IPTV"
  #CWKEYTYPE = "AES_ECB"

  KEYODDOREVEN = "ODD"
  #KEYODDOREVEN = "EVEN"

  CLEARODDKEY       = "00112233445566778899AABBCCDDEEFF"
  CLEAREVENKEY      = "00112233445566778899AABBCCDDEEFF"

  CLEARODDIV        = ""
  CLEAREVENIV       = ""
