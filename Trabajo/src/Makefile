KERNEL_VER=5.4.0-29-generic
obj-m += hello-1.o
obj-m += hello-2.o

all:
	make -C /lib/modules/$(KERNEL_VER)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KERNEL_VER)/build M=$(PWD) clean
