#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>  
#include <linux/jiffies.h>
#include <linux/delay.h>

static void get_jiffies(){
	printk(KERN_INFO "Size of unsigned long:%d\n", sizeof(unsigned long));
	printk(KERN_INFO "Now jiffies:%lu\n", jiffies);
}

static void total_time(){
	unsigned long start, total, i = 0, sum;
	start = jiffies;
	// Do some tasks
	for(i=0; i < 1000000; i++){
		pr_info("===");
	}

	total = jiffies - start;
	printk(KERN_INFO "It took %lu ticks \n", jiffies_to_clock_t(total));
	printk(KERN_INFO "It took %lu jiffies \n", total);
	printk(KERN_INFO "It took %lu s \n", total/HZ);
}

static void my_timer(){
	unsigned long timeout = jiffies + HZ, i=0;
	// do some work
	 for(i=0; i < 1000000; i++){
        pr_info("===");
    }
	// time out checking
	if(time_after(jiffies, timeout)){
		// time out 
		printk(KERN_INFO "What you did Time out.... Bumb\n ");
	}else{
		// ok
		printk(KERN_INFO "Not time out ..haha\n");
	}
}

// short delay case, cannot done by jiffies
static void delay_test(){
	mdelay(100);  // 
}

static int thread_init(void){
	//get_jiffies();
	//total_time();
	my_timer();
	return 0;
}

static void thread_exit(void)
{
	printk(KERN_ALERT"Exiting Module\n");
}

MODULE_LICENSE("GPL");
module_init(thread_init);
module_exit(thread_exit);
