/*About concurrent and race condition
complete.c -- witers awake the readers  

*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h> // task_struct
#include <linux/kernel.h>  // printk()
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/completion.h>

MODULE_LICENSE("Dual BSD/GPL");
static int complete_major = 300; // the major device number;
DECLARE_COMPLETION(comp);

ssize_t complete_read(struct file *filp, char __user *buf, size_t count, loff_t *pos){
	printk(KERN_DEBUG "process %d(%s) going to sleep",current->pid, current->comm);
	wait_for_completion(&comp);
	printk(KERN_DEBUG "awoken process %d(%s)",current->pid, current->comm);
	return 0;
}

ssize_t complete_write(struct file *filp, char __user *buf, size_t count, loff_t *pos){
	printk(KERN_DEBUG "process %d(%s) awake the readers..",current->pid, current->comm);
	complete(&comp);
	return count;
}

struct file_operations complete_fops = {
	.owner = THIS_MODULE,
	.read = complete_read,
	.write = complete_write,
};

int complete_init(void){
	int result;
	//register our major,and accept a dynamic number;
	result = register_chrdev(complete_major, "complete", &complete_fops);
	if(result < 0)
		return result;
	if(complete_major == 0)
		complete_major = result;// parameter indicate dynamic sssign,
	return 0;
}

int complete_cleanup(void){
	unregister_chrdev(complete_major, "complete");
}

module_init(complete_init);
module_exit(complete_cleanup);
















