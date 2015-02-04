
int main(){
    __asm__(
            "jmp forward;"
    "backward:popl %esi;"
            "movl $4, %eax;"
            "movl $2, %ebx;"
            "movl %esi, %ecx;"
            "movl $12, %edx;"
            "int $0x80;"
            "int3;"
    "forward:call backward;"
            ".string \"Hello World\\n\";"
        );
}
