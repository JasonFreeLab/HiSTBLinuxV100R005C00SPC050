#!/bin/sh

if [ $# -ne 3 ]
then
    echo -e "usage: ./MakeCASystemRootBox.sh outdir mode toolchain"
    echo -e "        for example: ./MakeCASystemRootBox.sh /home/user/HiSTBLinuxV100R002/out/hi3716mv410/hi3716m41dma_ca_debug/rootbox DEBUG arm-histbv300-linux"
    exit 1
fi

rootbox_dir=$1
mode=$2
toolchain_name=$3
sdk_path=$1/../../../..
etc_dir=$sdk_path/source/rootfs/scripts/hica_build/lxc/system_build


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

if [ ! -d $rootbox_dir/home/stb/usr/sbin ];then
   mkdir $rootbox_dir/home/stb/usr/sbin
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

if [ ! -d $rootbox_dir/home/stb/home ];then
   mkdir $rootbox_dir/home/stb/home
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
   	lib_to_cp=" librt-2.24.so "
	lib_to_cp+=" librt.so.1 "
	lib_to_cp+=" libcrypt-2.24.so "
	lib_to_cp+=" libcrypt.so.1 "
	lib_to_cp+=" libdl-2.24.so "
	lib_to_cp+=" libdl.so.2 "
	lib_to_cp+=" libstdc++.so.6.0.20 "
	lib_to_cp+=" libstdc++.so.6 "
	lib_to_cp+=" libpthread-2.24.so "
	lib_to_cp+=" libpthread.so.0 "
	lib_to_cp+=" libgcc_s.so.1 "
	lib_to_cp+=" libc-2.24.so "
	lib_to_cp+=" libc.so.6 "
	lib_to_cp+=" libm-2.24.so "
	lib_to_cp+=" libm.so.6 "
	lib_to_cp+=" ld-2.24.so "
	lib_to_cp+=" ld-linux.so.3 "
	lib_to_cp+=" libutil-2.24.so "
   	lib_to_cp+=" libutil.so.1 "
fi

for ff in $lib_to_cp ; do
    $SCP -d $rootbox_dir/lib/$ff 		$rootbox_dir/home/stb/lib
done


##########################################################################################################################
#### copy the dynamic libraries needed by customer application in $rootbox/lib to the directory $rootbox/home/stb/usr/lib
##########################################################################################################################
usrlib_to_cp=" libHA.AUDIO.* "
usrlib_to_cp+=" libfreetype.so.6.14.0 "
usrlib_to_cp+=" libfreetype.so.6 "
usrlib_to_cp+=" libfreetype.so "
usrlib_to_cp+=" libz.so.1.2.11 "
usrlib_to_cp+=" libz.so.1 "
usrlib_to_cp+=" libz.so "
usrlib_to_cp+=" libssl.so.1.0.0 "
usrlib_to_cp+=" libssl.so "
usrlib_to_cp+=" libcrypto.so.1.0.0 "
usrlib_to_cp+=" libcrypto.so "

usrlib_to_cp+=" liblxc.so.1.2.0 "
usrlib_to_cp+=" liblxc.so.1 "
usrlib_to_cp+=" liblxc.so "
usrlib_to_cp+=" libcap.so.2.25 "
usrlib_to_cp+=" libcap.so.2 "
usrlib_to_cp+=" libcap.so "


usrlib_to_cp+=" libhigo.so "
usrlib_to_cp+=" libhigoadp.so "
usrlib_to_cp+=" higo-adp "

for ff in $usrlib_to_cp ; do
    $SCP -r -d $rootbox_dir/usr/lib/$ff 		$rootbox_dir/home/stb/usr/lib
done

##########################################################################################################################
#### copy the some executive binaries into LXC
##########################################################################################################################
$SCP -rf $rootbox_dir/usr/sbin/init.lxc $rootbox_dir/home/stb/usr/sbin/

##########################################################################################################################
#### copy the iptables command into LXC
##########################################################################################################################
$SCP -rf $rootbox_dir/sbin/iptables $rootbox_dir/home/stb/sbin/
$SCP -rf $rootbox_dir/sbin/xtables-multi $rootbox_dir/home/stb/sbin/

##########################################################################################################################
if [ $rootbox_dir == "/" ]; then

    echo "target is root dir, copy the lib to board and should change the owner"
    chown -R 1000:1000 $rootbox_dir/home/stb/lib
    chown -R 1000:1000 $rootbox_dir/home/stb/usr/lib
fi

if [ $mode == "DEBUG" ]; then
   echo "Step 2: update DEBUG vertion etc files"
   $SCP -a $etc_dir/debug/*  $rootbox_dir/etc
fi

if [ $mode == "RELEASE" ]; then

    echo "Step 2: update $mode version etc files"
    mode_dir=`echo $mode | tr "[A-Z]" "[a-z]"`
    $SCP -a $etc_dir/$mode_dir/*  $rootbox_dir/etc

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
#if customer do not use USB in App ,should delete disk-hotplug.sh and 11-usb-hotplug.rules
#   file_to_del+=" $rootbox_dir/etc/udev/disk-hotplug.sh"
#   file_to_del+=" $rootbox_dir/etc/udev/rules.d/11-usb-hotplug.rules "
    file_to_del+=" $rootbox_dir/etc/udev/udisk-hotplug.sh"
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/50-firmware.rules "
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/54-gphoto.rules "
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/60-pcmcia.rules "
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/61-usb-phone.rules "
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/75-cd-aliases-generator.rules.optional "
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/75-persistent-net-generator.rules.optional "
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/90-hal.rules "
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/device-mapper.rules "
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/97-bluetooth-serial.rules "
    file_to_del+=" $rootbox_dir/etc/udev/rules.d/99-fuse.rules "
    file_to_del+=" $rootbox_dir/etc/ld.so.cache "
    file_to_del+=" $rootbox_dir/etc/resolv.conf "
    file_to_del+=" $rootbox_dir/home/stb/etc/ld.so.cache"
#   file_to_del+=" $rootbox_dir/sbin/iptables* "
    file_to_del+=" $rootbox_dir/bin/him* "
    file_to_del+=" $rootbox_dir/usr/lib/libiconv.so "
    file_to_del+=" $rootbox_dir/usr/share/udhcpc "
#   file_to_del+=" $rootbox_dir/usr/lib/lib* "
    file_to_del+=" $rootbox_dir/lib/libresolv* "
    file_to_del+=" $rootbox_dir/lib/libpcprofile.so "
    file_to_del+=" $rootbox_dir/lib/libmemusage.so "
    file_to_del+=" $rootbox_dir/lib/libnsl* "
#   file_to_del+=" $rootbox_dir/lib/libcrypt* "
    file_to_del+=" $rootbox_dir/lib/libcidn* "
    file_to_del+=" $rootbox_dir/lib/libanl* "
    file_to_del+=" $rootbox_dir/lib/libSegFault* "
    file_to_del+=" $rootbox_dir/lib/libBrokenLocale* "
    file_to_del+=" $rootbox_dir/lib/libBrokenLocale* "
#libnss* can not be deleted because CA need us delete CONFIG_USE_BB_PWD_GRP, CONFIG_USE_BB_SHADOW, CONFIG_USE_BB_CRYPT, and  CONFIG_USE_BB_CRYPT_SHA.
#Then libnss* can not be deleted,otherwise ,login can not be used in release enviorment.
#   file_to_del+=" $rootbox_dir/lib/libnss* "
    file_to_del+=" $rootbox_dir/lib/firmware "
    file_to_del+=" $rootbox_dir/dev/console "
    file_to_del+=" $rootbox_dir/dev/tty* "
    file_to_del+=" $rootbox_dir/share "

    for ff in $file_to_del ; do
        $SRM  -rf $ff
    done

fi

if [ $mode == "RELEASE" ]; then
    file_to_del+=" $rootbox_dir/dev/console "
    file_to_del+=" $rootbox_dir/dev/tty* "

    for ff in $file_to_del ; do
        $SRM  -rf $ff
    done

fi



echo "Step 3: strip lib or binary file "
############ strip lib or binary file################################
$STRIP --strip-debug --strip-unneeded --remove-section=.comment --remove-section=.note --preserve-dates $rootbox_dir/kmod/usb/*.ko
$STRIP --strip-debug --strip-unneeded --remove-section=.comment --remove-section=.note --preserve-dates $rootbox_dir/kmod/*.ko

STRIP_DIR="$rootbox_dir/bin/"
STRIP_DIR+=" $rootbox_dir/lib/"
STRIP_DIR+=" $rootbox_dir/sbin/"
STRIP_DIR+=" $rootbox_dir/usr/"
STRIP_DIR+=" $rootbox_dir/home/stb/bin/"
STRIP_DIR+=" $rootbox_dir/home/stb/lib/"
STRIP_DIR+=" $rootbox_dir/home/stb/usr/"
STRIP_DIR+=" $rootbox_dir/home/stb/home/"

files=`find $STRIP_DIR -type f`
for ff in $files ; do
    $STRIP $ff 2> /dev/null
    $STRIP $ff -R .note -R .comment 2> /dev/null
    if [ $? -ne 0 ]; then
    continue; #Ignore error during strip
    fi
done

echo "Step 4: creat LXC "
if [ -x $etc_dir/lxc_create_proxy.sh ];then
   $etc_dir/lxc_create_proxy.sh $mode $rootbox_dir proxy
fi
if [ -x $etc_dir/lxc_create_server.sh ];then
   $etc_dir/lxc_create_server.sh $mode $rootbox_dir server
fi
if [ -x $etc_dir/lxc_create_dtv_core.sh ];then
   $etc_dir/lxc_create_dtv_core.sh $mode $rootbox_dir core
fi
if [ -x $etc_dir/lxc_create_browser.sh ];then
   $etc_dir/lxc_create_browser.sh $mode $rootbox_dir browser
fi
#Only for basic lxc
if [ -x $etc_dir/lxc_create_base.sh ];then
	$etc_dir/lxc_create_base.sh $mode $rootbox_dir lxc
fi

$SRM  -rf $rootbox_dir/home/stb
