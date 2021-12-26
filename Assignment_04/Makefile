KDIR	= /lib/modules/`uname -r`/build

obj-m	= detect_keyboard.o

build:
	make -C $(KDIR) M="$(PWD)"

clean:
	make -C $(KDIR) M=`pwd` clean
