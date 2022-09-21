PWD      := $(shell pwd)
OPPDIR   := $(subst $(TOPDIR),,$(PWD))
OBJDIR   := $(OBJTREE)$(OPPDIR)
all:
	@echo "use default ddr training"
	@mkdir -p $(OBJDIR)
	@rm -f $(OBJDIR)/libddr.a
	$(MAKE) -C ../default/cmd_bin TOPDIR=$(TOPDIR) CROSS_COMPILE="$(CROSS_COMPILE)"
	$(MAKE) -C ../default
	@cp -f $(OBJDIR)/../default/libddr.a $(OBJDIR)

clean:
	$(MAKE) -C ../default/cmd_bin TOPDIR=$(TOPDIR) CROSS_COMPILE="$(CROSS_COMPILE)" clean
	$(MAKE) -C ../default clean
	rm -rf libddr.a