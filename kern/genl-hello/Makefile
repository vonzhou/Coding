ifneq ($(KERNELRELEASE),)
mymodule-objs:=genl_kern.c
obj-m += genl_kern.o
else
        PWD := $(shell pwd)
        KVER := $(shell uname -r)
        KDIR := /lib/modules/$(KVER)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD)
clean:
	rm -rf *.o *.mod.c *.ko *.mod.o *.symvers *.order *-
endif

