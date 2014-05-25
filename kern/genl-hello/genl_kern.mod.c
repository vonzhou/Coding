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
	{ 0xf6628fc9, "module_layout" },
	{ 0x7629a0f8, "genl_unregister_ops" },
	{ 0x459a7fca, "genl_unregister_family" },
	{ 0x989f71fe, "genl_register_ops" },
	{ 0x6f1d93a6, "genl_register_family" },
	{ 0x5ce2e8d7, "netlink_unicast" },
	{ 0x2becda32, "nla_put" },
	{ 0xde0bdcff, "memset" },
	{ 0x5caf4af1, "skb_put" },
	{ 0x77782dca, "__alloc_skb" },
	{ 0x27e1a049, "printk" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "FA674F859EEC0D34C02680E");
