KDIR	= /lib/modules/`uname -r`/build

obj-m			= misc_device.o
CFLAGS_misc_device.o	= -D AUTHOR_NAME='"amassnao"'

build:
	make -C $(KDIR) M="$(PWD)"

clean:
	make -C $(KDIR) M=`pwd` clean
