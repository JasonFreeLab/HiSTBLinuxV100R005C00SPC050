link-out-dir = $(out-dir)

ifneq ($(TA_OUT_DIR),)
ta-out-dir = $(TA_OUT_DIR)
else
ta-out-dir = $(out-dir)
endif
ta-entry-file = $(TRUSTEDCORE_DIR)/release/internal_tasks/elf_main_entry.o


all: $(link-out-dir)/$(binary).elf $(link-out-dir)/$(binary).dmp \
	$(link-out-dir)/$(binary).bin $(link-out-dir)/$(binary).sec \
	$(ta-out-dir)/$(taname).elf

cleanfiles += $(link-out-dir)/$(binary).elf $(link-out-dir)/$(binary).dmp
cleanfiles += $(link-out-dir)/$(binary).map
cleanfiles += $(link-out-dir)/$(binary).bin
cleanfiles += $(link-out-dir)/$(binary).sec
cleanfiles += $(ta-out-dir)/$(taname).elf

link-ldflags  = $(LDFLAGS)
link-ldflags += -r -d --strip-debug
link-ldflags += --whole-archive -T $(TA_LINK_SCRIPT) $(ta-entry-file) --no-whole-archive

# Macro to reverse a list
reverse = $(if $(wordlist 2,2,$(1)),$(call reverse,$(wordlist 2,$(words $(1)),$(1))) $(firstword $(1)),$(1))

link-ldadd  = $(LDADD)
link-ldadd += $(addprefix -L,$(libdirs))
link-ldadd += $(addprefix -l,$(call reverse,$(libnames)))
ldargs-$(binary).elf := $(link-ldflags) $(objs) $(link-ldadd)


link-script-cppflags-$(sm) := -DASM=1 \
	$(filter-out $(CPPFLAGS_REMOVE) $(cppflags-remove), \
		$(nostdinc$(sm)) $(CPPFLAGS) \
		$(addprefix -I,$(incdirs$(sm)) $(link-out-dir)) \
		$(cppflags$(sm)))


define user-link
	$(q)$(LD$(sm)) $(ldargs-$(binary).elf) -o $(2) $(1) `$(CC1) -mthumb-interwork -print-libgcc-file-name`
endef

$(link-out-dir)/$(binary).elf: $(objs) $(libdeps) $(TA_LINK_SCRIPT)
	@$(cmd-echo-silent) '  LD      $@'
	$(call user-link,,$@)

$(ta-out-dir)/$(taname).elf: $(link-out-dir)/$(binary).elf
	@$(cmd-echo-silent) '  CP   $<   $@'
	$(q)cp -af $< $@

$(link-out-dir)/$(binary).dmp: $(link-out-dir)/$(binary).elf
	@$(cmd-echo-silent) '  OBJDUMP $@'
	$(q)$(OBJDUMP$(sm)) -l -x -d $< > $@

$(link-out-dir)/$(binary).bin: $(link-out-dir)/$(binary).elf
	@$(cmd-echo-silent) '  PACK      $@ $(CURDIR)/manifest.txt'
	test ! -f $(CURDIR)/manifest.txt || $(TRUSTEDCORE_PACK_TA_SCRIPT) $(link-out-dir)/$(binary).elf $(CURDIR)/manifest.txt

$(link-out-dir)/$(binary).sec: $(link-out-dir)/$(binary).bin
	@echo '  SIGN    $@'
