#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include <linux/sched.h>

static void  current_process(){
	struct task_struct *task = current; // current process
	printk(KERN_INFO "current process info pid=%d, parent pid=%d \n", task->pid, task->parent->pid);
}	

// 打印init进程的所有孩子
static void init_child(){
	struct task_struct *p;
	struct list_head *list;
	struct list_head *tasks = &init_task.children;
	list_for_each(list, tasks){
		p = list_entry(list, struct task_struct, sibling);
		printk(KERN_INFO "pid=%d \n", p->pid);
	}
}

// 打印出所有的进程树结构

static int __init lkp_init(void)
{
	printk(" ===module init====\n");
	current_process();
	init_child();
	return 0;
}

static void __exit lkp_cleanup(void)
{
	printk(" ===module exit====\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);


