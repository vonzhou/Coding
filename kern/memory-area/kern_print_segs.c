#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/mm.h>

static int pid_mem = 1;

static void print_mem(struct task_struct *task)
{
        struct mm_struct *mm;
        struct vm_area_struct *vma;
        int count = 0;
        mm = task->mm;
        printk(KERN_INFO "This mm_struct has %d vmas.\n", mm->map_count);
        for (vma = mm->mmap ; vma ; vma = vma->vm_next) {
                pr_info("Vma number %d: \n", ++count);
                pr_info("Starts at 0x%lx, Ends at 0x%lx\n",
                          vma->vm_start, vma->vm_end);
        }
        pr_info("Code  Segment start = 0x%lx, end = 0x%lx \n"
                 "Data  Segment start = 0x%lx, end = 0x%lx\n"
                 "Stack Segment start = 0x%lx\n",
                 mm->start_code, mm->end_code,
                 mm->start_data, mm->end_data,
                 mm->start_stack);
}

static int mm_exp_load(void){
        struct task_struct *task;
        printk("Will detect process %d's VMAs information.\n", pid_mem);
		// lookup this task
        for_each_process(task) {
                if ( task->pid == pid_mem) {
                        printk(KERN_INFO "%s[%d]\n", task->comm, task->pid);
                        print_mem(task);
                }
        }
        return 0;
}

static void mm_exp_unload(void)
{
        printk(KERN_INFO "Print segment information module exiting.\n");
}

module_init(mm_exp_load);
module_exit(mm_exp_unload);
module_param(pid_mem, int, 0);

MODULE_DESCRIPTION ("Print segment information");
MODULE_LICENSE("GPL");
