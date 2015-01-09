#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include <linux/sched.h>

// 获取当前进程的一些信息，熟悉 task_struct 结构
static void  current_process(){
	struct task_struct *task = current; // current process
	printk(KERN_INFO "process name=%s, pid=%d, parent pid=%d \n", task->comm, task->pid, task->parent->pid);
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

// 从init开始，遍历出所有的进程树结构
static void thread_tree(){
	struct task_struct *task;	
	task = &init_task;
	do {
		// Get the thread info from stack pointer
		struct thread_info * ti = (struct thread_info*)(task->stack);
		struct task_struct * _task = ti->task;
		// A check to see if each task has a separate stack area by checking the address.
		// 通过栈指针获得的进程信息
		printk("Stack Tail Address %p\n", ti); 
		printk("And corresponding task: %d, %s\n", _task->pid, _task->comm);
		// 当前遍历的该进程的信息，及调度统计
		printk("Process %d : %s has %d threads\n", task->pid, task->comm, get_nr_threads(task));
		printk("Kernel Stack size:%luKB, run times on this cpu:%lu, time waiting:%llu, last run ts:%llud, last ts queued to rq:%llud\n", 
				THREAD_SIZE/1024, task->sched_info.pcount, task->sched_info.run_delay,
	 			task->sched_info.last_arrival, task->sched_info.last_queued);
		printk("Real time sched timeout:%lu\n",task->rt.timeout);


		// A kernel thread has no address space.
		if (task->mm == NULL) {
			printk("KERNEL THREAD\n\n");
		}
		else {
			printk("USER THREAD\n");
		}		

		// If task is kthreadd, traverse all children to find out all the kernel threads.
		if (task->pid == 2) {
			struct task_struct *child_task;
			// Iterate task->children list of 'kthreadd', they are listed by siblings field.
			list_for_each_entry(child_task, &(task->children), sibling) {
				printk("\t\t %d 	:	%s\n",child_task->pid, child_task->comm);
			}
		}
		task = next_task(task);
	} while (task != &init_task);	
}

static int __init lkp_init(void)
{
	printk(" ===module init====\n");
	//current_process();
	//init_child();
	thread_tree();
	return 0;
}

static void __exit lkp_cleanup(void)
{
	printk(" ===module exit====\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);
MODULE_LICENSE("GPL");

