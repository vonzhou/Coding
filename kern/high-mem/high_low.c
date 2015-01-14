#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/highmem.h>
#include <linux/gfp.h>
#include <linux/mm_types.h>
#include <asm/io.h>
#include <linux/types.h>
#include <asm/cache.h>   //  L1_CACHE_BYTES
#include <asm/page_types.h>  //  PAGE_OFFSET
#include <linux/mm.h>    //varibale high_memory

static int hello_init(void) {
		// 内核中分配内存的常见情况
		struct page *mypage = alloc_page(GFP_USER);
		struct page *highmem_page;
		pr_info("L1 cache size %d\n", L1_CACHE_BYTES);
		pr_info("page_offset : %lx\n", PAGE_OFFSET);
		pr_info("high memory begining : %lx\n", (unsigned long)high_memory);
		
		if (!mypage) printk(KERN_ERR "Couldn't allocate normal page\n" );
		else {

				unsigned long page_addr = page_address(mypage);
				//printk(KERN_ERR "Address %lu\n", page_addr);


				phys_addr_t phy_addr = virt_to_phys(page_addr);
				printk(KERN_ERR "Address %lx\n", page_addr);
				printk(KERN_ERR "Physical Address is %lx \n", phy_addr);
		}


		// 分配高端内存 然后映射到内核空间
		highmem_page = alloc_page(GFP_HIGHUSER);
		if (!highmem_page) printk(KERN_ERR "Couldn't allocate highmem page \n" );
		else {

				unsigned long highmem_page_address = kmap(highmem_page);
				phys_addr_t phy_addr;
				if (!highmem_page_address) printk(KERN_ERR "Couldn't map highmem pages.\n");
				else {
						printk(KERN_ERR "Address for highuser pages after kmap is : %lx\n", 
										highmem_page_address );
				}

				phy_addr = virt_to_phys(page_address(highmem_page));
				printk(KERN_ERR "Physical Address is %lx \n", phy_addr);
		}

		kunmap(highmem_page);
		__free_page( highmem_page);
		__free_page(mypage);

		return 0;
}

static void hello_exit(void) {
		printk("====Bye===\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
