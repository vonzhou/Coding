
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/net.h>
#include <net/sock.h>
#include <linux/in.h>
#include <linux/types.h>
#include <linux/kthread.h>
#include <linux/wait.h>
#include <linux/skbuff.h>
#include <linux/string.h>
#include <asm-generic/unaligned.h>
#include <linux/sysctl.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <asm/checksum.h>
#include <linux/ip.h>
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


