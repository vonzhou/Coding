#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include <linux/percpu.h>
#include <linux/smp.h>

struct stats_percpu{
	int apple;
	int orange;
};

static int  percpu_test(){
	void *ptr;
	struct stats_percpu *pstats;
	ptr = alloc_percpu(struct stats_percpu);
	if(!ptr){
		printk(KERN_INFO "wrong\n");
		return -ENOMEM;
	}
	
	pstats = get_cpu_var(ptr);
	// deal with it
//	pstats->apple = 100;
//	pstats->orange = 2;
	printk(KERN_INFO "current cpu is :%d\n", smp_processor_id());
	put_cpu_var(ptr);
	return 0;
}

static int __init lkp_init(void)
{
	printk(" ===module init====\n");
	percpu_test();
	return 0;
}

static void __exit lkp_cleanup(void)
{
	printk(" ===module exit====\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);
MODULE_LICENSE("GPL");

