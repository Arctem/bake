#include "codegen/generator.h"
#include "codegen/director.h"

#define BICL "## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
              .globl Bool..vtable\n\
              Bool..vtable:           ## virtual function table for Bool\n\
              .quad string1\n\
              .quad Bool..new\n\
              .quad Object.abort\n\
              .quad Object.copy\n\
              .quad Object.type_name\n\
              ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
              .globl IO..vtable\n\
              IO..vtable:             ## virtual function table for IO\n\
              .quad string2\n\
              .quad IO..new\n\
              .quad Object.abort\n\
              .quad Object.copy\n\
              .quad Object.type_name\n\
              .quad IO.in_int\n\
              .quad IO.in_string\n\
              .quad IO.out_int\n\
              .quad IO.out_string\n\
              ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
              .globl Int..vtable\n\
              Int..vtable:            ## virtual function table for Int\n\
              .quad string3\n\
              .quad Int..new\n\
              .quad Object.abort\n\
              .quad Object.copy\n\
              .quad Object.type_name\n\
              ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
              Object..vtable:         ## virtual function table for Object\n\
              .quad string7\n\
              .quad Object..new\n\
              .quad Object.abort\n\
              .quad Object.copy\n\
              .quad Object.type_name\n\
              ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
              .globl String..vtable\n\
              String..vtable:         ## virtual function table for String\n\
              .quad string8\n\
              .quad String..new\n\
              .quad Object.abort\n\
              .quad Object.copy\n\
              .quad Object.type_name\n\
              .quad String.concat\n\
              .quad String.length\n\
              .quad String.substr\n\
              ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"

// built-in code definitions
#define BICD ".globl Bool..new\n\
Bool..new:              ## constructor for Bool\n\
                        pushq %rbp\n\
                        movq %rsp, %rbp\n\
                        ## stack room for temporaries: 1\n\
                        movq $8, %r14\n\
                        subq %r14, %rsp\n\
                        ## return address handling\n\
                        movq $4, %r12\n\
                        movq $8, %rsi\n\
      movq %r12, %rdi\n\
      call calloc\n\
      movq %rax, %r12\n\
                        ## store class tag, object size and vtable pointer\n\
                        movq $0, %r14\n\
                        movq %r14, 0(%r12)\n\
                        movq $4, %r14\n\
                        movq %r14, 8(%r12)\n\
                        movq $Bool..vtable, %r14\n\
                        movq %r14, 16(%r12)\n\
                        ## initialize attributes\n\
                        ## self[3] holds field (raw content) (Int)\n\
                        movq $0, %r13\n\
                        movq %r13, 24(%r12)\n\
                        ## self[3] (raw content) initializer -- none \n\
                        movq %r12, %r13\n\
                        ## return address handling\n\
                        movq %rbp, %rsp\n\
                        popq %rbp\n\
                        ret\n\
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
.globl IO..new\n\
IO..new:                ## constructor for IO\n\
                        pushq %rbp\n\
                        movq %rsp, %rbp\n\
                        ## stack room for temporaries: 1\n\
                        movq $8, %r14\n\
                        subq %r14, %rsp\n\
                        ## return address handling\n\
                        movq $3, %r12\n\
                        movq $8, %rsi\n\
      movq %r12, %rdi\n\
      call calloc\n\
      movq %rax, %r12\n\
                        ## store class tag, object size and vtable pointer\n\
                        movq $10, %r14\n\
                        movq %r14, 0(%r12)\n\
                        movq $3, %r14\n\
                        movq %r14, 8(%r12)\n\
                        movq $IO..vtable, %r14\n\
                        movq %r14, 16(%r12)\n\
                        movq %r12, %r13\n\
                        ## return address handling\n\
                        movq %rbp, %rsp\n\
                        popq %rbp\n\
                        ret\n\
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
.globl Int..new\n\
Int..new:               ## constructor for Int\n\
                        pushq %rbp\n\
                        movq %rsp, %rbp\n\
                        ## stack room for temporaries: 1\n\
                        movq $8, %r14\n\
                        subq %r14, %rsp\n\
                        ## return address handling\n\
                        movq $4, %r12\n\
                        movq $8, %rsi\n\
      movq %r12, %rdi\n\
      call calloc\n\
      movq %rax, %r12\n\
                        ## store class tag, object size and vtable pointer\n\
                        movq $1, %r14\n\
                        movq %r14, 0(%r12)\n\
                        movq $4, %r14\n\
                        movq %r14, 8(%r12)\n\
                        movq $Int..vtable, %r14\n\
                        movq %r14, 16(%r12)\n\
                        ## initialize attributes\n\
                        ## self[3] holds field (raw content) (Int)\n\
                        movq $0, %r13\n\
                        movq %r13, 24(%r12)\n\
                        ## self[3] (raw content) initializer -- none \n\
                        movq %r12, %r13\n\
                        ## return address handling\n\
                        movq %rbp, %rsp\n\
                        popq %rbp\n\
                        ret\n\
.globl Object..new\n\
Object..new:            ## constructor for Object\n\
                        pushq %rbp\n\
                        movq %rsp, %rbp\n\
                        ## stack room for temporaries: 1\n\
                        movq $8, %r14\n\
                        subq %r14, %rsp\n\
                        ## return address handling\n\
                        movq $3, %r12\n\
                        movq $8, %rsi\n\
      movq %r12, %rdi\n\
      call calloc\n\
      movq %rax, %r12\n\
                        ## store class tag, object size and vtable pointer\n\
                        movq $12, %r14\n\
                        movq %r14, 0(%r12)\n\
                        movq $3, %r14\n\
                        movq %r14, 8(%r12)\n\
                        movq $Object..vtable, %r14\n\
                        movq %r14, 16(%r12)\n\
                        movq %r12, %r13\n\
                        ## return address handling\n\
                        movq %rbp, %rsp\n\
                        popq %rbp\n\
                        ret\n\
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
.globl String..new\n\
String..new:            ## constructor for String\n\
                        pushq %rbp\n\
                        movq %rsp, %rbp\n\
                        ## stack room for temporaries: 1\n\
                        movq $8, %r14\n\
                        subq %r14, %rsp\n\
                        ## return address handling\n\
                        movq $4, %r12\n\
                        movq $8, %rsi\n\
      movq %r12, %rdi\n\
      call calloc\n\
      movq %rax, %r12\n\
                        ## store class tag, object size and vtable pointer\n\
                        movq $3, %r14\n\
                        movq %r14, 0(%r12)\n\
                        movq $4, %r14\n\
                        movq %r14, 8(%r12)\n\
                        movq $String..vtable, %r14\n\
                        movq %r14, 16(%r12)\n\
                        ## initialize attributes\n\
                        ## self[3] holds field (raw content) (String)\n\
                        movq $the.empty.string, %r13\n\
                        movq %r13, 24(%r12)\n\
                        ## self[3] (raw content) initializer -- none \n\
                        movq %r12, %r13\n\
                        ## return address handling\n\
                        movq %rbp, %rsp\n\
                        popq %rbp\n\
                        ret\n\
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
.globl Object.abort\n\
Object.abort:           ## method definition\n\
                        pushq %rbp\n\
                        movq %rsp, %rbp\n\
                        movq 16(%rbp), %r12\n\
                        ## stack room for temporaries: 1\n\
                        movq $8, %r14\n\
                        subq %r14, %rsp\n\
                        ## return address handling\n\
                        ## method body begins\n\
                        movq $string7, %r13\n\
                        movq %r13, %rdi\n\
      call cooloutstr\n\
                        movl $0, %edi\n\
      call exit\n\
.globl Object.abort.end\n\
Object.abort.end:       ## method body ends\n\
                        ## return address handling\n\
                        movq %rbp, %rsp\n\
                        popq %rbp\n\
                        ret\n\
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
.globl Object.copy\n\
Object.copy:            ## method definition\n\
                        pushq %rbp\n\
                        movq %rsp, %rbp\n\
                        movq 16(%rbp), %r12\n\
                        ## stack room for temporaries: 1\n\
                        movq $8, %r14\n\
                        subq %r14, %rsp\n\
                        ## return address handling\n\
                        ## method body begins\n\
                        movq 8(%r12), %r14\n\
                        movq $8, %rsi\n\
      movq %r14, %rdi\n\
      call calloc\n\
      movq %rax, %r13\n\
                        pushq %r13\n\
.globl l1\n\
l1:                     cmpq $0, %r14\n\
      je l2\n\
                        movq 0(%r12), %r15\n\
                        movq %r15, 0(%r13)\n\
                        movq $8, %r15\n\
                        addq %r15, %r12\n\
                        addq %r15, %r13\n\
                        movq $1, %r15\n\
                        subq %r15, %r14\n\
                        jmp l1\n\
.globl l2\n\
l2:                     ## done with Object.copy loop\n\
                        popq %r13\n\
.globl Object.copy.end\n\
Object.copy.end:        ## method body ends\n\
                        ## return address handling\n\
                        movq %rbp, %rsp\n\
                        popq %rbp\n\
                        ret\n\
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
.globl Object.type_name\n\
Object.type_name:       ## method definition\n\
                        pushq %rbp\n\
                        movq %rsp, %rbp\n\
                        movq 16(%rbp), %r12\n\
                        ## stack room for temporaries: 1\n\
                        movq $8, %r14\n\
                        subq %r14, %rsp\n\
                        ## return address handling\n\
                        ## method body begins\n\
                        ## new String\n\
                        pushq %rbp\n\
                        pushq %r12\n\
                        movq $String..new, %r14\n\
                        call *%r14\n\
                        popq %r12\n\
                        popq %rbp\n\
                        ## obtain vtable for self object\n\
                        movq 16(%r12), %r14\n\
                        ## look up type name at offset 0 in vtable\n\
                        movq 0(%r14), %r14\n\
                        movq %r14, 24(%r13)\n\
.globl Object.type_name.end\n\
Object.type_name.end:   ## method body ends\n\
                        ## return address handling\n\
                        movq %rbp, %rsp\n\
                        popq %rbp\n\
                        ret\n\
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
.globl IO.in_int\n\
IO.in_int:              ## method definition\n\
                        pushq %rbp\n\
                        movq %rsp, %rbp\n\
                        movq 16(%rbp), %r12\n\
                        ## stack room for temporaries: 1\n\
                        movq $8, %r14\n\
                        subq %r14, %rsp\n\
                        ## return address handling\n\
                        ## method body begins\n\
                        ## new Int\n\
                        pushq %rbp\n\
                        pushq %r12\n\
                        movq $Int..new, %r14\n\
                        call *%r14\n\
                        popq %r12\n\
                        popq %rbp\n\
                        movq %r13, %r14\n\
                        movl  $1, %esi\n\
      movl $4096, %edi\n\
      call calloc\n\
      pushq %rax\n\
      movq %rax, %rdi\n\
      movq $4096, %rsi \n\
      movq stdin(%rip), %rdx\n\
      call fgets \n\
      popq %rdi \n\
      movl $0, %eax\n\
      pushq %rax\n\
      movq %rsp, %rdx\n\
      movq $percent.ld, %rsi\n\
      call sscanf\n\
      popq %rax\n\
      movq $0, %rsi\n\
      cmpq $2147483647, %rax \n\
      cmovg %rsi, %rax\n\
      cmpq $-2147483648, %rax \n\
      cmovl %rsi, %rax\n\
      movq %rax, %r13\n\
                        movq %r13, 24(%r14)\n\
                        movq %r14, %r13\n\
.globl IO.in_int.end\n\
IO.in_int.end:          ## method body ends\n\
                        ## return address handling\n\
                        movq %rbp, %rsp\n\
                        popq %rbp\n\
                        ret\n\
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
.globl IO.in_string\n\
IO.in_string:           ## method definition\n\
                        pushq %rbp\n\
                        movq %rsp, %rbp\n\
                        movq 16(%rbp), %r12\n\
                        ## stack room for temporaries: 1\n\
                        movq $8, %r14\n\
                        subq %r14, %rsp\n\
                        ## return address handling\n\
                        ## method body begins\n\
                        ## new String\n\
                        pushq %rbp\n\
                        pushq %r12\n\
                        movq $String..new, %r14\n\
                        call *%r14\n\
                        popq %r12\n\
                        popq %rbp\n\
                        movq %r13, %r14\n\
                        call coolgetstr \n\
      movq %rax, %r13\n\
                        movq %r13, 24(%r14)\n\
                        movq %r14, %r13\n\
.globl IO.in_string.end\n\
IO.in_string.end:       ## method body ends\n\
                        ## return address handling\n\
                        movq %rbp, %rsp\n\
                        popq %rbp\n\
                        ret\n\
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
.globl IO.out_int\n\
IO.out_int:             ## method definition\n\
                        pushq %rbp\n\
                        movq %rsp, %rbp\n\
                        movq 24(%rbp), %r12\n\
                        ## stack room for temporaries: 1\n\
                        movq $8, %r14\n\
                        subq %r14, %rsp\n\
                        ## return address handling\n\
                        ## fp[3] holds argument x (Int)\n\
                        ## method body begins\n\
                        movq 16(%rbp), %r13\n\
                        movq $percent.d, %rdi\n\
    movl %r13d, %eax\n\
    cdqe\n\
    movq %rax, %rsi\n\
      movl $0, %eax\n\
      call printf\n\
                        movq %r12, %r13\n\
.globl IO.out_int.end\n\
IO.out_int.end:         ## method body ends\n\
                        ## return address handling\n\
                        movq %rbp, %rsp\n\
                        popq %rbp\n\
                        ret\n\
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
.globl IO.out_string\n\
IO.out_string:          ## method definition\n\
                        pushq %rbp\n\
                        movq %rsp, %rbp\n\
                        movq 16(%rbp), %r12\n\
                        ## stack room for temporaries: 1\n\
                        movq $8, %r14\n\
                        subq %r14, %rsp\n\
                        ## return address handling\n\
                        ## fp[3] holds argument x (String)\n\
                        ## method body begins\n\
                        movq 24(%rbp), %r14\n\
                        movq 24(%r14), %r13\n\
                        movq %r13, %rdi\n\
      call cooloutstr\n\
                        movq %r12, %r13\n\
.globl IO.out_string.end\n\
IO.out_string.end:      ## method body ends\n\
                        ## return address handling\n\
                        movq %rbp, %rsp\n\
                        popq %rbp\n\
                        ret\n\
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
.globl String.concat\n\
String.concat:          ## method definition\n\
                        pushq %rbp\n\
                        movq %rsp, %rbp\n\
                        movq 16(%rbp), %r12\n\
                        ## stack room for temporaries: 1\n\
                        movq $8, %r14\n\
                        subq %r14, %rsp\n\
                        ## return address handling\n\
                        ## fp[3] holds argument s (String)\n\
                        ## method body begins\n\
                        ## new String\n\
                        pushq %rbp\n\
                        pushq %r12\n\
                        movq $String..new, %r14\n\
                        call *%r14\n\
                        popq %r12\n\
                        popq %rbp\n\
                        movq %r13, %r15\n\
                        movq 24(%rbp), %r14\n\
                        movq 24(%r14), %r14\n\
                        movq 24(%r12), %r13\n\
                        movq %r13, %rdi\n\
      movq %r14, %rsi\n\
      call coolstrcat\n\
      movq %rax, %r13\n\
                        movq %r13, 24(%r15)\n\
                        movq %r15, %r13\n\
.globl String.concat.end\n\
String.concat.end:      ## method body ends\n\
                        ## return address handling\n\
                        movq %rbp, %rsp\n\
                        popq %rbp\n\
                        ret\n\
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
.globl String.length\n\
String.length:          ## method definition\n\
                        pushq %rbp\n\
                        movq %rsp, %rbp\n\
                        movq 16(%rbp), %r12\n\
                        ## stack room for temporaries: 1\n\
                        movq $8, %r14\n\
                        subq %r14, %rsp\n\
                        ## return address handling\n\
                        ## method body begins\n\
                        ## new Int\n\
                        pushq %rbp\n\
                        pushq %r12\n\
                        movq $Int..new, %r14\n\
                        call *%r14\n\
                        popq %r12\n\
                        popq %rbp\n\
                        movq %r13, %r14\n\
                        movq 24(%r12), %r13\n\
                        movq %r13, %rdi\n\
      movl $0, %eax\n\
      call coolstrlen\n\
      movq %rax, %r13\n\
                        movq %r13, 24(%r14)\n\
                        movq %r14, %r13\n\
.globl String.length.end\n\
String.length.end:      ## method body ends\n\
                        ## return address handling\n\
                        movq %rbp, %rsp\n\
                        popq %rbp\n\
                        ret\n\
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
.globl String.substr\n\
String.substr:          ## method definition\n\
                        pushq %rbp\n\
                        movq %rsp, %rbp\n\
                        movq 16(%rbp), %r12\n\
                        ## stack room for temporaries: 1\n\
                        movq $8, %r14\n\
                        subq %r14, %rsp\n\
                        ## return address handling\n\
                        ## fp[4] holds argument i (Int)\n\
                        ## fp[3] holds argument l (Int)\n\
                        ## method body begins\n\
                        ## new String\n\
                        pushq %rbp\n\
                        pushq %r12\n\
                        movq $String..new, %r14\n\
                        call *%r14\n\
                        popq %r12\n\
                        popq %rbp\n\
                        movq %r13, %r15\n\
                        movq 24(%rbp), %r14\n\
                        movq 24(%r14), %r14\n\
                        movq 32(%rbp), %r13\n\
                        movq 24(%r13), %r13\n\
                        movq 24(%r12), %r12\n\
                        movq %r12, %rdi\n\
      movq %r13, %rsi\n\
      movq %r14, %rdx\n\
      call coolsubstr\n\
      movq %rax, %r13\n\
                        cmpq $0, %r13\n\
      jne l3\n\
                        movq $string9, %r13\n\
                        movq %r13, %rdi\n\
      call cooloutstr\n\
                        movl $0, %edi\n\
      call exit\n\
.globl l3\n\
l3:                     movq %r13, 24(%r15)\n\
                        movq %r15, %r13\n\
.globl String.substr.end\n\
String.substr.end:      ## method body ends\n\
                        ## return address handling\n\
                        movq %rbp, %rsp\n\
                        popq %rbp\n\
                        ret\n\
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\
.globl the.empty.string\n\
the.empty.string:       # \"\"\n\
.byte 0\n\
\
.globl percent.d\n\
percent.d : # \"%ld\"\n\
.byte  37 # '%'\n\
.byte 108 # 'l'\n\
.byte 100 # 'd'\n\
.byte 0\n\
\
.globl percent.ld\n\
percent.ld:             # \"%ld\"\n\
.byte  32 # ' '\n\
.byte  37 # '%'\n\
.byte 108 # 'l'\n\
.byte 100 # 'd'\n\
.byte 0\n\
\
.globl string1\n\
string1:                #\"Bool\"\n\
  .byte  66 # 'B'\n\
  .byte 111 # 'o'\n\
  .byte 111 # 'o'\n\
  .byte 108 # 'l'\n\
  .byte 0\n\
\n\
  .globl string2\n\
  string2 : # \"IO\"\n\
  .byte  73 # 'I'\n\
  .byte  79 # 'O'\n\
  .byte 0\n\
\n\
  .globl string3\n\
  string3 : # \"Int\"\n\
  .byte  73 # 'I'\n\
  .byte 110 # 'n'\n\
  .byte 116 # 't'\n\
  .byte 0\n\
\n\
  .globl string4\n\
  string4 : # \"Main\"\n\
  .byte  77 # 'M'\n\
  .byte  97 # 'a'\n\
  .byte 105 # 'i'\n\
  .byte 110 # 'n'\n\
  .byte 0\n\
\n\
  .globl string5\n\
  string5 : # \"Object\"\n\
  .byte  79 # 'O'\n\
  .byte  98 # 'b'\n\
  .byte 106 # 'j'\n\
  .byte 101 # 'e'\n\
  .byte  99 # 'c'\n\
  .byte 116 # 't'\n\
  .byte 0\n\
\n\
  .globl string6\n\
  string6 : # \"String\"\n\
  .byte  83 # 'S'\n\
  .byte 116 # 't'\n\
  .byte 114 # 'r'\n\
  .byte 105 # 'i'\n\
  .byte 110 # 'n'\n\
  .byte 103 # 'g'\n\
  .byte 0\n\
\n\
  .globl string7\n\
  string7 : # \"abort\\n\"\n\
  .byte  97 # 'a'\n\
  .byte  98 # 'b'\n\
  .byte 111 # 'o'\n\
  .byte 114 # 'r'\n\
  .byte 116 # 't'\n\
  .byte  92 # '\\'\n\
  .byte 110 # 'n'\n\
  .byte 0\n\
\n\
  .globl string8\n\
  string8 : # \"Hello, world!\\n\"\n\
  .byte  72 # 'H'\n\
  .byte 101 # 'e'\n\
  .byte 108 # 'l'\n\
  .byte 108 # 'l'\n\
  .byte 111 # 'o'\n\
  .byte  44 # ','\n\
  .byte  32 # ' '\n\
  .byte 119 # 'w'\n\
  .byte 111 # 'o'\n\
  .byte 114 # 'r'\n\
  .byte 108 # 'l'\n\
  .byte 100 # 'd'\n\
  .byte  33 # '!'\n\
  .byte  92 # '\\'\n\
  .byte 110 # 'n'\n\
  .byte 0\n\
\n\
  .globl string9\n\
  string9 : # \"ERROR: 0: Exception: String.substr out of range\\n\"\n\
  .byte  69 # 'E'\n\
  .byte  82 # 'R'\n\
  .byte  82 # 'R'\n\
  .byte  79 # 'O'\n\
  .byte  82 # 'R'\n\
  .byte  58 # ':'\n\
  .byte  32 # ' '\n\
  .byte  48 # '0'\n\
  .byte  58 # ':'\n\
  .byte  32 # ' '\n\
  .byte  69 # 'E'\n\
  .byte 120 # 'x'\n\
  .byte  99 # 'c'\n\
  .byte 101 # 'e'\n\
  .byte 112 # 'p'\n\
  .byte 116 # 't'\n\
  .byte 105 # 'i'\n\
  .byte 111 # 'o'\n\
  .byte 110 # 'n'\n\
  .byte  58 # ':'\n\
  .byte  32 # ' '\n\
  .byte  83 # 'S'\n\
  .byte 116 # 't'\n\
  .byte 114 # 'r'\n\
  .byte 105 # 'i'\n\
  .byte 110 # 'n'\n\
  .byte 103 # 'g'\n\
  .byte  46 # '.'\n\
  .byte 115 # 's'\n\
  .byte 117 # 'u'\n\
  .byte  98 # 'b'\n\
  .byte 115 # 's'\n\
  .byte 116 # 't'\n\
  .byte 114 # 'r'\n\
  .byte  32 # ' '\n\
  .byte 111 # 'o'\n\
  .byte 117 # 'u'\n\
  .byte 116 # 't'\n\
  .byte  32 # ' '\n\
  .byte 111 # 'o'\n\
  .byte 102 # 'f'\n\
  .byte  32 # ' '\n\
  .byte 114 # 'r'\n\
  .byte  97 # 'a'\n\
  .byte 110 # 'n'\n\
  .byte 103 # 'g'\n\
  .byte 101 # 'e'\n\
  .byte  92 # '\\'\n\
  .byte 110 # 'n'\n\
  .byte 0\n\
\n\
                        .globl cooloutstr\n\
  .type cooloutstr, @function\n\
cooloutstr:\n\
.LFB0:\n\
  .cfi_startproc\n\
  pushq %rbp\n\
  .cfi_def_cfa_offset 16\n\
  .cfi_offset 6, -16\n\
  movq  %rsp, %rbp\n\
  .cfi_def_cfa_register 6\n\
  subq  $32, %rsp\n\
  movq  %rdi, -24(%rbp)\n\
  movl  $0, -4(%rbp)\n\
  jmp .L2\n\
.L5:\n\
  movl  -4(%rbp), %eax\n\
  cltq\n\
  addq  -24(%rbp), %rax\n\
  movzbl  (%rax), %eax\n\
  cmpb  $92, %al\n\
  jne .L3\n\
  movl  -4(%rbp), %eax\n\
  cltq\n\
  addq  $1, %rax\n\
  addq  -24(%rbp), %rax\n\
  movzbl  (%rax), %eax\n\
  cmpb  $110, %al\n\
  jne .L3\n\
  movq  stdout(%rip), %rax\n\
  movq  %rax, %rsi\n\
  movl  $10, %edi\n\
  call  fputc\n\
  addl  $2, -4(%rbp)\n\
  jmp .L2\n\
.L3:\n\
  movl  -4(%rbp), %eax\n\
  cltq\n\
  addq  -24(%rbp), %rax\n\
  movzbl  (%rax), %eax\n\
  cmpb  $92, %al\n\
  jne .L4\n\
  movl  -4(%rbp), %eax\n\
  cltq\n\
  addq  $1, %rax\n\
  addq  -24(%rbp), %rax\n\
  movzbl  (%rax), %eax\n\
  cmpb  $116, %al\n\
  jne .L4\n\
  movq  stdout(%rip), %rax\n\
  movq  %rax, %rsi\n\
  movl  $9, %edi\n\
  call  fputc\n\
  addl  $2, -4(%rbp)\n\
  jmp .L2\n\
.L4:\n\
  movq  stdout(%rip), %rdx\n\
  movl  -4(%rbp), %eax\n\
  cltq\n\
  addq  -24(%rbp), %rax\n\
  movzbl  (%rax), %eax\n\
  movsbl  %al, %eax\n\
  movq  %rdx, %rsi\n\
  movl  %eax, %edi\n\
  call  fputc\n\
  addl  $1, -4(%rbp)\n\
.L2:\n\
  movl  -4(%rbp), %eax\n\
  cltq\n\
  addq  -24(%rbp), %rax\n\
  movzbl  (%rax), %eax\n\
  testb %al, %al\n\
  jne .L5\n\
  movq  stdout(%rip), %rax\n\
  movq  %rax, %rdi\n\
  call  fflush\n\
  leave\n\
  .cfi_def_cfa 7, 8\n\
  ret\n\
  .cfi_endproc\n\
  .LFE0:\n\
  .size cooloutstr, .-cooloutstr\n\
.globl coolstrlen\n\
  .type coolstrlen, @function\n\
coolstrlen:\n\
.LFB1:\n\
  .cfi_startproc\n\
  pushq %rbp\n\
  .cfi_def_cfa_offset 16\n\
  .cfi_offset 6, -16\n\
  movq  %rsp, %rbp\n\
  .cfi_def_cfa_register 6\n\
  movq  %rdi, -24(%rbp)\n\
  movl  $0, -4(%rbp)\n\
  jmp .L7\n\
.L8:\n\
  movl  -4(%rbp), %eax\n\
  addl  $1, %eax\n\
  movl  %eax, -4(%rbp)\n\
.L7:\n\
  movl  -4(%rbp), %eax\n\
  mov %eax, %eax\n\
  addq  -24(%rbp), %rax\n\
  movzbl  (%rax), %eax\n\
  testb %al, %al\n\
  jne .L8\n\
  movl  -4(%rbp), %eax\n\
  leave\n\
  .cfi_def_cfa 7, 8\n\
  ret\n\
  .cfi_endproc\n\
.LFE1:\n\
  .size coolstrlen, .-coolstrlen\n\
  .section  .rodata\n\
.LC0:\n\
  .string \"%s%s\"\n\
  .text\n\
.globl coolstrcat\n\
  .type coolstrcat, @function\n\
coolstrcat:\n\
.LFB2:\n\
  .cfi_startproc\n\
  pushq %rbp\n\
  .cfi_def_cfa_offset 16\n\
  .cfi_offset 6, -16\n\
  movq  %rsp, %rbp\n\
  .cfi_def_cfa_register 6\n\
  pushq %rbx\n\
  subq  $40, %rsp\n\
  movq  %rdi, -40(%rbp)\n\
  movq  %rsi, -48(%rbp)\n\
  cmpq  $0, -40(%rbp)\n\
  jne .L10\n\
  .cfi_offset 3, -24\n\
  movq  -48(%rbp), %rax\n\
  jmp .L11\n\
.L10:\n\
  cmpq  $0, -48(%rbp)\n\
  jne .L12\n\
  movq  -40(%rbp), %rax\n\
  jmp .L11\n\
.L12:\n\
  movq  -40(%rbp), %rax\n\
  movq  %rax, %rdi\n\
  call  coolstrlen\n\
  movl  %eax, %ebx\n\
  movq  -48(%rbp), %rax\n\
  movq  %rax, %rdi\n\
  call  coolstrlen\n\
  leal  (%rbx,%rax), %eax\n\
  addl  $1, %eax\n\
  movl  %eax, -20(%rbp)\n\
  movl  -20(%rbp), %eax\n\
  cltq\n\
  movl  $1, %esi\n\
  movq  %rax, %rdi\n\
  call  calloc\n\
  movq  %rax, -32(%rbp)\n\
  movl  $.LC0, %edx\n\
  movl  -20(%rbp), %eax\n\
  movslq  %eax, %rbx\n\
  movq  -48(%rbp), %rsi\n\
  movq  -40(%rbp), %rcx\n\
  movq  -32(%rbp), %rax\n\
  movq  %rsi, %r8\n\
  movq  %rbx, %rsi\n\
  movq  %rax, %rdi\n\
  movl  $0, %eax\n\
  call  snprintf\n\
  movq  -32(%rbp), %rax\n\
.L11:\n\
  addq  $40, %rsp\n\
  popq  %rbx\n\
  leave\n\
  .cfi_def_cfa 7, 8\n\
  ret\n\
  .cfi_endproc\n\
.LFE2:\n\
  .size coolstrcat, .-coolstrcat\n\
  .section  .rodata\n\
.LC1:\n\
  .string \"\"\n\
  .text\n\
.globl coolgetstr\n\
  .type coolgetstr, @function\n\
coolgetstr:\n\
.LFB3:\n\
  .cfi_startproc\n\
  pushq %rbp\n\
  .cfi_def_cfa_offset 16\n\
  .cfi_offset 6, -16\n\
  movq  %rsp, %rbp\n\
  .cfi_def_cfa_register 6\n\
  subq  $32, %rsp\n\
  movl  $1, %esi\n\
  movl  $40960, %edi\n\
  call  calloc\n\
  movq  %rax, -16(%rbp)\n\
  movl  $0, -4(%rbp)\n\
.L20:\n\
  movq  stdin(%rip), %rax\n\
  movq  %rax, %rdi\n\
  call  fgetc\n\
  movl  %eax, -20(%rbp)\n\
  cmpl  $-1, -20(%rbp)\n\
  je  .L14\n\
  cmpl  $10, -20(%rbp)\n\
  jne .L15\n\
.L14:\n\
  cmpl  $0, -4(%rbp)\n\
  je  .L16\n\
  movl  $.LC1, %eax\n\
  jmp .L17\n\
.L16:\n\
  movq  -16(%rbp), %rax\n\
  jmp .L17\n\
.L15:\n\
  cmpl  $0, -20(%rbp)\n\
  jne .L18\n\
  movl  $1, -4(%rbp)\n\
  jmp .L20\n\
.L18:\n\
  movq  -16(%rbp), %rax\n\
  movq  %rax, %rdi\n\
  call  coolstrlen\n\
  mov %eax, %eax\n\
  addq  -16(%rbp), %rax\n\
  movl  -20(%rbp), %edx\n\
  movb  %dl, (%rax)\n\
  jmp .L20\n\
.L17:\n\
  leave\n\
  .cfi_def_cfa 7, 8\n\
  ret\n\
  .cfi_endproc\n\
.LFE3:\n\
  .size coolgetstr, .-coolgetstr\n\
.globl coolsubstr\n\
  .type coolsubstr, @function\n\
coolsubstr:\n\
.LFB4:\n\
  .cfi_startproc\n\
  pushq %rbp\n\
  .cfi_def_cfa_offset 16\n\
  .cfi_offset 6, -16\n\
  movq  %rsp, %rbp\n\
  .cfi_def_cfa_register 6\n\
  subq  $48, %rsp\n\
  movq  %rdi, -24(%rbp)\n\
  movq  %rsi, -32(%rbp)\n\
  movq  %rdx, -40(%rbp)\n\
  movq  -24(%rbp), %rax\n\
  movq  %rax, %rdi\n\
  call  coolstrlen\n\
  movl  %eax, -4(%rbp)\n\
  cmpq  $0, -32(%rbp)\n\
  js  .L22\n\
  cmpq  $0, -40(%rbp)\n\
  js  .L22\n\
  movq  -40(%rbp), %rax\n\
  movq  -32(%rbp), %rdx\n\
  addq  %rax, %rdx\n\
  movl  -4(%rbp), %eax\n\
  cltq\n\
  cmpq  %rax, %rdx\n\
  jle .L23\n\
.L22:\n\
  movl  $0, %eax\n\
  jmp .L24\n\
.L23:\n\
  movq  -40(%rbp), %rdx\n\
  movq  -32(%rbp), %rax\n\
  addq  -24(%rbp), %rax\n\
  movq  %rdx, %rsi\n\
  movq  %rax, %rdi\n\
  call  strndup\n\
.L24:\n\
  leave\n\
  .cfi_def_cfa 7, 8\n\
  ret\n\
  .cfi_endproc\n\
.LFE4:\n\
  .size coolsubstr, .-coolsubstr\n"
// end built in code definitions

namespace codegen {
  std::string* Generator::generateBuiltInClassList() { return new std::string(BICL); }
  std::string* Generator::generateBuiltInMethods() { return new std::string(BICD); }

  void Generator::addToDataList(std::string* s) {
    Director* d = Director::getInstance();

    std::cout << "adding to data list" << std::endl; // TEST
    d->addToDataList(s);
  }

  void Generator::pushAll() {
    for (int i = 0; i < Allocator::regNum; i++) {
      this->genPush(Allocator::getRegister(i));
    }
  }

  void Generator::popAll() {
    for (int i = Allocator::regNum - 1; i >= 0; i--) {
      this->genPop(Allocator::getRegister(i));
    }
  }

  void Generator::genNoOp() {
    Director* d = Director::getInstance();

    std::cout << "generating nop" << std::endl; // TEST
    d->addToBlockList(new string("nop"));
  }

  void Generator::fnop() {
    Director* d = Director::getInstance();

    std::cout << "generating fnop" << std::endl; // TEST
    d->addToBlockList(new string("fnop"));
  }

  void Generator::genLabel(std::string label) {
    Director* d = Director::getInstance();
    std::cout << "generating label" << std::endl; // TEST
    string* s = new string(label + ":");

    d->addToBlockList(s);
  }

  // start of data movement
  void Generator::genMov(std::string r1, std::string r2) {
    Director* d = Director::getInstance();
    std::cout << "generating mov" << std::endl; // TEST
    string* s = new string("movq " + r1 + ", " + r2);

    d->addToBlockList(s);
  }

  void Generator::genCopy(std::string r1, std::string r2) {
    Director* d = Director::getInstance();
    std::cout << "Generating copy" << std::endl; // TEST

    string* s = new string("copy " + r1 + ", " + r2);

    d->addToBlockList(s);
  }
  //end of data movement

  // basic integer arithmatic

  void Generator::genAdd(std::string r1, std::string r2) {
    Director* d = Director::getInstance();
    std::cout << "generating add" << std::endl; // TEST
    string* s = new string("addq " + r1 + ", " + r2);

    d->addToBlockList(s);
  }

  void Generator::genSub(std::string r1, std::string r2) {
    Director* d = Director::getInstance();
    std::cout << "generating sub" << std::endl; // TEST
    string* s = new string("subq " + r1 + ", " + r2);

    d->addToBlockList(s);
  }

  /**
  * This is a weird command to generate. It needs to be done precisely with the register allocator.
  * It multiplies the argument register given with RAX. "mulq %r8" multiplies RAX * R8.
  * It then stores the lower part of the multiplication (odds are the result is larger than 64 bits) in RAX.
  * The higher part is stored in RDX.
  **/
  void Generator::genMul(std::string r1) {
    Director* d = Director::getInstance();
    std::cout << "generatring mul" << std::endl; // TEST
    string* s = new string("mul " + r1);

    d->addToBlockList(s);
  }

  /**
  * This is very similar to multiplication. "div %r8" performs RAX/R8.
  * The quotient is stored in RAX. The remainder is stored in RDX.
  **/
  void Generator::genDiv(std::string r1) {
    Director* d = Director::getInstance();
    std::cout << "generatring div" << std::endl; // TEST
    string* s = new string("div " + r1);

    d->addToBlockList(s);
  }

  /**
  * This just negates the value of the register.
  */
  void Generator::genNeg(std::string r1) {
    Director* d = Director::getInstance();
    std::cout << "generating neg" << std::endl; // TEST

    string* s = new string("neg " + r1);
    d->addToBlockList(s);
  }
  // end basic integer arithmatic

  // begin stack operations

  void Generator::genPush(std::string src) {
    Director* d = Director::getInstance();
    std::cout << "generating push" << std::endl; // TEST

    string* s = new string("pushq " + src);
    d->addToBlockList(s);
  }

  void Generator::genPop(std::string dest) {
    Director* d = Director::getInstance();
    std::cout << "generating pop" << std::endl; // TEST

    string* s = new string("popq " + dest);
    d->addToBlockList(s);
  }
  // end stack operations

  // begin misc ops
  void Generator::genXchg(std::string r1, std::string r2) {
    Director* d = Director::getInstance();
    std::cout << "generating xchg" << std::endl; // TEST

    string* s = new string("xchg " + r1 + ", " + r2);
    d->addToBlockList(s);
  }
  // end misc ops

  // begin control flow ops
  void Generator::genJmp(std::string label) {
    Director* d = Director::getInstance();
    std::cout << "generating br" << std::endl; // TEST

    string* s = new string("jmp " + label);
    d->addToBlockList(s);
  }

  void Generator::genCall(std::string func) {
    Director* d = Director::getInstance();
    std::cout << "generating call" << std::endl; // TEST

    string* s = new string("call " + func);
    d->addToBlockList(s);
  }
}
