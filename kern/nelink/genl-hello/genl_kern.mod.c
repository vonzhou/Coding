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
	{ 0x263f5f42, __VMLINUX_SYMBOL_STR(genl_unregister_ops) },
	{ 0x10d9bba3, __VMLINUX_SYMBOL_STR(genl_unregister_family) },
	{ 0x475b8ddd, __VMLINUX_SYMBOL_STR(genl_register_ops) },
	{ 0xb4902b30, __VMLINUX_SYMBOL_STR(__genl_register_family) },
	{ 0xec868c6, __VMLINUX_SYMBOL_STR(netlink_unicast) },
	{ 0xc040d57e, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x555b89d3, __VMLINUX_SYMBOL_STR(genlmsg_put) },
	{ 0xd7e8f88, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "BC512478966FD105AF229DF");
