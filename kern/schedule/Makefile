ifneq ($(KERNELRELEASE),)
mymodule-objs:=schedule_test.c
obj-m += schedule_test.o
else
	PWD := $(shell pwd)
	KVER := $(shell uname -r)
	KDIR := /lib/modules/$(KVER)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD)
clean:
	rm -rf *.o *.mod.c *.ko *.mod.o *.symvers *.order *-
endif
