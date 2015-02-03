.data
hello:
    .string "hello vonzhou\n"
.global main
main:
    movl $4,%eax
    movl $2,%ebx
    movl $hello, %ecx
    movl $14, %edx
    int $0x80
    movl $1, %eax
    xorl %ebx,%ebx
    int $0x80
    ret
