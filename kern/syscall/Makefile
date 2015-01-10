ifneq ($(KERNELRELEASE),)
mymodule-objs:=intercept.c
obj-m += intercept.o
else
	PWD := $(shell pwd)
	KVER := $(shell uname -r)
	KDIR := /lib/modules/$(KVER)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD)
clean:
	rm -rf *.o *.mod.c *.ko *.mod.o *.symvers *.order .*.cmd .tmp*
endif
