
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/delay.h>
#include <asm/paravirt.h>

unsigned long **sys_call_table;
unsigned long original_cr0;

asmlinkage long (*ref_sys_read)(unsigned int fd, char __user *buf, size_t count);
asmlinkage long new_sys_read(unsigned int fd, char __user *buf, size_t count)
{
        long ret;
        ret = ref_sys_read(fd, buf, count);
		//printk(KERN_INFO "sys_read return : %d\n", ret);
		// 用这里的fd进行拦截特定的文件读
        if(fd == 4)
                printk(KERN_INFO "ret:%d, intercept: 0x%02X\n", ret, buf[0]);

        return ret;
}

static unsigned long **aquire_sys_call_table(void)
{
        unsigned long int offset = PAGE_OFFSET;
        unsigned long **sct;
		// 从内核空间开始找起		
        printk(KERN_INFO "Page offset : %lx, ULLONG_MAX : %llx\n", offset, ULLONG_MAX);
        while (offset < ULLONG_MAX) {
                sct = (unsigned long **)offset;

                if (sct[__NR_close] == (unsigned long *) sys_close) 
                        return sct;

                offset += sizeof(void *);
        }
        
        return NULL;
}

static int __init interceptor_start(void) 
{
		
        printk(KERN_INFO "Module init .....\n");
		sys_call_table = aquire_sys_call_table();
        if(!sys_call_table)
                return -1;
        printk(KERN_INFO "System call table addr is : %lx\n", &sys_call_table[0]);
        original_cr0 = read_cr0();

        write_cr0(original_cr0 & ~0x00010000); // page protection disabled
        ref_sys_read = (void *)sys_call_table[__NR_read];
        sys_call_table[__NR_read] = (unsigned long *)new_sys_read;
        write_cr0(original_cr0);    
        
        return 0;
}

static void __exit interceptor_end(void) 
{
        if(!sys_call_table) {
                return;
        }
        
        write_cr0(original_cr0 & ~0x00010000);
        sys_call_table[__NR_read] = (unsigned long *)ref_sys_read;
        write_cr0(original_cr0);
        
        msleep(2000);
}

module_init(interceptor_start);
module_exit(interceptor_end);

MODULE_LICENSE("GPL");

