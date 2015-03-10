
1. 打印线程ID  --threadids;
2. 获得线程的退出状态 -- exitstatus ;
3. 在把自动变量作为pthread_exit的参数时发生的问题    --badexit ;
4. 线程清理处理程序 -- cleanup;
4. 使用互斥量保护数据结构  mutex1;
5. 两个互斥量的使用方法  mutex2;
8. 使用读写锁   -- rwlock ;









(1) 子线程循环10次 主线程循环100次 接着子线程10次 主线程100次  如此循环50次  使用条件变量实现  TwoThreadLoop ;
(2) 编写一个程序 开启3个线程ID分别为A,B,C 每个线程将自己的ID打印到屏幕上10遍 输出的结果按照ABC的顺序 如ABCABC...一次类推   ThreeThreadPrintABC;
(3) 有四个线程1 2 3 4,线程1输出1 线程2输出2以此类推 现有四个文件ABCD 初始为空 现在让四个文件呈现如下格式：A-123412.. B-23412341.. C-34123412.. D-41234123.. Print1234ToFiles ;
(4) 生产者消费者问题：   
用条件变量实现  -- ProducerConsumer1 ;
用信号量实现       -- ProducerCusumer2 ;

(5) 读者写者问题：有一个写者很多读者 多个读者可以同时读文件 写者在写文件时不许读 同样有读者时不能写 ReaderWriter ;


