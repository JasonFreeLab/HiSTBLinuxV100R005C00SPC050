
Description
1. This tool is the Linux-version CASignTool.exe.
2. This tool uses the .cfg text to import configuration information. (The file name can be changed.)
3. Currently, this tool tolerates no space in the path.
4. This tool is used as follows:

  1>./CASignTool 0 ../cfg/Signboot_config.cfg
  Sign the key area only: 
  Among paths of the three key files, if either the Root_private_key_file and External_public_key_file or the Root_private_key_file and BootFile are filled, the CASignTool only signs the key area. The input of the BootFile can be fastboot.bin or keyarea.bin.
  
  Make unsigned file and secure boot:
  If the ROOT_RSA_Private_Key is not set while the external priv key and external pub key are set, the image and signature of other areas and the image of the key area are generated.
  
  Sign boot area except key area:
  If the ROOT_RSA_Private_Key and external public key are not set, and External_pivate_key_file is filled, the image and signature of other areas are generated.
  
  Sign all areas:
  Read in the information about the chiptype, key file, cfg.bin, msid, version, inputdir, and outputdir from the Signboot_config.cfg file. The signed image is generated in the directory set by using the parameter OutputFileDir.
  The options, such as -k, -b, -r, and -o, are available for configuring the corresponding paths of the key file, boot table, source file, and output file, respectively.

  2>./CASignTool 1 ../cfg/merge_config.cfg
  Combine files of all areas as the final boot image.
  Read in the information about the chiptype, signed .bin files, inputdir, and outputdir from the merge_config.cfg file to integrate the information as the final boot image. The final boot image is generated in the directory set by using the parameter OutputFileDir.
  The -r and -o options are available for configuring the corresponding paths of the source file and output file, respectively.

  3>./CASignTool 2 -K KeyFilePath -R srcFilePath -O outputFilePath [-h 1|2] [-ss sectionsize] [-ys 1|0]
  Sign the non-boot image in common mode.
  The parameter -K sets the path of signing key, -R sets the path of the image to be signed, -O sets the paths of the output path of the signed image. -h sets the method of signing, 1 is sha1, 2is sha256, if not set, choose sh256 be default. -ss sets 
  the section size, for example, to have 1MB segmented signature, set the value to be 1, if not set or 0 is set, the segmentation will not be done. -ys sets the file system, if 1 is set, the file system will be set as yaffs, if 0 is set, the file system will be NONE.

  The -k, -r, and ¨Co options are available for configuring the corresponding paths of the key file, source file, and output file, respectively.

  4>./CASignTool 3 special_merge_config.cfg -m m -K KeyFilePath -r srcDirPath -O destFilePath
   or ./CASignTool 3 special_single_config.cfg -m s -K KeyFilePath -r srcDirPath -o destDirPath
  Sign the non-boot image in special mode.
  Merge Model:
  In the config file, the parameter ImageNumber indicates the number of images to be signed. When a signed image is added, the parameters ImageXXX and OffsetofImageXXX are added. XXX indicates the number of indexes, and increases in sequence. For the command line, -m sets the signing model, m is merge model, -r sets the path of signed image, -O sets the path of merged image.

  Single Model:
  In the config file, the parameter ImageNumber indicates the number of images to be signed.When a signed image is added, the parameters ImageXXX are added. XXX indicates the number of indexes, and increases in sequence. For the command line, -m sets the signing model, s is single model, -R sets the path of signed image, -O sets the path of the directory of merged image.
      
  5>./CASignTool 4 crypto_config.cfg [-it t/b -ot t/b] [-K KeyFilePath] -R srcFilePath -O destFilePath
  Encrypt and decrypt the non-boot image.
  Read in the information about the AES key, initialization vector(IV) from the crypto_config.cfg file. -K sets the path of RSA private key file, -R sets the path of the inputfile, -O sets the path of output file.
    Note: Configure parameters in the crypto_config.cfg file as required. For example, if the AES encryption algorithm is used, you need to configure the encryption algorithm (Algorithm), encryption mode (Mode), encryption private key (Key), and IV. At the same time, during decrypting and encrypting, you nead to use -it and -ot to set the input and output type respectively, b means .bin, t means .txt, if not set, the file will be poccessed as binary file by default.
 
  6>./CASignTool 7 ../cfg/verifyboot.cfg
  Verify the final boot image.
  Read in the information about the final boot image, root pub key, msid, version, msidmask, versionmask, encryption status, and encryption key from the verifyboot.cfg file to verify whether the final boot image is generated correctly.

  7>./CASignTool 8 eValue keyDestPath
  Generate the RSA key.
  Enter the prime number eValue and the directory of the generated key keyDestPath. The created key is generated in the keyDestpath directory.

5. The names of the input files and output files can be configured in the .cfg file.
6. During the boot image signature, the supported chips include Hi3798 CV200, Hi3798M V100, Hi3716M V420, Hi3716M V410, Hi3796M V100, Hi3796M V200, Hi3798M V200 and Hi3716D V110. The chips can be configured in the .cfg file. For non-boot images, you do not need consider the chip type.
7. The .cfg files automatically delete the comment lines starting with #.
8. For other problems, contact us.
