#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

static dev_t first;
static struct cdev c_dev;
static struct class *cl;

static int _open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Driver: open\n");
	return 0;
}

static int _close(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Driver: close\n");
	return 0;
}

static ssize_t _read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Driver: read\n");
	return 0;
}

static ssize_t _write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Driver: write\n");
        return len;
}

static struct file_operations pugs_fops = 
{
	.owner = THIS_MODULE,
	.open = _open,
	.release = _close,
	.read = _read,
	.write = _write
};


static int __init ofcd_init(void) {
	int ret;
	struct device *dev_ret;

	printk(KERN_INFO "ofcd registered\n");
	if ((ret = alloc_chrdev_region(&first, 0, 1, "amassnao")) < 0)
	{
		return ret;
	}
	if (IS_ERR(cl = class_create(THIS_MODULE, "chardrv")))
	{
		unregister_chrdev_region(first, 1);
		return PTR_ERR(cl);
	}
	if (IS_ERR(dev_ret = device_create(cl, NULL, first, NULL, "nullable")))
	{
		class_destroy(cl);
		unregister_chrdev_region(first, 1);
		return PTR_ERR(dev_ret);
	}

	cdev_init(&c_dev, &pugs_fops);
	if ((ret = cdev_add(&c_dev, first, 1)) < 0)
	{
		device_destroy(cl, first);
		class_destroy(cl);
		unregister_chrdev_region(first, 1);
		return ret;
	}
	return 0;
}

static void __exit ofcd_exit(void) {
	cdev_del(&c_dev);
	device_destroy(cl, first);
	class_destroy(cl);
	unregister_chrdev_region(first, 1);
	printk(KERN_INFO "ofcd unregistred\n");
}

module_init(ofcd_init);
module_exit(ofcd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("amassnao");
MODULE_DESCRIPTION("my first character device");
