#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>

static int __init lkp_init(void)
{
	printk(" <1> hello ,world..\n");
	return 0;
}

static void __exit lkp_cleanup(void)
{
	printk("<2> goodbye, leaving kernel space...\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);


