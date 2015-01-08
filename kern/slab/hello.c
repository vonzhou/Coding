#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include <linux/slab.h>

static void  slab_test(){
	unsigned long page;
	page = __get_free_pages(GFP_KERNEL, 2);  // 4 pages
	// in x86 the virtual is 16bits
	printk(KERN_INFO "page virtual addr:%x\n", page);
	
	free_pages(page, 2);
}

static int __init lkp_init(void)
{
	printk(" ===module init====\n");
	page_test();
	return 0;
}

static void __exit lkp_cleanup(void)
{
	printk(" ===module exit====\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);


