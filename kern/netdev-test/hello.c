#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include <linux/notifier.h>
#include <linux/netdevice.h>

static int iterate_netdev(){
	struct net_device *dev;

	dev = first_net_device(&init_net);
	printk(KERN_INFO "net device iteration:");
	while (dev) {
    	printk(KERN_INFO "name:%s, ifindex:%d\n", dev->name, dev->ifindex);
    	dev = next_net_device(dev);
	}
}

// get netdev by index and do some thing
static int netdev_test(int index)
{
	struct net_device *dev;
	dev = dev_get_by_index_rcu(&init_net, index);
	if(dev == NULL){
		printk(KERN_INFO "get dev error\n");
		return -1;
	}
	
   	printk(KERN_INFO "name:%s, ifindex:%d\n", dev->name, dev->ifindex);
	//printk(KERN_INFO "%d\n", dev==NULL);
	//printk(KERN_INFO "net device ifindex : %d, name:%s\n", dev->ifindex, dev->name);
	//printk(KERN_INFO "net device event : %ld\n", event);
    
}

static int __init lkp_init(void)
{
	int err , index;
	index = 1;
	printk(KERN_INFO " module init..\n");
	//iterate_netdev();
	netdev_test(index);	
	return 0;
}

static void __exit lkp_cleanup(void)
{
	printk("<2> goodbye, leaving kernel space...\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);


