	发生以下错误，导致模块卸载不掉  TODO

[322932.413280]  ===module init====
[322932.413299] general protection fault: 0000 [#1] SMP 
[322932.413443] Modules linked in: hello(OF+) genl_kern(OF) ip6table_filter ip6_tables ebtable_nat ebtables ipt_MASQUERADE iptable_nat nf_nat_ipv4 nf_nat nf_conntrack_ipv4 nf_defrag_ipv4 xt_state nf_conntrack rdma_ucm(OF) ib_ucm(OF) ipt_REJECT xt_CHECKSUM rdma_cm(OF) iw_cm(OF) iptable_mangle xt_tcpudp iptable_filter ip_tables pci_stub x_tables vboxpci(OF) vboxnetadp(OF) vboxnetflt(OF) vboxdrv(OF) ib_ipoib(OF) ib_cm(OF) ib_uverbs(OF) ib_umad(OF) bridge stp mlx5_ib(OF) llc mlx5_core(OF) mlx4_en(OF) mlx4_ib(OF) ib_sa(OF) ib_mad(OF) ib_core(OF) ib_addr(OF) mlx4_core(OF) compat(OF) bnep rfcomm bluetooth ast joydev ttm drm_kms_helper drm sysimgblt dcdbas sysfillrect syscopyarea ioatdma mac_hid lpc_ich i7core_edac edac_core parport_pc ppdev lp parport hid_generic usbhid hid ahci igb mptsas libahci mptscsih dca i2c_algo_bit mptbase ptp scsi_transport_sas pps_core [last unloaded: hello]
[322932.418891] CPU: 9 PID: 22933 Comm: insmod Tainted: PF          O 3.11.0-15-generic #25~precise1-Ubuntu
[322932.418985] Hardware name: Dell     C6100       /0D61XP, BIOS 1.51.00 10/06/2010
[322932.419068] task: ffff8801b4f21770 ti: ffff880169ce4000 task.ti: ffff880169ce4000
[322932.419150] RIP: 0010:[<ffffffffa05ed049>]  [<ffffffffa05ed049>] lkp_init+0x49/0x1000 [hello]
[322932.419280] RSP: 0018:ffff880169ce5dd8  EFLAGS: 00010283
[322932.419349] RAX: ffff100323985de0 RBX: 0000000000000000 RCX: 0000000000000018
[322932.419430] RDX: 0000000000000018 RSI: 0000000000000100 RDI: ffffffff81c5aa40
[322932.419510] RBP: ffff880169ce5de8 R08: ffffffff81d03de0 R09: 0000000000000100
[322932.419591] R10: ffff880334fda800 R11: 0000000000000008 R12: ffffffffa05ed000
[322932.419671] R13: 0000000000000000 R14: 0000000000ef3010 R15: 0000000000000000
[322932.419783] FS:  00007f6e96bc9700(0000) GS:ffff8801b9ca0000(0000) knlGS:0000000000000000
[322932.419872] CS:  0010 DS: 0000 ES: 0000 CR0: 000000008005003b
[322932.419940] CR2: 0000000000ef402f CR3: 000000016df2a000 CR4: 00000000000007e0
[322932.419996] Stack:
[322932.420031]  ffff880169ce5e18 000060fcc00013e8 ffff880169ce5e68 ffffffff8100212a
[322932.420883]  0000000000ef3010 0000000000000000 ffff880169ce5e38 ffffffff810578e3
[322932.421023]  0000000000000000 0000000000000000 0000000000ef3010 ffffffffa05ef000
[322932.421168] Call Trace:
[322932.421210]  [<ffffffff8100212a>] do_one_initcall+0xfa/0x1b0
[322932.421264]  [<ffffffff810578e3>] ? set_memory_nx+0x43/0x50
[322932.421322]  [<ffffffff81730257>] do_init_module+0x80/0x1d1
[322932.421374]  [<ffffffff810d1af9>] load_module+0x4c9/0x5f0
[322932.421425]  [<ffffffff810cf270>] ? show_initstate+0x50/0x50
[322932.421476]  [<ffffffff810d1cd4>] SyS_init_module+0xb4/0x100
[322932.421529]  [<ffffffff8175099d>] system_call_fastpath+0x1a/0x1f
[322932.421581] Code: 00 00 e8 4b c9 b7 e0 48 85 c0 48 89 45 f8 75 0e 48 c7 c7 39 40 6a a0 e8 28 26 14 e1 eb 33 48 8d 45 f8 65 48 03 04 25 88 dc 00 00 <48> 8b 00 48 c7 c7 42 40 6a a0 c7 00 64 00 00 00 c7 40 04 02 00 
[322932.425483] RIP  [<ffffffffa05ed049>] lkp_init+0x49/0x1000 [hello]
[322932.425562]  RSP <ffff880169ce5dd8>
[322932.432604] ---[ end trace da0ad3a4c5a3b7c2 ]---
