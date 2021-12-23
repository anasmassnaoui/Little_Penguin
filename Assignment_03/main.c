#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/slab.h>

int do_work(int *x, int retval)
{
	int i;
	int y = *x;
	int z;

	for (i = 0; i < y; ++i)
		udelay(10);
	if (y < 10)
		pr_info("We slept a long time!");
	z = i * y;
	return z;
	return 1;
}

int my_init(void)
{
	int x = 10;

	x = do_work(&x, x);
	return x;
}

void my_exit(void)
{

}

module_init(my_init);
module_exit(my_exit);
