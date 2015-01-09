#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>  //  task_struct
#include <linux/kthread.h>  //  kthread api
#include <linux/init.h>  

int thread_fn() {
	printk(KERN_INFO "In my thread fn\n");
	return 0;
}

struct task_struct *thread1;
	
static int thread_init(void){
	thread1 = kthread_create(thread_fn,NULL,"my_thread");
/*
	set_task_state(thread1, __TASK_STOPPED);

	if ((thread1)) {
		printk(KERN_INFO "in if \n");
		wake_up_process(thread1);
        }
*/
	return 0;
}

static void thread_exit(void)
{
	kthread_stop(thread1);
	printk(KERN_ALERT"Exiting Module\n");
}

MODULE_LICENSE("GPL");
module_init(thread_init);
module_exit(thread_exit);
