#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/usb.h>
#include <linux/usb/input.h>
#include <linux/hid.h>

static int __init init_keyboard_listener(void)
{
	printk(KERN_INFO "USB Keyboard plug in\n");
	return 0;
}

static void __exit dispose_keyboard_listener(void)
{
	printk(KERN_INFO "USB Keyboard unplugged\n");
}

module_init(init_keyboard_listener);
module_exit(dispose_keyboard_listener);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anas MASSNAOUI");
MODULE_DESCRIPTION("USB Keyboard Registration Driver");


