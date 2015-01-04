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
	{ 0x8b77232d, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xd702cfa4, __VMLINUX_SYMBOL_STR(netlink_kernel_release) },
	{ 0xec868c6, __VMLINUX_SYMBOL_STR(netlink_unicast) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xd59007da, __VMLINUX_SYMBOL_STR(skb_recv_datagram) },
	{ 0xf4b4e2e9, __VMLINUX_SYMBOL_STR(__netlink_kernel_create) },
	{ 0x4c20a81, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0xcf21d241, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "A8AC549E60515367326E874");
