# UNPv2 4.10 为发送的消息增加消息头结构，而不是直接使用字节流
---

消息结构体是：

```C
struct mymesg {
  long	mesg_len;	/* #bytes in mesg_data, can be 0 */
  long	mesg_type;	/* message type, must be > 0 */
  char	mesg_data[MAXMESGDATA];
};
```

**注意：** 之前的代码有问题，应该是“(n = mesg_send(fd, mptr)) != (MESGHDRSIZE + mptr->mesg_len))” 否则总是发送失败。



