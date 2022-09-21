#!/bin/bash

QT_LOCAL_PATH=`pwd`
export SDK_DIR=$QT_LOCAL_PATH/../../..

#qtÑ¹Ëõ°üÂ·¾¶
export QT_ORIGIN_PATH=$SDK_DIR/third_party/open_source

export QT_PRE_PATH=qt-everywhere-opensource-src-5.5.1
export BUILDER_PATH=$SDK_DIR/tools/linux/toolchains/arm-histbv310-linux/target
export SYSTEM_ROOT=$BUILDER_PATH
export CROSS=arm-histbv310-linux
export BUILDER_LIB_PATH=$BUILDER_PATH/lib
#export SHARE_LIB_PATH=$SDK_DIR/out/hi3798cv200/hi3798cv2dmo/lib/share
export SHARE_LIB_PATH=$HI_SHARED_LIB_DIR
export QT_EXT_GZ=tar.gz
export QT_SOURCE=$SDK_DIR/source/component/qt
export QT_PATCH_PATH=$QT_SOURCE/qtpatches
export HISI_SDK_ROOTFS=$HI_SHARED_LIB_DIR/../../rootfs
export ROOTFS_QT_ROOT=$HISI_SDK_ROOTFS/usr/lib/qt
export GRAPHICS_DEVICE=linuxfb

#$1:pkg name
func_patch_pkg()
{
    if [ -d $QT_PATCH_PATH/$1 ] ;then
        cp -af $QT_PATCH_PATH/$1/* $QT_SOURCE/$1
        if [ $? != 0 ] ;then
            echo "patch $1 failed!"
			cd $QT_SOURCE
            return 1;
        fi
    else
        echo "$1 no patch."
    fi
	
	echo "patch $1 end"
	cd $QT_SOURCE
    return 0;
}

#$1:pkg name
func_prepare_pkg()
{
    echo "prepare $1 begin..."
	if [ -d $1 ] ;then
		rm -rf $1
	else
		mkdir -p $1
	fi
	
	tar -xf $QT_ORIGIN_PATH/$1.$QT_EXT_GZ -C $QT_SOURCE
	if [ $? != 0 ];then
		echo "tar $1.$QT_EXT_GZ failed!"
		cd $QT_SOURCE
		return 1
	fi  
               
	func_patch_pkg $1
	if [ $? != 0 ];then
		echo "patch $1 failed!"
		cd $QT_SOURCE
		return 1
	fi            
    
    echo "prepare $1 end"
    cd $QT_SOURCE
    return 0
}

#$1:pkg name
func_make_pkg()
{
    cd $QT_SOURCE/$1
    make uninstall

	cd $QT_SOURCE/$1/qtwebkit
	../qtbase/bin/qmake
	cd -
	make -j
	if [ $? != 0 ] ;then
		echo "make $1 failed!"
		cd $QT_SOURCE
		return 1;
	fi
	
	cd $QT_SOURCE/$1
	make -j install
	if [ $? != 0 ] ;then
		echo "make install $1 failed!"
		cd $QT_SOURCE
		return 1;
	fi
    
    cd $QT_SOURCE
	return 0;
}

func_make_browser()
{
	cd $QT_SOURCE/$1/qtwebkit-examples/examples/webkitwidgets/browser/
	$QT_SOURCE/$1/qtbase/bin/qmake
	make -j
	make -j install
    return 0;
}

func_build_main()
{
	func_prepare_pkg $QT_PRE_PATH
    if [ $? != 0 ] ;then
        echo "func_prepare_pkg $QT_PRE_PATH failed!"
		cd $QT_SOURCE
        return 1;
    fi
	
	cd $QT_SOURCE/$QT_PRE_PATH
	chmod 777 configure
	./configure -opensource -release -silent -confirm-license -prefix /${QT_PRE_PATH}-${GRAPHICS_DEVICE}  \
		-no-dbus -make libs -nomake tools -qt-freetype -sysroot ${SYSTEM_ROOT} -platform linux-g++-64 -device linux-arm-hisilicon-${GRAPHICS_DEVICE} \
		-device-option CROSS_COMPILE=${BUILDER_PATH}/../bin/${CROSS}- -L${BUILDER_LIB_PATH} -c++11 -L${SHARE_LIB_PATH} \
		-skip qtandroidextras -skip qtmacextras -skip qtwinextras -skip qtdoc
	if [ $? != 0 ] ;then
		echo "configure $QT_PRE_PATH failed!"
		cd $QT_SOURCE
		return 1;
	fi
	
	cd $QT_SOURCE
	func_make_pkg $QT_PRE_PATH
    if [ $? != 0 ] ;then
        echo "func_make_pkg $QT_PRE_PATH failed!"
        cd $QT_SOURCE
        return 1;
    fi
	
	func_make_browser $QT_PRE_PATH
	if [ $? != 0 ] ;then
        echo "func_make_browser $QT_PRE_PATH failed!"
        cd $QT_SOURCE
        return 1;
    fi
	cd $QT_SOURCE
	return 0;
}

# install libs, plugins, browser to rootfs
func_install()
{
	mkdir -p $ROOTFS_QT_ROOT/bin
	cp -r $SYSTEM_ROOT/${QT_PRE_PATH}-${GRAPHICS_DEVICE}/lib $ROOTFS_QT_ROOT
	cp -r $SYSTEM_ROOT/${QT_PRE_PATH}-${GRAPHICS_DEVICE}/plugins $ROOTFS_QT_ROOT
	cp $SYSTEM_ROOT/${QT_PRE_PATH}-${GRAPHICS_DEVICE}/examples/webkitwidgets/browser/browser $ROOTFS_QT_ROOT/bin
	cp $QT_SOURCE/resources/hello.html $ROOTFS_QT_ROOT/bin
	cp $QT_SOURCE/resources/run_qt5.5_linuxfb $ROOTFS_QT_ROOT/bin
	rm -rf $ROOTFS_QT_ROOT/lib/cmake
	rm -rf $ROOTFS_QT_ROOT/lib/pkgconfig
	rm -f $ROOTFS_QT_ROOT/lib/*.a
	rm -f $ROOTFS_QT_ROOT/lib/*.la
	rm -f $ROOTFS_QT_ROOT/lib/*.prl
    return 0;
}

func_build_main
if [ $? = 0 ];then
	echo "----------------------------------------------"
	echo "  build Qt 5.5.1 ($GRAPHICS_DEVICE) successfully!"
	echo "----------------------------------------------"
	func_install
	echo "  installed to $ROOTFS_QT_ROOT"
fi
