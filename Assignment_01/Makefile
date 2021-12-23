KDIR	= /lib/modules/`uname -r`/build

obj-m	= main.o

build:
	make -C $(KDIR) M="$(PWD)"

clean:
	make -C $(KDIR) M=`pwd` clean
