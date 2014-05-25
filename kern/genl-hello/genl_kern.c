#include <net/genetlink.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
/*netlink attributes 可以通过枚举索引找到对应的类型
*用户空间应用程序要传递这样的信息*/

enum {
DOC_EXMPL_A_UNSPEC,
DOC_EXMPL_A_MSG,
__DOC_EXMPL_A_MAX,
};
#define DOC_EXMPL_A_MAX (__DOC_EXMPL_A_MAX - 1)

/*atribute policy就是定义各个属性的具体类型，参见net/netlink.h*/
static struct nla_policy doc_exmpl_genl_policy[DOC_EXMPL_A_MAX + 1] = {
	[DOC_EXMPL_A_MSG] = {.type = NLA_NUL_STRING},
};

#define VERSION_NR 1

//generic netlink family 定义
static struct genl_family doc_exmpl_genl_family = {
	.id = GENL_ID_GENERATE,
	.hdrsize = 0,
	.name = "CONTROL_EXMPL",
	.version = VERSION_NR,
	.maxattr = DOC_EXMPL_A_MAX,
};

/*定义命令类型，用户空间以此来表明需要执行的命令*/
enum{
DOC_EXMPL_C_UNSPEC,
DOC_EXMPL_C_ECHO,
__DOC_EXMPL_C_MAX,
};
#define DOC_EXMPL_C_MAX (__DOC_EXMPL_C_MAX - 1)

//echo command handler,接收一个msg并回复
int doc_exmpl_echo(struct sk_buff *skb2, struct genl_info *info){
	struct nlattr *na;
	struct sk_buff *skb;
	int rc;
	void *msg_hdr;
	char *data;
	if(info == NULL)
		goto error;
	//对于每个属性，genl_info的域attrs可以索引到具体结构，里面有payload
	na = info->attrs[DOC_EXMPL_A_MSG];
	if(na){
		data = (char *)nla_data(na);
		if(!data) printk("Receive data error!\n");
		else printk("Recv:%s\n",data);
	}else{
		printk("No info->attrs %d\n",DOC_EXMPL_A_MSG);
	}

	skb = genlmsg_new(NLMSG_GOODSIZE,GFP_KERNEL);
	if(!skb) goto error;
	
	/*构建消息头，函数原型是
	genlmsgput(struct sk_buff *,int pid,int seq_number,
		struct genl_family *,int flags,u8 command_index);
	*/
	msg_hdr = genlmsg_put(skb,0,info->snd_seq+1,&doc_exmpl_genl_family,
				0,DOC_EXMPL_C_ECHO);
	if(msg_hdr == NULL){
		rc = -ENOMEM;
		goto error;
	}
	
	//填充具体的netlink attribute:DOC_EXMPL_A_MSG，这是实际要传的数据
	rc = nla_put_string(skb,DOC_EXMPL_A_MSG,"Hello World from kernel space!");
	if(rc != 0) goto error;

	genlmsg_end(skb,msg_hdr);//消息构建完成
	//单播发送给用户空间的某个进程
	rc = genlmsg_unicast(genl_info_net(info),skb,info->snd_pid);
	if(rc != 0){
		printk("Unicast to process:%d failed!\n",info->snd_pid);
		goto error;
	}
	return 0;

	error:
	printk("Error occured in doc_echo!\n");
	return 0;
}

//将命令command echo和具体的handler对应起来
static struct genl_ops doc_exmpl_genl_ops_echo = {
        .cmd = DOC_EXMPL_C_ECHO,
        .flags = 0,
        .policy = doc_exmpl_genl_policy,
        .doit = doc_exmpl_echo,
        .dumpit = NULL,
};
	
//内核入口，注册generic netlink family/operations
static int __init genKernel_init(void) {
	 int rc;
	 printk("Generic Netlink Example Module inserted.\n");
        
	 rc = genl_register_family(&doc_exmpl_genl_family);
	 if (rc != 0) {
		  goto failure;
	 }
	 rc = genl_register_ops(&doc_exmpl_genl_family,&doc_exmpl_genl_ops_echo);
	 if (rc != 0) {
	 printk("Register ops: %i\n",rc);
	 genl_unregister_family(&doc_exmpl_genl_family);
	 goto failure;
	 }
	 return 0; 
	
	failure:
	 printk("Error occured while inserting generic netlink example module\n");
	 return -1;
}

static void __exit genKernel_exit(void) {
	 int ret;
	 printk("Generic Netlink Example Module unloaded.\n");
 
	 ret = genl_unregister_ops(&doc_exmpl_genl_family,&doc_exmpl_genl_ops_echo);
	 if(ret != 0) {
		  printk("Unregister ops failed: %i\n",ret);
		  return;
	 }	
	 ret = genl_unregister_family(&doc_exmpl_genl_family);
	 if(ret !=0) {
		  printk("Unregister family failed:%i\n",ret);
	 }
}

module_init(genKernel_init);
module_exit(genKernel_exit);
MODULE_LICENSE("GPL");


