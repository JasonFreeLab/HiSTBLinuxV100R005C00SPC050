# Get the dir of the ta-dev-kit, requires make version 3.81 or later
ta-dev-kit-dir := $(patsubst %/,%,$(abspath $(dir $(lastword $(MAKEFILE_LIST)))..))


.PHONY: all
all:

binary := $(BINARY)
libname := $(LIBNAME)
taname := $(TA_NAME)

ifneq ($(BINARY),)
ifneq ($(LIBNAME),)
$(error You can only specify one of BINARY or LIBNAME)
endif
else
ifeq ($(LIBNAME),)
$(error You must specify one of BINARY or LIBNAME)
endif
endif

ifeq ($(TA_NAME),)
$(error You must specify TA_NAME)
endif

# set ta compile env
sm := ta_arm32
sm-ta_arm32 := y
CFG_ARM32_ta_arm32 := y
ta_arm32-platform-cppflags := -DARM32=1 -D__ILP32__=1
ta_arm32-platform-cflags := -O2 -fstrict-aliasing -funswitch-loops -fno-short-enums -W -Wall -mfloat-abi=softfp -mfpu=neon -fno-omit-frame-pointer -fstack-protector-all -Wstack-protector -MD
ta_arm32-platform-aflags := 
CROSS_COMPILE32 := $(CROSS_COMPILE1)
CROSS_COMPILE_ta_arm32 := $(CROSS_COMPILE1)

ifneq ($O,)
out-dir := $O
else
out-dir := .
endif

ifneq ($V,1)
q := @
cmd-echo := true
cmd-echo-silent := echo
else
q :=
cmd-echo := echo
cmd-echo-silent := true
endif

ifneq ($(filter 4.%,$(MAKE_VERSION)),)  # make-4
ifneq ($(filter %s ,$(firstword x$(MAKEFLAGS))),)
cmd-echo-silent := true
endif
else                                    # make-3.8x
ifneq ($(findstring s, $(MAKEFLAGS)),)
cmd-echo-silent := true
endif
endif

cppflags$(sm)  := $($(sm)-platform-cppflags) $(CPPFLAGS_$(sm))
aflags$(sm)    := $($(sm)-platform-aflags)
cflags$(sm)    := $($(sm)-platform-cflags) $(CFLAGS_$(sm))


cppflags$(sm) += -I.


include $(ta-dev-kit-dir)/mk/cleandirs.mk

.PHONY: clean
clean: $(conf-file-clean)
	@$(cmd-echo-silent) '  CLEAN   $(out-dir)'
	${q}rm -f $(cleanfiles)
	${q}dirs="$(call cleandirs-for-rmdir)"; if [ -d "$$dirs" ]; then $(RMDIR) $$dirs; fi
	@$(cmd-echo-silent) '  CLEAN   $(O)'
	${q}if [ -d "$(O)" ]; then $(RMDIR) $(O); fi

subdirs = .
include  $(ta-dev-kit-dir)/mk/subdir.mk


include  $(ta-dev-kit-dir)/mk/gcc.mk
include  $(ta-dev-kit-dir)/mk/compile.mk
ifneq ($(binary),)
include  $(ta-dev-kit-dir)/mk/ta_link.mk
else
ifneq ($(libname),)
all: $(libname).a
cleanfiles += $(libname).a

$(libname).a: $(objs)
	@echo '  AR      $@'
	$(q)rm -f $@ && $(AR$(sm)) rcs -o $@ $^
endif
endif
