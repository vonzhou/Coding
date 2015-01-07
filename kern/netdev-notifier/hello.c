#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include <linux/notifier.h>
#include <linux/netdevice.h>
static int dp_device_event(struct notifier_block *unused, unsigned long event,
			   void *ptr)
{
	struct net_device *dev = ptr;
	//printk(KERN_INFO "%d\n", dev==NULL);
	printk(KERN_INFO "net device ifindex : %d, name:%s\n", dev->ifindex, dev->name);
	printk(KERN_INFO "net device event : %ld\n", event);
    
	switch (event) {
	case NETDEV_UNREGISTER:
	    printk(KERN_INFO "unregister\n");
        break;

    case NETDEV_CHANGENAME:
        printk(KERN_INFO "change name\n");
		break;
	}
	return NOTIFY_DONE;
}

struct notifier_block test_device_notifier = {
	.notifier_call = dp_device_event
};



static int __init lkp_init(void)
{
	int err;
	printk(KERN_INFO " module init..\n");
	err = register_netdevice_notifier(&test_device_notifier);
	if(err)
		return -1;
	return 0;
}

static void __exit lkp_cleanup(void)
{
	unregister_netdevice_notifier(&test_device_notifier);
	printk("<2> goodbye, leaving kernel space...\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);


