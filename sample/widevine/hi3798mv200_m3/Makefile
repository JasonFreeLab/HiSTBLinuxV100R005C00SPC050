.PHONY: all clean

all:
	make -C $(CURDIR)/protobuf all
	make -C $(CURDIR)/provision all
	make -C $(CURDIR)/sample mksamplecommon_lib
	make -C $(CURDIR)/sample sample_tvp_play
	./build.sh
	
clean:
	make -C $(CURDIR)/protobuf clean
	make -C $(CURDIR)/provision clean
	make -C $(CURDIR)/sample clean
	rm -rf $(CURDIR)/GoogleTest/out
