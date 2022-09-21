global-incdirs-y += include

cflags-y += -Wno-error -Wno-implicit-function-declaration -fgnu89-inline -Wno-unused-parameter
cflags-y += -I$(HI_TEE_API_DIR)/include

srcs-y += media_mem.c
srcs-y += mmz_ext.c
srcs-y += mmz_intf.c
srcs-y += mmz_user.c
srcs-y += debug.c
