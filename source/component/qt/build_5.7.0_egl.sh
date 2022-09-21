#!/bin/bash

QT_LOCAL_PATH=`pwd`
export SDK_DIR=$QT_LOCAL_PATH/../../..

export QT_PRE_PATH=qt-everywhere-opensource-src-5.7.0
export BUILDER_PATH=$SDK_DIR/tools/linux/toolchains/arm-histbv310-linux/target
export SYSTEM_ROOT=$BUILDER_PATH
export CROSS=arm-histbv310-linux
export BUILDER_LIB_PATH=$BUILDER_PATH/lib
#export SHARE_LIB_PATH=$SDK_DIR/out/hi3798cv200/hi3798cv2dmo/lib/share
export SHARE_LIB_PATH=$HI_SHARED_LIB_DIR
export QT_EXT_GZ=tar.gz
export QT_SOURCE=$SDK_DIR/source/component/qt
export QT_PATCH_PATH=$QT_SOURCE/qtpatches
export QT_OPEN_SOURCE_PATH=$SDK_DIR/third_party/open_source
export MY_INSTALL_PATH=$QT_SOURCE/out
export MY_THIRD_PATH=$MY_INSTALL_PATH/third_party
#BEGINE  由于目前我们的host的c++编译器版本低，需设置c++11版本编译器路径，如果host中已经有c++11可以不需要设置
#export HOST_C11_COMPILER=/home/<user>/gcc
#export PATH=$HOST_C11_COMPILER/build/bin:$PATH
#export LD_LIBRARY_PATH=$HOST_C11_COMPILER/build/lib64:$HOST_C11_COMPILER/build/lib32:$LD_LIBRARY_PATH
#END
export GRAPHICS_DEVICE=egl
export QMAKE_CONFIG_FILE=$QT_PATCH_PATH/qt-everywhere-opensource-src-5.7.0/qtbase/mkspecs/devices/linux-arm-hisilicon-${GRAPHICS_DEVICE}/qmake.conf
export HISI_SDK_ROOTFS=$HI_SHARED_LIB_DIR/../../rootfs
export ROOTFS_QT_ROOT=$HISI_SDK_ROOTFS/usr/lib/qt

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
	# modify qmake config path
	sed -i "s|QMAKE_INCDIR_EGL +=.*|QMAKE_INCDIR_EGL += $HI_INCLUDE_DIR|g" $QMAKE_CONFIG_FILE
	sed -i "s|QMAKE_LIBDIR_EGL +=.*|QMAKE_LIBDIR_EGL += $HI_SHARED_LIB_DIR|g" $QMAKE_CONFIG_FILE
	sed -i "s|QMAKE_INCDIR +=.*|QMAKE_INCDIR += $HI_SHARED_LIB_DIR/../../obj/source/component/freetype/release/include/freetype2 $MY_INSTALL_PATH/include|g" $QMAKE_CONFIG_FILE
    return 0;
}

#$1:pkg name
#$2:flag
func_prepare_pkg()
{
    echo "prepare $1 begin..."
	if [ x$2 != x"qt" ];then
		cd $MY_THIRD_PATH
	fi
	if [ -d $1 ] ;then
		rm -rf $1
	else
		mkdir -p $1
	fi
	
	if [ x$2 = x"qt" ];then
		tar -xf $QT_OPEN_SOURCE_PATH/$1.$QT_EXT_GZ -C $QT_SOURCE
	elif [ x$2 = x"tgz" ];then
		tar -xf $QT_OPEN_SOURCE_PATH/$1.tgz -C $MY_THIRD_PATH
	else
		tar -xf $QT_OPEN_SOURCE_PATH/$1.$QT_EXT_GZ -C $MY_THIRD_PATH
	fi
	if [ $? != 0 ];then
		echo "tar $1.$QT_EXT_GZ failed!"
		cd $QT_SOURCE
		return 1;
	fi

	func_patch_pkg $1
	if [ $? != 0 ];then
		echo "patch $1 failed!"
		cd $QT_SOURCE
		return 1;
	fi            
    
    echo "prepare $1 end"
    cd $QT_SOURCE
    return 0;
}

#$1:pkg name
func_make_pkg()
{
    cd $QT_SOURCE/$1
    make uninstall
	cd $QT_SOURCE/$1/qtwebengine
	../qtbase/bin/qmake
	cd -
	make -j 
	if [ $? != 0 ] ;then
		echo "make $1 failed!"
		cd $QT_SOURCE
		return 1;
	fi

	make -j install
	if [ $? != 0 ] ;then
		echo "make install $1 failed!"
		cd $QT_SOURCE
		return 1;
	fi

    cd $QT_SOURCE
	return 0;
}

#$1:pkg name
func_make_third_pkg()
{
	make -j
	if [ $? != 0 ] ;then
		echo "make $1 failed!"
		cd $QT_SOURCE
		return 1;
	fi
	make -j install
	if [ $? != 0 ] ;then
		echo "make install $1 failed!"
		cd $QT_SOURCE
		return 1;
	fi
	cd $MY_THIRD_PATH
	echo "make install $1 successfully!"
	return 0;
}

func_make_browser()
{
	cd $QT_SOURCE/$1/qtwebview/examples/webview/minibrowser/
	$QT_SOURCE/$1/qtbase/bin/qmake
	make -j
	make -j install
	return 0;
}

func_build_main()
{
	#1、编译依赖包expat-2.1.0
	func_prepare_pkg expat-2.1.0 "third"
    if [ $? != 0 ] ;then
        echo "func_prepare_pkg expat-2.1.0 failed!"
		cd $QT_SOURCE
        return 1;
    fi
	
	cd $MY_THIRD_PATH/expat-2.1.0
	chmod 777 configure
	./configure --host=arm-histbv310-linux --prefix=$MY_INSTALL_PATH --enable-shared
	if [ $? != 0 ] ;then
		echo "configure expat-2.1.0 failed!"
		cd $QT_SOURCE
		return 1;
	fi
	
	func_make_third_pkg expat-2.1.0
    if [ $? != 0 ] ;then
        echo "func_make_pkg expat-2.1.0 failed!"
        cd $QT_SOURCE
        return 1;
    fi

	#2、编译依赖包dbus-1.11.4
	export PKG_CONFIG_LIBDIR=/none
	unset PKG_CONFIG_PATH

	func_prepare_pkg dbus-1.11.4 "third"
    if [ $? != 0 ] ;then
        echo "func_prepare_pkg dbus-1.11.4 failed!"
		cd $QT_SOURCE
        return 1;
    fi
	
	cd $MY_THIRD_PATH/dbus-1.11.4
	chmod 777 configure
	CC=arm-histbv310-linux-gcc CXX=arm-histbv310-linux-g++ CFLAGS="-Wcast-align -g -O2 -I$MY_INSTALL_PATH/include" \
	CXXFLAGS=${CFLAGS} LDFLAGS+="-L$MY_INSTALL_PATH/lib -lexpat" ./configure --host=arm-histbv310-linux --prefix=$MY_INSTALL_PATH --enable-shared
	if [ $? != 0 ] ;then
		echo "configure dbus-1.11.4 failed!"
		cd $QT_SOURCE
		return 1;
	fi
	
	func_make_third_pkg dbus-1.11.4
    if [ $? != 0 ] ;then
        echo "func_make_pkg dbus-1.11.4 failed!"
        cd $QT_SOURCE
        return 1;
    fi
	
	#3、编译依赖包fontconfig-2.12.0
	func_prepare_pkg fontconfig-2.12.0 "third"
    if [ $? != 0 ] ;then
        echo "func_prepare_pkg fontconfig-2.12.0 failed!"
		cd $QT_SOURCE
        return 1;
    fi
	
	cd $MY_THIRD_PATH/fontconfig-2.12.0
	chmod 777 configure
	FREETYPE_CFLAGS="-I$SHARE_LIB_PATH/../../include/freetype2/freetype -I$SHARE_LIB_PATH/../../include/freetype2" FREETYPE_LIBS="-L$SHARE_LIB_PATH -lfreetype" FREETYPE_CPPFLAGS=$FREETYPE_CFLAGS \
	./configure --host=arm-histbv310-linux --prefix=$MY_INSTALL_PATH --enable-shared --with-expat-includes=$MY_INSTALL_PATH/include \
	--with-expat-lib=$MY_INSTALL_PATH/lib
	if [ $? != 0 ] ;then
		echo "configure fontconfig-2.12.0 failed!"
		cd $QT_SOURCE
		return 1;
	fi
	
	func_make_third_pkg fontconfig-2.12.0
    if [ $? != 0 ] ;then
        echo "func_make_pkg fontconfig-2.12.0 failed!"
        cd $QT_SOURCE
        return 1;
    fi
	
	#4、编译依赖包icu4c-54_1-src
	func_prepare_pkg icu4c-54_1-src "tgz"
    if [ $? != 0 ] ;then
        echo "func_prepare_pkg icu4c-54_1-src failed!"
		cd $QT_SOURCE
        return 1;
    fi
	
	cd $MY_THIRD_PATH/icu/source
	CC=arm-histbv310-linux-gcc CXX=arm-histbv310-linux-g++ ./runConfigureICU Linux/gcc
	make -j
	make clean
	
	chmod 777 configure
	./configure --host=arm-histbv310-linux --prefix=$MY_INSTALL_PATH --disable-samples --disable-tests --with-cross-build=$(pwd) \
	--with-data-packaging=archive --enable-samples=no --enable-tests=no --enable-extras=no
	if [ $? != 0 ] ;then
		echo "configure icu4c-54_1-src failed!"
		cd $QT_SOURCE
		return 1;
	fi
	
	make -j
	make -j install
	cd $QT_SOURCE
	
	#5、编译qt
	
	func_prepare_pkg $QT_PRE_PATH "qt"
    if [ $? != 0 ] ;then
        echo "func_prepare_pkg $QT_PRE_PATH failed!"
		cd $QT_SOURCE
        return 1;
    fi
	
	cd $QT_SOURCE/$QT_PRE_PATH
	chmod 777 configure
	./configure -silent -no-icu -no-iconv -I${SDK_DIR}/out/hi3798cv200/hi3798cv2dmo/include/freetype2 \
	-I${MY_INSTALL_PATH}/include -L${MY_INSTALL_PATH}/lib -pkg-config -fontconfig -opensource -release  -confirm-license \
	-prefix /${QT_PRE_PATH}-${GRAPHICS_DEVICE} -D EGL_FBDEV -eglfs -opengl es2 -no-dbus -make libs -nomake tools -qt-zlib -qt-freetype \
	-sysroot ${SYSTEM_ROOT} -platform linux-g++-64 -device linux-arm-hisilicon-${GRAPHICS_DEVICE} \
	-device-option CROSS_COMPILE=${BUILDER_PATH}/../bin/${CROSS}- -L${BUILDER_LIB_PATH} -c++std c++11 \
	-L${SHARE_LIB_PATH} -skip qtandroidextras -skip qtmacextras -skip qtwinextras -skip qtdoc
	if [ $? != 0 ] ;then
		echo "configure $QT_PRE_PATH failed!"
		cd $QT_SOURCE
		return 1;
	fi
	
	export PKG_CONFIG_LIBDIR=/none
	export PKG_CONFIG_PATH=$MY_INSTALL_PATH/lib/pkgconfig:/usr/local/lib/pkgconfig:/usr/lib/pkgconfig:/usr/lib/x86_64-linux-gnu/pkgconfig
	
	mkdir -p qtwebengine/lib
	cp $SHARE_LIB_PATH/../../obj/source/component/freetype/freetype-2.7/builds/unix/freetype2.pc $MY_INSTALL_PATH/lib/pkgconfig
	cp -rf $SHARE_LIB_PATH/* qtwebengine/lib/
	cp -rf $MY_INSTALL_PATH/lib/* qtwebengine/lib/
	
	cd $QT_SOURCE
	func_make_pkg $QT_PRE_PATH
    if [ $? != 0 ] ;then
        echo "func_make_pkg $QT_PRE_PATH failed!"
        #cd $QT_SOURCE
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
	cp -r $SYSTEM_ROOT/${QT_PRE_PATH}-${GRAPHICS_DEVICE}/libexec $ROOTFS_QT_ROOT
	cp -r $SYSTEM_ROOT/${QT_PRE_PATH}-${GRAPHICS_DEVICE}/resources $ROOTFS_QT_ROOT
	cp -r $SYSTEM_ROOT/${QT_PRE_PATH}-${GRAPHICS_DEVICE}/qml $ROOTFS_QT_ROOT
	cp -r $SYSTEM_ROOT/${QT_PRE_PATH}-${GRAPHICS_DEVICE}/translations $ROOTFS_QT_ROOT
# dependent libs
	cp -r $MY_INSTALL_PATH/lib $ROOTFS_QT_ROOT
# browser
	cp -r $SYSTEM_ROOT/${QT_PRE_PATH}-${GRAPHICS_DEVICE}/examples/webview/minibrowser/ $ROOTFS_QT_ROOT/bin
	cp $QT_SOURCE/resources/hello.html $ROOTFS_QT_ROOT/bin/minibrowser/
	cp -r $QT_SOURCE/resources/webgl $ROOTFS_QT_ROOT/bin/minibrowser/
	cp $QT_SOURCE/resources/run_qt5.7_egl $ROOTFS_QT_ROOT/bin
# config file, fonts
	cp $QT_SOURCE/resources/qt.conf $ROOTFS_QT_ROOT/libexec
	cp $QT_SOURCE/resources/qt.conf $ROOTFS_QT_ROOT/bin/minibrowser/
	mkdir -p $ROOTFS_QT_ROOT/lib/fonts
	cp $QT_SOURCE/resources/fonts.conf $ROOTFS_QT_ROOT/lib/fonts
	cp $QT_SOURCE/$QT_PRE_PATH/qtquickcontrols/examples/quickcontrols/extras/dashboard/fonts/DejaVuSans.ttf $ROOTFS_QT_ROOT/lib/fonts/
# remove useless files
	rm -rf $ROOTFS_QT_ROOT/lib/cmake
	rm -rf $ROOTFS_QT_ROOT/lib/dbus-1.0
	rm -rf $ROOTFS_QT_ROOT/lib/icu
	rm -rf $ROOTFS_QT_ROOT/lib/pkgconfig
	rm -f $ROOTFS_QT_ROOT/lib/*.a
	rm -f $ROOTFS_QT_ROOT/lib/*.la
	rm -f $ROOTFS_QT_ROOT/lib/*.prl
    return 0;
}

if [ -d $QT_SOURCE/out ];then
	rm -rf $QT_SOURCE/out
fi
mkdir -p out/third_party
func_build_main
if [ $? = 0 ];then
	echo "----------------------------------------------"
	echo "  build Qt 5.7.0 ($GRAPHICS_DEVICE) successfully!"
	echo "----------------------------------------------"
	func_install
	echo "  installed to $ROOTFS_QT_ROOT"
fi
