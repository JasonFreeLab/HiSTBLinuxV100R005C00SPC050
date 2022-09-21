################################################################################
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

HOST            := $(CFG_HI_ARM_TOOLCHAINS_NAME)
CROSS_COMPILE   := $(HOST)-
STRIP           := $(CROSS_COMPILE)strip
QT_NAME         := qt-everywhere-opensource-src

ifeq ($(HI_USER_SPACE_LIB),y)
QT_DIR := $(HI_OUT_DIR)/obj/source/component/qt
QT_INSTALL_DIR := $(HI_EXTERN_LIB_DIR)/qt
FREETYPE_DIR := $(HI_OUT_DIR)/obj/source/component/freetype
endif

QT_VER := 5.5.1
ifeq ($(CFG_HI_QT_VERSION_5.7.0),y)
QT_VER = 5.7.0
endif

ifeq ($(CFG_HI_QT_LINUXFB_SUPPORT),y)
GRAPHICS_DEVICE := linuxfb
endif

ifeq ($(CFG_HI_QT_EGL_SUPPORT),y)
GRAPHICS_DEVICE := egl
endif

QT = $(QT_NAME)-$(QT_VER)
BUILDER_PATH := $(SDK_DIR)/tools/linux/toolchains/$(CFG_HI_ARM_TOOLCHAINS_NAME)/target
SYSTEM_ROOT := $(BUILDER_PATH)
BUILDER_LIB_PATH := $(BUILDER_PATH)/lib
QMAKE_CONFIG_FILE := $(QT_DIR)/$(QT)/qtbase/mkspecs/devices/linux-arm-hisilicon-$(GRAPHICS_DEVICE)/qmake.conf

THIRD_INSTALL_PATH := $(QT_DIR)/third_install
THIRD_PATH := $(QT_DIR)/tmp
EXPAT_NAME := expat-2.1.0
DBUS_NAME := dbus-1.11.4
FONTCONFIG_NAME := fontconfig-2.12.0
ICU_NAME := icu4c-54_1-src

################################################################################
.PHONY: all clean
################################################################################

all: build_qt
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)test -d $(QT_INSTALL_DIR)/bin || mkdir -p $(QT_INSTALL_DIR)/bin
	$(AT)cp -ralf $(SYSTEM_ROOT)/$(QT)-$(GRAPHICS_DEVICE)/lib $(QT_INSTALL_DIR)
	$(AT)cp -ralf $(SYSTEM_ROOT)/$(QT)-$(GRAPHICS_DEVICE)/plugins $(QT_INSTALL_DIR)

ifeq ($(CFG_HI_QT_VERSION_5.5.1),y)
	$(AT)cp -ralf $(SYSTEM_ROOT)/$(QT)-$(GRAPHICS_DEVICE)/examples/webkitwidgets/browser/browser $(QT_INSTALL_DIR)/bin
	$(AT)cp -ralf $(COMPONENT_DIR)/qt/resources/hello.html $(QT_INSTALL_DIR)/bin
	$(AT)cp -ralf $(COMPONENT_DIR)/qt/resources/run_qt5.5_$(GRAPHICS_DEVICE) $(QT_INSTALL_DIR)/bin
ifeq ($(CFG_HI_QT_EGL_SUPPORT),y)
	$(AT)cp -ralf $(COMPONENT_DIR)/qt/resources/webgl $(QT_INSTALL_DIR)/bin
endif
endif #### 5.5.1

ifeq ($(CFG_HI_QT_VERSION_5.7.0),y)
	$(AT)test -d $(QT_INSTALL_DIR)/lib/fonts || mkdir -p $(QT_INSTALL_DIR)/lib/fonts
	$(AT)cp $(QT_DIR)/$(QT)/qtquickcontrols/examples/quickcontrols/extras/dashboard/fonts/DejaVuSans.ttf $(QT_INSTALL_DIR)/lib/fonts/
	$(AT)cp -ralf $(COMPONENT_DIR)/qt/resources/run_qt5.7_$(GRAPHICS_DEVICE) $(QT_INSTALL_DIR)/bin
ifeq ($(CFG_HI_QT_LINUXFB_SUPPORT),y)
	$(AT)cp -ralf $(SYSTEM_ROOT)/$(QT)-$(GRAPHICS_DEVICE)/examples/widgets/widgets/analogclock/analogclock $(QT_INSTALL_DIR)/bin
endif
ifeq ($(CFG_HI_QT_EGL_SUPPORT),y)
	$(AT)cp -ralf $(SYSTEM_ROOT)/$(QT)-$(GRAPHICS_DEVICE)/libexec      $(QT_INSTALL_DIR)
	$(AT)cp -ralf $(SYSTEM_ROOT)/$(QT)-$(GRAPHICS_DEVICE)/resources    $(QT_INSTALL_DIR)
	$(AT)cp -ralf $(SYSTEM_ROOT)/$(QT)-$(GRAPHICS_DEVICE)/qml          $(QT_INSTALL_DIR)
	$(AT)cp -ralf $(SYSTEM_ROOT)/$(QT)-$(GRAPHICS_DEVICE)/translations $(QT_INSTALL_DIR)

	# dependent libs
	$(AT)cp -ralf $(THIRD_INSTALL_PATH)/lib $(QT_INSTALL_DIR)
	# browser
	$(AT)cp -ralf $(SYSTEM_ROOT)/$(QT)-$(GRAPHICS_DEVICE)/examples/webview/minibrowser/  $(QT_INSTALL_DIR)/bin
	$(AT)cp $(COMPONENT_DIR)/qt/resources/hello.html                                     $(QT_INSTALL_DIR)/bin/minibrowser/
	$(AT)cp -ralf $(COMPONENT_DIR)/qt/resources/webgl                                    $(QT_INSTALL_DIR)/bin/minibrowser/
	# config file, fonts
	$(AT)cp $(COMPONENT_DIR)/qt/resources/qt.conf $(QT_INSTALL_DIR)/libexec
	$(AT)cp $(COMPONENT_DIR)/qt/resources/qt.conf $(QT_INSTALL_DIR)/bin/minibrowser/
	$(AT)rm -rf $(QT_INSTALL_DIR)/lib/dbus-1.0
	$(AT)rm -rf $(QT_INSTALL_DIR)/lib/rcu
endif
endif ####5.7.0
	$(AT)rm -rf $(QT_INSTALL_DIR)/lib/cmake
	$(AT)rm -rf $(QT_INSTALL_DIR)/lib/pkgconfig
	$(AT)rm -rf $(QT_INSTALL_DIR)/lib/*.a
	$(AT)rm -rf $(QT_INSTALL_DIR)/lib/*.la
	$(AT)rm -rf $(QT_INSTALL_DIR)/lib/*.prl
endif  #### HI_USER_SPACE_LIB

ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)test -d $(QT_INSTALL_DIR64)/bin || mkdir -p $(QT_INSTALL_DIR64)/bin
	$(AT)cp -ralf $(SYSTEM_ROOT)/$(QT)-$(GRAPHICS_DEVICE)/lib $(QT_INSTALL_DIR64)
	$(AT)cp -ralf $(SYSTEM_ROOT)/$(QT)-$(GRAPHICS_DEVICE)/plugins $(QT_INSTALL_DIR64)
ifeq ($(CFG_HI_QT_VERSION_5.5.1),y)
	$(AT)cp -ralf $(SYSTEM_ROOT)/$(QT)-$(GRAPHICS_DEVICE)/examples/webkitwidgets/browser/browser $(QT_INSTALL_DIR64)/bin
	$(AT)cp -ralf $(COMPONENT_DIR)/qt/resources/hello.html $(QT_INSTALL_DIR64)/bin
	$(AT)cp -ralf $(COMPONENT_DIR)/qt/resources/run_qt5.5_$(GRAPHICS_DEVICE) $(QT_INSTALL_DIR64)/bin
endif
ifeq ($(CFG_HI_QT_VERSION_5.7.0),y)
	$(AT)cp -ralf $(SYSTEM_ROOT)/$(QT)-$(GRAPHICS_DEVICE)/examples/widgets/widgets/analogclock/analogclock $(QT_INSTALL_DIR64)/bin
	$(AT)test -d $(QT_INSTALL_DIR64)/lib/fonts || mkdir -p $(QT_INSTALL_DIR64)/lib/fonts
	$(AT)cp $(QT_DIR64)/$(QT)/qtquickcontrols/examples/quickcontrols/extras/dashboard/fonts/DejaVuSans.ttf $(QT_INSTALL_DIR64)/lib/fonts/
	$(AT)cp -ralf $(COMPONENT_DIR)/qt/resources/run_qt5.7_$(GRAPHICS_DEVICE) $(QT_INSTALL_DIR64)/bin
endif
ifeq ($(CFG_HI_QT_EGL_SUPPORT),y)
	$(AT)cp -ralf $(COMPONENT_DIR)/qt/resources/webgl $(QT_INSTALL_DIR64)/bin
endif
	$(AT)rm -rf $(QT_INSTALL_DIR64)/lib/cmake
	$(AT)rm -rf $(QT_INSTALL_DIR64)/lib/pkgconfig
	$(AT)rm -rf $(QT_INSTALL_DIR64)/lib/*.la
	$(AT)rm -rf $(QT_INSTALL_DIR64)/lib/*.prl
endif  #### HI_USER_SPACE_LIB64

clean:
ifeq ($(CFG_HI_QT_SUPPORT),y)
ifeq ($(CFG_HI_CPU_ARCH),arm64)
	$(AT)rm -rf $(HI_OUT_DIR)/obj64/source/component/qt
	$(AT)rm -rf $(HI_EXTERN_LIB64_DIR)/bin/browser
	$(AT)rm -rf $(HI_EXTERN_LIB64_DIR)/bin/hello.html
	$(AT)rm -rf $(HI_EXTERN_LIB64_DIR)/bin/run_qt*
else
	$(AT)rm -rf $(HI_OUT_DIR)/obj/source/component/qt
	$(AT)rm -rf $(HI_EXTERN_LIB_DIR)/bin/browser
	$(AT)rm -rf $(HI_EXTERN_LIB_DIR)/bin/hello.html
	$(AT)rm -rf $(HI_EXTERN_LIB_DIR)/bin/run_qt*
endif
endif

build_qt:
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)test -d $(QT_INSTALL_DIR) || mkdir -p $(QT_INSTALL_DIR)
	$(AT)test -d $(QT_DIR) || mkdir -p $(QT_DIR)
	$(info "---->Now compile Qt version:$(QT) for $(GRAPHICS_DEVICE)")
	$(AT)test -d $(QT_DIR)/$(QT) || tar xf $(OPEN_SOURCE_DIR)/$(QT).tar.gz -C $(QT_DIR)

ifeq ($(CFG_HI_QT_LINUXFB_SUPPORT),y)  #### linuxfb
	#patch
	cp $(COMPONENT_DIR)/qt/qtpatches/$(QT)/* -drf $(QT_DIR)/$(QT)

ifeq ($(CFG_HI_QT_VERSION_5.5.1),y)
	cd $(QT_DIR)/$(QT) && \
	./configure -opensource -release -silent -confirm-license -prefix /$(QT)-$(GRAPHICS_DEVICE)  \
		-no-dbus -make libs -nomake tools -qt-freetype -sysroot $(SYSTEM_ROOT) -platform linux-g++-64 -device linux-arm-hisilicon-$(GRAPHICS_DEVICE) \
		-device-option CROSS_COMPILE=$(BUILDER_PATH)/../bin/$(CFG_HI_ARM_TOOLCHAINS_NAME)- -L$(BUILDER_LIB_PATH) -c++11 \
		-L$(HI_SHARED_LIB_DIR) -skip qtandroidextras -skip qtmacextras -skip qtwinextras -skip qtdoc

	cd $(QT_DIR)/$(QT); make uninstall
	cd $(QT_DIR)/$(QT)/qtwebkit; ../qtbase/bin/qmake

	cd $(QT_DIR)/$(QT); make -j; make install

	cd $(QT_DIR)/$(QT)/qtwebkit-examples/examples/webkitwidgets/browser && $(QT_DIR)/$(QT)/qtbase/bin/qmake; make -j; make install
endif #### 5.5.1

ifeq ($(CFG_HI_QT_VERSION_5.7.0),y)
	cd $(QT_DIR)/$(QT) && \
	./configure -opensource -release -silent -no-pkg-config -confirm-license -prefix /$(QT)-$(GRAPHICS_DEVICE)  \
		-no-dbus -make libs -nomake tools -qt-freetype -sysroot $(SYSTEM_ROOT) -platform linux-g++-64 -device linux-arm-hisilicon-$(GRAPHICS_DEVICE) \
		-device-option CROSS_COMPILE=$(BUILDER_PATH)/../bin/$(CFG_HI_ARM_TOOLCHAINS_NAME)- -L$(BUILDER_LIB_PATH) -c++std c++11 \
		-L$(HI_SHARED_LIB_DIR) -skip qtandroidextras -skip qtmacextras -skip qtwinextras -skip qtdoc -skip qtvirtualkeyboard

	cd $(QT_DIR)/$(QT); make uninstall
	cd $(QT_DIR)/$(QT)/qtwebengine; ../qtbase/bin/qmake

	cd $(QT_DIR)/$(QT); make -j; make install

	cd $(QT_DIR)/$(QT)/qtbase/examples/widgets/widgets/analogclock/ && $(QT_DIR)/$(QT)/qtbase/bin/qmake; make -j; make install
endif #### 5.7.0
endif #### linuxfb

ifeq ($(CFG_HI_QT_EGL_SUPPORT),y)  #### egl
ifeq ($(CFG_HI_QT_VERSION_5.5.1),y)
	cp $(COMPONENT_DIR)/qt/qtpatches/$(QT)/* -drf $(QT_DIR)/$(QT)
	sed -i "s|QMAKE_INCDIR_EGL +=.*|QMAKE_INCDIR_EGL += $(HI_INCLUDE_DIR)|g" $(QMAKE_CONFIG_FILE)
	sed -i "s|QMAKE_LIBDIR_EGL +=.*|QMAKE_LIBDIR_EGL += $(HI_SHARED_LIB_DIR)|g" $(QMAKE_CONFIG_FILE)

	cd $(QT_DIR)/$(QT) && \
	./configure -opensource -release -silent -confirm-license -prefix /$(QT)-$(GRAPHICS_DEVICE)  \
		-no-dbus -make libs -nomake tools -qt-freetype -sysroot $(SYSTEM_ROOT) -platform linux-g++-64 -device linux-arm-hisilicon-$(GRAPHICS_DEVICE) \
		-device-option CROSS_COMPILE=$(BUILDER_PATH)/../bin/$(CFG_HI_ARM_TOOLCHAINS_NAME)- -L$(BUILDER_LIB_PATH) -c++11 \
		-L$(HI_SHARED_LIB_DIR) -skip qtandroidextras -skip qtmacextras -skip qtwinextras -skip qtdoc -D EGL_FBDEV -eglfs -opengl es2

	cd $(QT_DIR)/$(QT); make uninstall
	cd $(QT_DIR)/$(QT)/qtwebkit; ../qtbase/bin/qmake

	cd $(QT_DIR)/$(QT); make -j; make install

	cd $(QT_DIR)/$(QT)/qtwebkit-examples/examples/webkitwidgets/browser && $(QT_DIR)/$(QT)/qtbase/bin/qmake; make -j; make install
endif #### 5.5.1

ifeq ($(CFG_HI_QT_VERSION_5.7.0),y)
	cp $(COMPONENT_DIR)/qt/qtpatches/$(QT)/* -drf $(QT_DIR)/$(QT)
	sed -i "s|QMAKE_INCDIR_EGL +=.*|QMAKE_INCDIR_EGL += $(HI_INCLUDE_DIR)|g" $(QMAKE_CONFIG_FILE)
	sed -i "s|QMAKE_LIBDIR_EGL +=.*|QMAKE_LIBDIR_EGL += $(HI_SHARED_LIB_DIR)|g" $(QMAKE_CONFIG_FILE)
	sed -i "s|QMAKE_INCDIR +=.*|QMAKE_INCDIR += $(FREETYPE_DIR)/release/include/freetype2/freetype $(THIRD_INSTALL_PATH)/include|g" $(QMAKE_CONFIG_FILE)

	make build_qt_depend
	cd $(QT_DIR)/$(QT) && \
	./configure -silent -no-icu -no-iconv -I$(HI_INCLUDE_DIR) -I$(HI_INCLUDE_DIR)/freetype2 -I$(THIRD_INSTALL_PATH)/include \
	-L$(THIRD_INSTALL_PATH)/lib -pkg-config -fontconfig -opensource -release  -confirm-license -no-glib \
	-prefix /$(QT)-$(GRAPHICS_DEVICE) -D EGL_FBDEV -eglfs -opengl es2 -no-dbus -make libs -nomake tools -qt-zlib -qt-freetype \
	-sysroot $(SYSTEM_ROOT) -platform linux-g++-64 -device linux-arm-hisilicon-$(GRAPHICS_DEVICE) \
	-device-option CROSS_COMPILE=$(BUILDER_PATH)/../bin/$(CFG_HI_ARM_TOOLCHAINS_NAME)- -L$(BUILDER_LIB_PATH) -c++std c++11 \
	-L$(HI_SHARED_LIB_DIR) -skip qtandroidextras -skip qtmacextras -skip qtwinextras -skip qtdoc

	export PKG_CONFIG_LIBDIR=/none
	export PKG_CONFIG_PATH=$(THIRD_INSTALL_PATH)/lib/pkgconfig:/usr/local/lib/pkgconfig:/usr/lib/pkgconfig:/usr/lib/x86_64-linux-gnu/pkgconfig
	mkdir -p $(QT_DIR)/$(QT)/qtwebengine/lib
	cp $(FREETYPE_DIR)/freetype-2.7/builds/unix/freetype2.pc $(THIRD_INSTALL_PATH)/lib/pkgconfig
	cp -rf $(HI_SHARED_LIB_DIR)/* $(QT_DIR)/$(QT)/qtwebengine/lib/
	cp -rf $(THIRD_INSTALL_PATH)/lib/* $(QT_DIR)/$(QT)/qtwebengine/lib/

	cd $(QT_DIR)/$(QT); make uninstall
	cd $(QT_DIR)/$(QT)/qtwebengine; ../qtbase/bin/qmake

	cd $(QT_DIR)/$(QT); make -j; make install

	cd $(QT_DIR)/$(QT)/qtwebview/examples/webview/minibrowser/ && $(QT_DIR)/$(QT)/qtbase/bin/qmake; make -j; make install
endif #### 5.7.0
endif #### egl

##for 5.7 egl
build_qt_depend:
	rm -rf $(THIRD_PATH);mkdir -p $(THIRD_PATH)
	rm -rf $(THIRD_INSTALL_PATH);mkdir -p $(THIRD_INSTALL_PATH)
	#1. expat-2.1.0
	$(AT)test -d $(THIRD_PATH)/$(EXPAT_NAME) || tar xf $(OPEN_SOURCE_DIR)/$(EXPAT_NAME).tar.gz -C  $(THIRD_PATH)
	cd $(THIRD_PATH)/$(EXPAT_NAME);./configure --host=$(HOST) --prefix=$(THIRD_INSTALL_PATH) --enable-shared
	cd $(THIRD_PATH)/$(EXPAT_NAME);make -j;make install

	#2. dbus-1.11.4
	$(AT)test -d $(THIRD_PATH)/$(DBUS_NAME) || tar xf $(OPEN_SOURCE_DIR)/$(DBUS_NAME).tar.gz -C  $(THIRD_PATH)
	cd $(THIRD_PATH)/$(DBUS_NAME);CC=$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc CXX=$(CFG_HI_ARM_TOOLCHAINS_NAME)-g++ CFLAGS="-Wcast-align -g -O2 \
	-I$(THIRD_INSTALL_PATH)/include" CXXFLAGS=$(CFLAGS) LDFLAGS+="-L$(THIRD_INSTALL_PATH)/lib -lexpat" \
	./configure --host=$(HOST) --prefix=$(THIRD_INSTALL_PATH) --enable-shared --disable-tests
	cd $(THIRD_PATH)/$(DBUS_NAME);make -j;make install

	#3. fontconfig-2.12.0
	$(AT)test -d $(THIRD_PATH)/$(FONTCONFIG_NAME) || tar xf $(OPEN_SOURCE_DIR)/$(FONTCONFIG_NAME).tar.gz -C  $(THIRD_PATH)
	cd $(THIRD_PATH)/$(FONTCONFIG_NAME);FREETYPE_CFLAGS="-I$(HI_INCLUDE_DIR)/freetype2/freetype -I$(HI_INCLUDE_DIR)/freetype2" \
	FREETYPE_LIBS="-L$(HI_SHARED_LIB_DIR) -lfreetype" FREETYPE_CPPFLAGS=$(FREETYPE_CFLAGS) \
	./configure --host=$(HOST) --prefix=$(THIRD_INSTALL_PATH) --enable-shared \
	--with-expat-includes=$(THIRD_INSTALL_PATH)/include --with-expat-lib=$(THIRD_INSTALL_PATH)/lib
	cd $(THIRD_PATH)/$(FONTCONFIG_NAME);make -j;make install

	#4. icu4c-54_1-src
	$(AT)test -d $(THIRD_PATH)/$(ICU_NAME) || tar xf $(OPEN_SOURCE_DIR)/$(ICU_NAME).tgz -C  $(THIRD_PATH)
	cd $(THIRD_PATH)/icu/source;CC=$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc CXX=$(CFG_HI_ARM_TOOLCHAINS_NAME)-g++ ./runConfigureICU Linux/gcc
	cd $(THIRD_PATH)/icu/source;make -j;make clean;
	cd $(THIRD_PATH)/icu/source;./configure --host=$(HOST) --prefix=$(THIRD_INSTALL_PATH) --disable-samples --disable-tests \
	--with-cross-build=$(THIRD_PATH)/icu/source --with-data-packaging=archive --enable-samples=no --enable-tests=no --enable-extras=no
	cd $(THIRD_PATH)/icu/source;make -j;make install

endif #### HI_USER_SPACE_LIB


#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


