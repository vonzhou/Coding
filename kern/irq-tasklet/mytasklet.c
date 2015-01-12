#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>

struct tasklet_struct my;

void my_handler (unsigned long data) {
	pr_info("my tasklet handler haha...\n");
	return ;
}

/* Initialize the module and a tasklet */
static int __init my_tasklet_init(void)
{
  	int result;
	tasklet_init(&my, my_handler, 0);
	pr_info("init our tasklet handler...\n");

	tasklet_schedule(&my);
  	return result;
}

/* Remove the interrupt handler */
static void __exit my_tasklet_exit(void) {
	tasklet_kill(&my);
}

MODULE_LICENSE ("GPL");
module_init(my_tasklet_init);
module_exit(my_tasklet_exit);

