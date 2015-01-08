#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include <linux/types.h>  // list_head
#include <linux/slab.h>
#include <linux/string.h>
struct person{
	char name[20];
	int age;
	struct list_head list;
};

static LIST_HEAD(plist);

static int person_ops(){
	struct person *mike, *aron;
	struct person *p;
	struct list_head *tmp;
	mike = kmalloc(sizeof(struct person), GFP_KERNEL);
	strcpy(mike->name, "Mike");
	mike->age = 23;
	INIT_LIST_HEAD(&mike->list);

	aron = kmalloc(sizeof(struct person), GFP_KERNEL);
	strcpy(aron->name ,"Aron Swartz");
	aron->age = 26;
	INIT_LIST_HEAD(&aron->list);
	
	list_add(&aron->list, &plist);
	list_add(&mike->list, &plist);

	list_for_each(tmp, &plist){
		p = list_entry(tmp, struct person, list);
		printk(KERN_INFO "name:%s age:%d\n", p->name, p->age);
	}
	// another traverse way
	list_for_each_entry(p, &plist, list){
		p->age += 1;
		// ......
	}

	list_for_each_entry(p, &plist, list){
		printk(KERN_INFO "name:%s, age:%d\n", p->name, p->age);
    }

	kfree(mike);
	kfree(aron);
}

static int __init lkp_init(void)
{
	printk(" ===module init====\n");
	person_ops();
	return 0;
}

static void __exit lkp_cleanup(void)
{
	printk(" ===module exit====\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);


