#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/string.h>
#include <asm/uaccess.h>

static int on_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int on_close(struct inode *inode, struct file *file)
{
        return 0;
}

static ssize_t on_write(struct file *file, const char __user *buf, size_t len, loff_t *pos)
{
	if (strncmp(buf, AUTHOR_NAME, len) != 0)
		return -EINVAL;
	return len;
}

static ssize_t on_read(struct file *file, char __user *buf, size_t len, loff_t *pos)
{
	if (*pos == 0)
	{
		if (copy_to_user(buf, AUTHOR_NAME, sizeof(AUTHOR_NAME)) != 0)
			return -EFAULT;
		(*pos)++;
		return sizeof(AUTHOR_NAME);
	}

	return 0;
}

static const struct file_operations file_operations =
{
	.owner		= THIS_MODULE,
	.write		= on_write,
	.read		= on_read,
	.open		= on_open,
	.release	= on_close,
};

static struct miscdevice misc_device =
{
	.minor = MISC_DYNAMIC_MINOR,
	.name = "fourtytwo",
	.fops = &file_operations,
};

static int __init init_misc(void)
{
	int ret;

	if((ret = misc_register(&misc_device)) != 0)
		return ret;
	printk(KERN_INFO "misc char device driver initialized\n");
	return 0;
}

static void __exit dispose_misc(void)
{
	misc_deregister(&misc_device);
	printk(KERN_INFO "misc char device driver released\n");
}

module_init(init_misc);
module_exit(dispose_misc);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anas MASSNAOUI");
MODULE_DESCRIPTION("device driver - Misc Driver");

