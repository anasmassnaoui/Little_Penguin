#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

MODULE_DESCRIPTION("Assignment 01");
MODULE_AUTHOR("amassnao");
MODULE_LICENSE("GPL");

static int dummy_init(void)
{
        printk("Hello World !\n");
        return 0;
}

static void dummy_exit(void)
{
        printk("Cleaning up module.\n");
}

module_init(dummy_init);
module_exit(dummy_exit);

