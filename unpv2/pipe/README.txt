1. 使用两个pipe实现全双工通信的 客户-服务器程序  mainpipe;
2. 测试linux是否支持默认的全双工 fduplex;
3. 使用popen    --mainpopen ;
R:APUE14.3
4.使用具名管道FIFO   -- mainfifo;
5. 无亲缘关系的俩进程使用FIFO   -- mainfifo2 ;
6. 单个服务器多个客户 使用FIFO通信  -- fifocliserv ;
7. 给管道增加消息头结构    -- pipemesg ;


### sibling communicate by pipe, 2015-8-22 
利用pipe实现兄弟进程之间的通信 sibling-pipe.c

###







