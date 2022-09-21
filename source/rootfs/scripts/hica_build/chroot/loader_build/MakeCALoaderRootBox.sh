#!/bin/sh

if [ $# -ne 3 ]
then
    echo -e "usage: $0  outdir  mode toolchain"
    echo -e "        for example: $0 /home/user/HiSTBLinuxV100R002/out/hi3716mv410/hi3716m41dma_ca_debug/rootbox DEBUG arm-histbv300-linux"
    exit 1
fi


rootbox_dir=$1
mode=$2
toolchain_name=$3
sdk_path=$1/../../../..
etc_dir=$sdk_path/source/rootfs/scripts/hica_build/chroot/loader_build

STRIP=${toolchain_name}-strip

if [ -d $etc_dir ];then
   echo "$etc_dir" 
else
   echo "$etc_dir is not exist"
   exit 1 
fi

if [ -d $rootbox_dir ];then
   echo "$rootbox_dir" 
else
   echo "$rootbox_dir is not exist"
   exit 1
fi


SCP=cp
SRM=rm


#check library path
if [ -d $rootbox_dir/home/stb/lib ];then
   $SRM -rf $rootbox_dir/home/stb/lib/*
else
   mkdir $rootbox_dir/home/stb/lib
fi

if [ -d $rootbox_dir/home/stb/usr/lib ];then
   $SRM -rf $rootbox_dir/home/stb/usr/lib/*
else
   mkdir $rootbox_dir/home/stb/usr/lib
fi

if [ ! -d $rootbox_dir/home/stb/proc ];then
   mkdir $rootbox_dir/home/stb/proc
fi

if [ ! -d $rootbox_dir/home/stb/sys ];then
   mkdir $rootbox_dir/home/stb/sys
fi

if [ ! -d $rootbox_dir/home/stb/mnt ];then
   mkdir $rootbox_dir/home/stb/mnt
fi
if [ -e $rootbox_dir/home/loader ]&&[ -d $rootbox_dir/home/res ];then
   $SCP -rvf  $rootbox_dir/home/loader $rootbox_dir/home/stb
   $SCP -rvf  $rootbox_dir/home/res $rootbox_dir/home/stb
   $SRM -rf	$rootbox_dir/home/loader
   $SRM -rf	$rootbox_dir/home/res
fi
echo "Step 1: copy necessary dynamic lib"

##########################################################################################################
# User should run the command like "/lib/ld-linux.so.3 --list /home/stb/sample_tsplay" on the board 
# to find the dynamic libraries need by the customer application "/home/stb/sample_tsplay", 
# the result does not include the audio libraries.
##########################################################################################################

#### copy the dynamic libraries needed by customer application in $rootbox/lib to the directory $rootbox/home/stb/lib

if [ $toolchain_name == "arm-histbv310-linux" ]; then
   	echo "toolchain_name is arm-histbv310-linux"
   	lib_to_cp=" librt-*.so "
	lib_to_cp+=" librt.so.1 "
	lib_to_cp+=" libcrypt-*.so "
	lib_to_cp+=" libcrypt.so.1 "
	lib_to_cp+=" libdl-*.so "
	lib_to_cp+=" libdl.so.2 "
	lib_to_cp+=" libstdc++.so.6.0.20 "
	lib_to_cp+=" libstdc++.so.6 "
	lib_to_cp+=" libpthread-*.so "
	lib_to_cp+=" libpthread.so.0 "
	lib_to_cp+=" libgcc_s.so.1 "
	lib_to_cp+=" libc-*.so "
	lib_to_cp+=" libc.so.6 "
	lib_to_cp+=" libm-*.so "
	lib_to_cp+=" libm.so.6 "
	lib_to_cp+=" ld-*.so "

	lib_to_cp+=" ld-linux.so.3 "
	lib_to_cp+=" libutil-*.so "
	lib_to_cp+=" libutil.so.1 "
fi

for ff in $lib_to_cp ; do 
    $SCP -d $rootbox_dir/lib/$ff 		$rootbox_dir/home/stb/lib
done

##########################################################################################################################
#### copy the dynamic libraries needed by customer application in $rootbox/lib to the directory $rootbox/home/stb/usr/lib
##########################################################################################################################
usrlib_to_cp=" libfreetype.* "
usrlib_to_cp+=" libz.* "

for ff in $usrlib_to_cp ; do
    $SCP -d $1/pub/lib/share/$ff 		$rootbox_dir/usr/lib
    $SCP -d $rootbox_dir/usr/lib/$ff 		$rootbox_dir/home/stb/usr/lib
done

if [ $mode == "DEBUG" ]; then
   echo "Step 2: update DEBUG vertion etc files"
   $SCP -a $etc_dir/debug/*  $rootbox_dir/etc
fi 


if [ $mode == "RELEASE" ] || [ $mode == "FINAL" ]; then

   echo "Step 2: update $mode version etc files"
    $SCP -a $etc_dir/release/*  $rootbox_dir/etc

    echo "Step 3: delete unused files"

    file_to_del+=" $rootbox_dir/etc/fs-version "
    file_to_del+=" $rootbox_dir/etc/ld.so.conf "
    file_to_del+=" $rootbox_dir/etc/mtab "
    file_to_del+=" $rootbox_dir/etc/profile "
    file_to_del+=" $rootbox_dir/etc/protocols "
    file_to_del+=" $rootbox_dir/etc/services "	
    file_to_del+=" $rootbox_dir/etc/init.d/S80network "
    file_to_del+=" $rootbox_dir/etc/init.d/S99init "
    file_to_del+=" $rootbox_dir/etc/udev/firmware.sh "
    file_to_del+=" $rootbox_dir/etc/udev/udev.conf "
    file_to_del+=" $rootbox_dir/etc/udev/usbdev-hotplug.sh "
    file_to_del+=" $rootbox_dir/etc/udev/udisk-hotplug.sh"
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/50-firmware.rules "
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/54-gphoto.rules "
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/60-pcmcia.rules "
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/61-usb-phone.rules "
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/75-cd-aliases-generator.rules.optional "
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/75-persistent-net-generator.rules.optional "
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/97-bluetooth-serial.rules "
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/99-fuse.rules "
    file_to_del+=" $rootbox_dir/etc/ld.so.cache "
    file_to_del+=" $rootbox_dir/etc/resolv.conf " 
    file_to_del+=" $rootbox_dir/home/stb/etc/ld.so.cache"
    file_to_del+=" $rootbox_dir/sbin/iptables* "                        
    file_to_del+=" $rootbox_dir/sbin/iptables* "
    file_to_del+=" $rootbox_dir/bin/him* "   
    file_to_del+=" $rootbox_dir/usr/lib/libiconv.so " 
    file_to_del+=" $rootbox_dir/usr/share/udhcpc "
    #file_to_del+=" $rootbox_dir/usr/lib/lib* "    
    file_to_del+=" $rootbox_dir/lib/libresolv* "
    file_to_del+=" $rootbox_dir/lib/libpcprofile.so "
    file_to_del+=" $rootbox_dir/lib/libmemusage.so "
    file_to_del+=" $rootbox_dir/lib/libnsl* "
    #file_to_del+=" $rootbox_dir/lib/libcrypt* "
    file_to_del+=" $rootbox_dir/lib/libcidn* "
    file_to_del+=" $rootbox_dir/lib/libanl* "
    file_to_del+=" $rootbox_dir/lib/libSegFault* "
    file_to_del+=" $rootbox_dir/lib/libBrokenLocale* "    
    file_to_del+=" $rootbox_dir/lib/libBrokenLocale* "
    #libnss* can not be deleted because CA need us delete CONFIG_USE_BB_PWD_GRP, CONFIG_USE_BB_SHADOW, CONFIG_USE_BB_CRYPT, and  CONFIG_USE_BB_CRYPT_SHA.
    #Then libnss* can not be deleted,otherwise ,login can not be used in release enviorment.
    #file_to_del+=" $rootbox_dir/lib/libnss* "
    file_to_del+=" $rootbox_dir/lib/firmware "
    file_to_del+=" $rootbox_dir/dev/console "
    file_to_del+=" $rootbox_dir/dev/tty* "
    file_to_del+=" $rootbox_dir/share "
    file_to_del+=" $rootbox_dir/lib/libutil* "
    file_to_del+=" $rootbox_dir/opt "
    file_to_del+=" $rootbox_dir/tmp "
    
    for ff in $file_to_del ; do
        $SRM  -rf $ff
    done

fi

# prepare different /etc/inittab for debug and release mode 
if [ "$mode" == "DEBUG" ]; then

# create console devnode
mknod $rootbox_dir/dev/console c 5 1

else # release or final mode

    file_to_del+=" $rootbox_dir/dev/console "
    file_to_del+=" $rootbox_dir/dev/tty* " 

    for ff in $file_to_del ; do
        $SRM  -rf $ff
    done
fi

echo "Step 3: strip lib or binary files"
STRIP_DIR="$rootbox_dir/bin/"
STRIP_DIR+=" $rootbox_dir/lib/"
STRIP_DIR+=" $rootbox_dir/sbin/"
STRIP_DIR+=" $rootbox_dir/usr/"
STRIP_DIR+=" $rootbox_dir/home/"

files=`find $STRIP_DIR -type f`
for ff in $files ; do    
    $STRIP $ff 2> /dev/null
    $STRIP $ff -R .note -R .comment 2> /dev/null
    if [ $? -ne 0 ]; then
    continue; #Ignore error during strip
    fi
done
