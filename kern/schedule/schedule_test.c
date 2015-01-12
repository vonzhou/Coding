
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>

#define TEST_INTERVAL 10 * HZ

static void test_work_handler(struct work_struct *work);

static DECLARE_DELAYED_WORK(test_work, test_work_handler);

static void test_work_handler(struct work_struct *work){
	// do sth
    printk(KERN_INFO "test work function.\n");
	// and then schedule it again 
	schedule_delayed_work(&test_work, TEST_INTERVAL);
}

static int __init main_init(void){
    schedule_delayed_work(&test_work, TEST_INTERVAL);

    return 0;
}

static void __exit main_exit(void){
    cancel_delayed_work_sync(&test_work);
}

module_init(main_init);
module_exit(main_exit);
MODULE_LICENSE("GPL");


