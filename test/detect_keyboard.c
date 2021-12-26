#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/usb.h>
#include <linux/usb/input.h>
#include <linux/hid.h>

static struct usb_device_id keyboard_identifiers[] =
{
	{ USB_INTERFACE_INFO(
		USB_INTERFACE_CLASS_HID,
		USB_INTERFACE_SUBCLASS_BOOT,
		USB_INTERFACE_PROTOCOL_KEYBOARD)
	},
	{}
};

MODULE_DEVICE_TABLE(usb, keyboard_identifiers);

static int on_keyboard_connect(struct usb_interface *interface, const struct usb_device_id *id)
{
	printk(KERN_INFO "keyboard: (%04X:%04X) plugged\n", id->idVendor, id -> idProduct);
	return 0;
}

static void on_keyboard_disconnect(struct usb_interface *interface)
{
	printk(KERN_INFO "keyboard disconnected");
}

static struct usb_driver keyboard_driver =
{
	.name = "keyboard_driver",
	.id_table = keyboard_identifiers,
	.probe = on_keyboard_connect,
	.disconnect = on_keyboard_disconnect,
};

static int __init init_keyboard_listener(void)
{
	printk(KERN_INFO "register keyboard listener\n");
	return usb_register(&keyboard_driver);
}

static void __exit dispose_keyboard_listener(void)
{
	printk(KERN_INFO "release keyboard listener\n");
	usb_deregister(&keyboard_driver);
}

module_init(init_keyboard_listener);
module_exit(dispose_keyboard_listener);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anas MASSNAOUI");
MODULE_DESCRIPTION("USB Keyboard Registration Driver");


