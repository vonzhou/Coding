
ptrace0 - 在tracer收到由于系统调用而来的控制时，设置单步执行 从而简单对指令计数
ptrace1 - 得到系统调用号 
ptrace2 - 获得系统调用的参数 和 返回值 PTRACE_SYSCALL 设置的是在系统调用的入口和出口
都会停止子进程的执行，这样可以在write退出的时候从eax寄存器得到它的返回值 
ptrace3 - 利用PTRACE_GETREGS获得系统调用时寄存器值
ptrace4 - 改变tracee中的内存单元内容 每次读取的是一个word
ptrace5 - 在系统调用之后单步执行，获得正在执行的指令

