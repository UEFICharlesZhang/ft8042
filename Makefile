ifeq ($(KERNELRELEASE), )
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR)  M=$(PWD)  
clean:
	rm -rf *.mk .tmp_versions Module.symvers *.mod.c *.o *.ko .*.cmd Module.markers modules.order
load:
	insmod ft8042.ko
unload:
	rmmod ft8042
install: default
	mkdir -p /lib/modules/$(shell uname -r)/kernel/drivers/misc/
	cp -f ./ft8042.ko /lib/modules/$(shell uname -r)/kernel/drivers/misc/
	depmod -a
	echo "ft8042" >> /etc/modules
uninstall:
	rm -rf /lib/modules/$(shell uname -r)/kernel/drivers/misc/ft8042.ko
	depmod -a
else
	obj-m := ft8042.o
endif