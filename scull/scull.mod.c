#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x15b2dc7b, "module_layout" },
	{ 0x7406f5c5, "kobject_put" },
	{ 0xe99ab841, "cdev_del" },
	{ 0x68c70c2d, "kmalloc_caches" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x3d3774b, "cdev_init" },
	{ 0x76ebea8, "pv_lock_ops" },
	{ 0x15692c87, "param_ops_int" },
	{ 0xd8e484f0, "register_chrdev_region" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x32fd4b62, "__wake_up_sync" },
	{ 0x8619221b, "no_llseek" },
	{ 0x4792c572, "down_interruptible" },
	{ 0x72b0a36c, "kobject_set_name" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x836f11d1, "tty_devnum" },
	{ 0x1691522d, "nonseekable_open" },
	{ 0x68dfc59f, "__init_waitqueue_head" },
	{ 0x2bc95bd4, "memset" },
	{ 0x289ae517, "current_task" },
	{ 0x50eedeb8, "printk" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x2f287f0d, "copy_to_user" },
	{ 0xf1dd72c7, "fasync_helper" },
	{ 0xb4390f9a, "mcount" },
	{ 0xdd1a2871, "down" },
	{ 0x60ac4203, "cdev_add" },
	{ 0xc6cbbc89, "capable" },
	{ 0xb2fd5ceb, "__put_user_4" },
	{ 0x4292364c, "schedule" },
	{ 0x2c9189e, "kmem_cache_alloc_trace" },
	{ 0x67f7403e, "_raw_spin_lock" },
	{ 0xe45f60d8, "__wake_up" },
	{ 0x37a0cba, "kfree" },
	{ 0x622fa02a, "prepare_to_wait" },
	{ 0xc4554217, "up" },
	{ 0x2c0325d0, "kill_fasync" },
	{ 0x75bb675a, "finish_wait" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x29537c9e, "alloc_chrdev_region" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "431BFE19168DA20E761FB01");
