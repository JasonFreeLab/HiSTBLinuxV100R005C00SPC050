#!/bin/sh

if [ $# -ne 3 ]
then
    echo -e "usage: ./lxc_creat.sh mode rootbox_dir lxc_name"
    echo -e "        for example: ./lxc_creat.sh DEBUG /home/user/HiSTBLinuxV100R002/out/hi3716mv410/hi3716m41dma_ca_debug/rootbox stb"
    exit 1
fi

LXC_MODE=$1
SDK_PATH=$2/../../../..
PREFIX=$2
name=$3

SAMPLE_OUT_PATH=$2/../$OBJ_NAME/sample


APP_NAME=sample_dvbplay

# create fs directory tree
install_fs_dir()
{
    tree="\
$PREFIX/$lxc_rootfs_dir/dev \
$PREFIX/$lxc_rootfs_dir/home \
$PREFIX/$lxc_rootfs_dir/root \
$PREFIX/$lxc_rootfs_dir/etc \
$PREFIX/$lxc_rootfs_dir/etc/init.d \
$PREFIX/$lxc_rootfs_dir/bin \
$PREFIX/$lxc_rootfs_dir/sbin \
$PREFIX/$lxc_rootfs_dir/proc \
$PREFIX/$lxc_rootfs_dir/sys \
$PREFIX/$lxc_rootfs_dir/mnt \
$PREFIX/$lxc_rootfs_dir/tmp \
$PREFIX/$lxc_rootfs_dir/dev/pts \
$PREFIX/$lxc_rootfs_dir/lib \
$PREFIX/$lxc_rootfs_dir/usr/sbin \
$PREFIX/$lxc_rootfs_dir/usr/lib"

    mkdir -p $tree
        chmod 755 $tree

    mkdir -p $PREFIX/`dirname $lxc_config_file`
}

# create container init script for CA debug
install_dbg_fs_scripts()
{
    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/inittab
::sysinit:/etc/init.d/rcS
tty1::respawn:/bin/sh
EOF
    chmod 644 $PREFIX/$lxc_rootfs_dir/etc/inittab

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/init.d/rcS
#!/bin/sh
EOF
    chmod 744 $PREFIX/$lxc_rootfs_dir//etc/init.d/rcS

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/passwd
root:x:0:0:root:/root:/bin/sh
lxc:x:1000:1000:Linux User,,,:/home:/bin/sh
EOF
    chmod 644 $PREFIX/$lxc_rootfs_dir/etc/passwd

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/group
root:x:0:root
gstb:x:1000:
EOF
    chmod 644 $PREFIX/$lxc_rootfs_dir/etc/group

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/shadow
$name:\$1\$eF8I65UL\$7FfdLFZEBw46GPpAOYcOQ/:0:0:99999:7:::
EOF
    chmod 640 $PREFIX/$lxc_rootfs_dir/etc/shadow

    # udhcpc scripts
    mkdir -p $PREFIX/$lxc_rootfs_dir/usr/share/udhcpc
    cp -r $PREFIX/usr/share/udhcpc/* $PREFIX/$lxc_rootfs_dir/usr/share/udhcpc

}


# create container init script for CA release
install_rel_fs_scripts()
{
    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/inittab
::sysinit:/etc/init.d/rcS
EOF
    chmod 644 $PREFIX/$lxc_rootfs_dir/etc/inittab

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/init.d/rcS
#!/bin/sh
EOF
    chmod 744 $PREFIX/$lxc_rootfs_dir/etc/init.d/rcS

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/passwd
root:x:0:0:root:/root:/bin/false
EOF
    chmod 644 $PREFIX/$lxc_rootfs_dir/etc/passwd

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/group
root:x:0:root
EOF
    chmod 644 $PREFIX/$lxc_rootfs_dir/etc/group

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/shadow
root:!:15506:0:99999:7:::
EOF
    chmod 640 $PREFIX/$lxc_rootfs_dir/etc/shadow

}

# install busybox
install_busybox()
{
    # refer to Busybox Config File For LXC
    cp -r $PREFIX/home/stb/* $PREFIX/$lxc_rootfs_dir/
    cp -r $PREFIX/usr/sbin/init.lxc $PREFIX/$lxc_rootfs_dir/usr/sbin/
    cp -r $PREFIX/sbin/iptables $PREFIX/$lxc_rootfs_dir/sbin/
    cp -r $PREFIX/sbin/xtables-multi $PREFIX/$lxc_rootfs_dir/sbin/
}


install_app()
{
	# install our sample
	echo "install our sample application: $APP_NAME $APP_NAME2"
	cp -fr $SAMPLE_OUT_PATH/dvbplay/$APP_NAME $PREFIX/$lxc_rootfs_dir/home/
}

# create and deploy lxc config file for CA debug
install_lxc_dbg_config()
{
    cat <<EOF > $PREFIX/$lxc_config_file
lxc.utsname = $name

lxc.id_map = u 0 1000 10
lxc.id_map = g 0 1000 10

lxc.cap.keep = sys_admin net_raw net_admin setuid setgid chown sys_time

lxc.tty = 1
lxc.pts = 1
lxc.rootfs = $lxc_rootfs_dir
lxc.mount = $lxc_config_dir/fstab
lxc.pivotdir = /tmp/lxc_putold

lxc.mount.entry = /sys/power/state sys/power/state none rw,bind 0 0
lxc.mount.entry = shm dev/shm tmpfs rw,nosuid,nodev,noexec,mode=0660,create=dir 0 0
lxc.mount.entry = /dev/shm dev/shm none rw,bind 0 0

lxc.mount.entry = /dev/hi_adec dev/hi_adec none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_adsp dev/hi_adsp none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_aenc dev/hi_aenc none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_ao dev/hi_ao none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_ca dev/hi_ca none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_cipher dev/hi_cipher none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_demux dev/hi_demux none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_disp dev/hi_disp none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_gpio dev/hi_gpio none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_hdmi dev/hi_hdmi none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_i2c dev/hi_i2c none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_ir dev/hi_ir none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_keyled dev/hi_keyled none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_log dev/hi_log none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_mce dev/hi_mce none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_mem dev/hi_mem none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_module dev/hi_module none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_otp dev/hi_otp none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_pm dev/hi_pm none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_png dev/hi_png none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_pq dev/hi_pq none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_pvr dev/hi_pvr none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_sci dev/hi_sci none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_stat dev/hi_stat none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_svdec dev/hi_svdec none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_sync dev/hi_sync none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_sys dev/hi_sys none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_tde dev/hi_tde none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_tuner dev/hi_tuner none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_userproc dev/hi_userproc none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_vdec dev/hi_vdec none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_vo dev/hi_vo none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_vpss dev/hi_vpss none bind,optional,create=file 0 0
lxc.mount.entry = /dev/fb0 dev/fb0 none bind,optional,create=file 0 0
lxc.mount.entry = /dev/fb1 dev/fb0 none bind,optional,create=file 0 0
lxc.mount.entry = /dev/jpeg dev/jpeg none bind,optional,create=file 0 0

lxc.mount.entry = /dev/mmz_userdev dev/mmz_userdev none bind,optional,create=file 0 0
lxc.mount.entry = /dev/mem dev/mem none bind,optional,create=file 0 0
lxc.mount.entry = /dev/null dev/null none bind,optional,create=file 0 0
lxc.mount.entry = /dev/urandom dev/urandom none bind,optional,create=file 0 0
lxc.mount.entry = /dev/watchdog dev/watchdog none bind,optional,create=file 0 0

lxc.network.type = veth
lxc.network.flags = up
lxc.network.link = br0
lxc.network.hwaddr = 4a:49:43:49:79:bf
lxc.network.ipv4 = 192.168.1.2/24
lxc.network.name = eth1
#lxc.network.ipv4.gateway = 192.168.1.1

#config devcies access
lxc.cgroup.devices.deny = a

# /dev/null and zero
lxc.cgroup.devices.allow = c 1:3 rwm
lxc.cgroup.devices.allow = c 1:5 rwm
# consoles
lxc.cgroup.devices.allow = c 5:1 rwm
lxc.cgroup.devices.allow = c 5:0 rwm
lxc.cgroup.devices.allow = c 4:0 rwm
lxc.cgroup.devices.allow = c 4:1 rwm
# /dev/{,u}random
lxc.cgroup.devices.allow = c 1:9 rwm
lxc.cgroup.devices.allow = c 1:8 rwm
lxc.cgroup.devices.allow = c 136:* rwm
lxc.cgroup.devices.allow = c 5:2 rwm
# hi_*
lxc.cgroup.devices.allow = c 218:* rwm
# fb8
lxc.cgroup.devices.allow = c 29:* rwm
# others
lxc.cgroup.devices.allow = c 10:* rwm
EOF

    chmod 644 $PREFIX/usr/var/lib/lxc/$name/config

    cat <<EOF > $PREFIX/$lxc_config_dir/fstab
proc            /home/$name/proc           proc    defaults        0       0
sysfs           /home/$name/sys            sysfs   defaults        0       0
tmp             /home/$name/tmp            tmpfs   nosuid,noexec,nodev,mode=1770        0       0
dev             /home/$name/dev            tmpfs   nosuid,noexec,nodev,mode=0770        0       0
EOF
    chmod 644 $PREFIX/$lxc_config_dir/fstab

}

# create and deploy lxc config file for CA release
install_lxc_rel_config()
{
    cat <<EOF > $PREFIX/$lxc_config_file
lxc.utsname = $name

#lxc.id_map = u 0 1000 10
#lxc.id_map = g 0 1000 10

lxc.cap.keep = sys_admin net_raw net_admin sys_time setuid setgid chown

lxc.rootfs = $lxc_rootfs_dir
lxc.mount = $lxc_config_dir/fstab
lxc.pivotdir = /tmp/lxc_putold

lxc.mount.entry = /sys/power/state sys/power/state none rw,bind 0 0
lxc.mount.entry = shm dev/shm tmpfs rw,nosuid,nodev,noexec,mode=0660,create=dir 0 0
lxc.mount.entry = /dev/shm dev/shm none rw,bind 0 0

lxc.mount.entry = /dev/hi_adec dev/hi_adec none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_adsp dev/hi_adsp none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_aenc dev/hi_aenc none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_ao dev/hi_ao none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_ca dev/hi_ca none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_cipher dev/hi_cipher none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_demux dev/hi_demux none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_disp dev/hi_disp none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_gpio dev/hi_gpio none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_hdmi dev/hi_hdmi none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_i2c dev/hi_i2c none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_ir dev/hi_ir none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_keyled dev/hi_keyled none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_log dev/hi_log none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_mce dev/hi_mce none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_mem dev/hi_mem none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_module dev/hi_module none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_otp dev/hi_otp none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_pm dev/hi_pm none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_png dev/hi_png none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_pq dev/hi_pq none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_pvr dev/hi_pvr none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_sci dev/hi_sci none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_stat dev/hi_stat none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_svdec dev/hi_svdec none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_sync dev/hi_sync none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_sys dev/hi_sys none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_tde dev/hi_tde none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_tuner dev/hi_tuner none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_userproc dev/hi_userproc none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_vdec dev/hi_vdec none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_vo dev/hi_vo none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_vpss dev/hi_vpss none bind,optional,create=file 0 0
lxc.mount.entry = /dev/fb0 dev/fb0 none bind,optional,create=file 0 0
lxc.mount.entry = /dev/fb1 dev/fb0 none bind,optional,create=file 0 0
lxc.mount.entry = /dev/jpeg dev/jpeg none bind,optional,create=file 0 0

lxc.mount.entry = /dev/mmz_userdev dev/mmz_userdev none bind,optional,create=file 0 0
lxc.mount.entry = /dev/mem dev/mem none bind,optional,create=file 0 0
lxc.mount.entry = /dev/null dev/null none bind,optional,create=file 0 0
lxc.mount.entry = /dev/urandom dev/urandom none bind,optional,create=file 0 0
lxc.mount.entry = /dev/watchdog dev/watchdog none bind,optional,create=file 0 0

lxc.network.type = veth
lxc.network.link = br0
lxc.network.hwaddr = 4a:49:43:49:79:bf
lxc.network.ipv4 = 192.168.1.2/24
lxc.network.name = eth1
#lxc.network.ipv4.gateway = 192.168.1.1
lxc.network.flags = up

lxc.cgroup.devices.deny = a
# /dev/null and zero
lxc.cgroup.devices.allow = c 1:3 rwm
lxc.cgroup.devices.allow = c 1:5 rwm
# consoles
lxc.cgroup.devices.allow = c 5:1 rwm
lxc.cgroup.devices.allow = c 5:0 rwm
lxc.cgroup.devices.allow = c 4:0 rwm
lxc.cgroup.devices.allow = c 4:1 rwm
# /dev/{,u}random
lxc.cgroup.devices.allow = c 1:9 rwm
lxc.cgroup.devices.allow = c 1:8 rwm
lxc.cgroup.devices.allow = c 136:* rwm
lxc.cgroup.devices.allow = c 5:2 rwm
# hi_*
lxc.cgroup.devices.allow = c 218:* rwm
# fb8
lxc.cgroup.devices.allow = c 29:* rwm
# others
lxc.cgroup.devices.allow = c 10:* rwm
EOF

    chmod 644 $PREFIX/usr/var/lib/lxc/$name/config

    cat <<EOF > $PREFIX/$lxc_config_dir/fstab
proc            /home/$name/proc           proc    defaults        0       0
sysfs           /home/$name/sys            sysfs   defaults        0       0
tmp             /home/$name/tmp            tmpfs   nosuid,noexec,nodev,mode=1770        0       0
dev             /home/$name/dev            tmpfs   nosuid,noexec,nodev,gid=1000,mode=0770        0       0
EOF
    chmod 644 $PREFIX/$lxc_config_dir/fstab

}

##################################################################################

lxc_config_dir=/usr/var/lib/lxc/$name
lxc_config_file=$lxc_config_dir/config
lxc_rootfs_dir=/home/$name

install_fs_dir
install_busybox
install_app

if [ $LXC_MODE == "DEBUG" ]; then
	install_dbg_fs_scripts
	install_lxc_dbg_config
else
	install_rel_fs_scripts
	install_lxc_rel_config
fi

