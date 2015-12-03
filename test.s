## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
              .globl Bool..vtable
              Bool..vtable:           ## virtual function table for Bool
              .quad string1
              .quad Bool..new
              .quad Object.abort
              .quad Object.copy
              .quad Object.type_name
              ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
              .globl IO..vtable
              IO..vtable:             ## virtual function table for IO
              .quad string2
              .quad IO..new
              .quad Object.abort
              .quad Object.copy
              .quad Object.type_name
              .quad IO.in_int
              .quad IO.in_string
              .quad IO.out_int
              .quad IO.out_string
              ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
              .globl Int..vtable
              Int..vtable:            ## virtual function table for Int
              .quad string3
              .quad Int..new
              .quad Object.abort
              .quad Object.copy
              .quad Object.type_name
              ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
              Object..vtable:         ## virtual function table for Object
              .quad string7
              .quad Object..new
              .quad Object.abort
              .quad Object.copy
              .quad Object.type_name
              ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
              .globl String..vtable
              String..vtable:         ## virtual function table for String
              .quad string8
              .quad String..new
              .quad Object.abort
              .quad Object.copy
              .quad Object.type_name
              .quad String.concat
              .quad String.length
              .quad String.substr
              ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.globl Bool..new
Bool..new:              ## constructor for Bool
                        pushq %rbp
                        movq %rsp, %rbp
                        ## stack room for temporaries: 1
                        movq $8, %r14
                        subq %r14, %rsp
                        ## return address handling
                        movq $4, %r12
                        movq $8, %rsi
      movq %r12, %rdi
      call calloc
      movq %rax, %r12
                        ## store class tag, object size and vtable pointer
                        movq $0, %r14
                        movq %r14, 0(%r12)
                        movq $4, %r14
                        movq %r14, 8(%r12)
                        movq $Bool..vtable, %r14
                        movq %r14, 16(%r12)
                        ## initialize attributes
                        ## self[3] holds field (raw content) (Int)
                        movq $0, %r13
                        movq %r13, 24(%r12)
                        ## self[3] (raw content) initializer -- none 
                        movq %r12, %r13
                        ## return address handling
                        movq %rbp, %rsp
                        popq %rbp
                        ret
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.globl IO..new
IO..new:                ## constructor for IO
                        pushq %rbp
                        movq %rsp, %rbp
                        ## stack room for temporaries: 1
                        movq $8, %r14
                        subq %r14, %rsp
                        ## return address handling
                        movq $3, %r12
                        movq $8, %rsi
      movq %r12, %rdi
      call calloc
      movq %rax, %r12
                        ## store class tag, object size and vtable pointer
                        movq $10, %r14
                        movq %r14, 0(%r12)
                        movq $3, %r14
                        movq %r14, 8(%r12)
                        movq $IO..vtable, %r14
                        movq %r14, 16(%r12)
                        movq %r12, %r13
                        ## return address handling
                        movq %rbp, %rsp
                        popq %rbp
                        ret
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.globl Int..new
Int..new:               ## constructor for Int
                        pushq %rbp
                        movq %rsp, %rbp
                        ## stack room for temporaries: 1
                        movq $8, %r14
                        subq %r14, %rsp
                        ## return address handling
                        movq $4, %r12
                        movq $8, %rsi
      movq %r12, %rdi
      call calloc
      movq %rax, %r12
                        ## store class tag, object size and vtable pointer
                        movq $1, %r14
                        movq %r14, 0(%r12)
                        movq $4, %r14
                        movq %r14, 8(%r12)
                        movq $Int..vtable, %r14
                        movq %r14, 16(%r12)
                        ## initialize attributes
                        ## self[3] holds field (raw content) (Int)
                        movq $0, %r13
                        movq %r13, 24(%r12)
                        ## self[3] (raw content) initializer -- none 
                        movq %r12, %r13
                        ## return address handling
                        movq %rbp, %rsp
                        popq %rbp
                        ret
.globl Object..new
Object..new:            ## constructor for Object
                        pushq %rbp
                        movq %rsp, %rbp
                        ## stack room for temporaries: 1
                        movq $8, %r14
                        subq %r14, %rsp
                        ## return address handling
                        movq $3, %r12
                        movq $8, %rsi
      movq %r12, %rdi
      call calloc
      movq %rax, %r12
                        ## store class tag, object size and vtable pointer
                        movq $12, %r14
                        movq %r14, 0(%r12)
                        movq $3, %r14
                        movq %r14, 8(%r12)
                        movq $Object..vtable, %r14
                        movq %r14, 16(%r12)
                        movq %r12, %r13
                        ## return address handling
                        movq %rbp, %rsp
                        popq %rbp
                        ret
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.globl String..new
String..new:            ## constructor for String
                        pushq %rbp
                        movq %rsp, %rbp
                        ## stack room for temporaries: 1
                        movq $8, %r14
                        subq %r14, %rsp
                        ## return address handling
                        movq $4, %r12
                        movq $8, %rsi
      movq %r12, %rdi
      call calloc
      movq %rax, %r12
                        ## store class tag, object size and vtable pointer
                        movq $3, %r14
                        movq %r14, 0(%r12)
                        movq $4, %r14
                        movq %r14, 8(%r12)
                        movq $String..vtable, %r14
                        movq %r14, 16(%r12)
                        ## initialize attributes
                        ## self[3] holds field (raw content) (String)
                        movq $the.empty.string, %r13
                        movq %r13, 24(%r12)
                        ## self[3] (raw content) initializer -- none 
                        movq %r12, %r13
                        ## return address handling
                        movq %rbp, %rsp
                        popq %rbp
                        ret
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.globl Object.abort
Object.abort:           ## method definition
                        pushq %rbp
                        movq %rsp, %rbp
                        movq 16(%rbp), %r12
                        ## stack room for temporaries: 1
                        movq $8, %r14
                        subq %r14, %rsp
                        ## return address handling
                        ## method body begins
                        movq $string7, %r13
                        movq %r13, %rdi
      call cooloutstr
                        movl $0, %edi
      call exit
.globl Object.abort.end
Object.abort.end:       ## method body ends
                        ## return address handling
                        movq %rbp, %rsp
                        popq %rbp
                        ret
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.globl Object.copy
Object.copy:            ## method definition
                        pushq %rbp
                        movq %rsp, %rbp
                        movq 16(%rbp), %r12
                        ## stack room for temporaries: 1
                        movq $8, %r14
                        subq %r14, %rsp
                        ## return address handling
                        ## method body begins
                        movq 8(%r12), %r14
                        movq $8, %rsi
      movq %r14, %rdi
      call calloc
      movq %rax, %r13
                        pushq %r13
.globl l1
l1:                     cmpq $0, %r14
      je l2
                        movq 0(%r12), %r15
                        movq %r15, 0(%r13)
                        movq $8, %r15
                        addq %r15, %r12
                        addq %r15, %r13
                        movq $1, %r15
                        subq %r15, %r14
                        jmp l1
.globl l2
l2:                     ## done with Object.copy loop
                        popq %r13
.globl Object.copy.end
Object.copy.end:        ## method body ends
                        ## return address handling
                        movq %rbp, %rsp
                        popq %rbp
                        ret
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.globl Object.type_name
Object.type_name:       ## method definition
                        pushq %rbp
                        movq %rsp, %rbp
                        movq 16(%rbp), %r12
                        ## stack room for temporaries: 1
                        movq $8, %r14
                        subq %r14, %rsp
                        ## return address handling
                        ## method body begins
                        ## new String
                        pushq %rbp
                        pushq %r12
                        movq $String..new, %r14
                        call *%r14
                        popq %r12
                        popq %rbp
                        ## obtain vtable for self object
                        movq 16(%r12), %r14
                        ## look up type name at offset 0 in vtable
                        movq 0(%r14), %r14
                        movq %r14, 24(%r13)
.globl Object.type_name.end
Object.type_name.end:   ## method body ends
                        ## return address handling
                        movq %rbp, %rsp
                        popq %rbp
                        ret
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.globl IO.in_int
IO.in_int:              ## method definition
                        pushq %rbp
                        movq %rsp, %rbp
                        movq 16(%rbp), %r12
                        ## stack room for temporaries: 1
                        movq $8, %r14
                        subq %r14, %rsp
                        ## return address handling
                        ## method body begins
                        ## new Int
                        pushq %rbp
                        pushq %r12
                        movq $Int..new, %r14
                        call *%r14
                        popq %r12
                        popq %rbp
                        movq %r13, %r14
                        movl  $1, %esi
      movl $4096, %edi
      call calloc
      pushq %rax
      movq %rax, %rdi
      movq $4096, %rsi 
      movq stdin(%rip), %rdx
      call fgets 
      popq %rdi 
      movl $0, %eax
      pushq %rax
      movq %rsp, %rdx
      movq $percent.ld, %rsi
      call sscanf
      popq %rax
      movq $0, %rsi
      cmpq $2147483647, %rax 
      cmovg %rsi, %rax
      cmpq $-2147483648, %rax 
      cmovl %rsi, %rax
      movq %rax, %r13
                        movq %r13, 24(%r14)
                        movq %r14, %r13
.globl IO.in_int.end
IO.in_int.end:          ## method body ends
                        ## return address handling
                        movq %rbp, %rsp
                        popq %rbp
                        ret
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.globl IO.in_string
IO.in_string:           ## method definition
                        pushq %rbp
                        movq %rsp, %rbp
                        movq 16(%rbp), %r12
                        ## stack room for temporaries: 1
                        movq $8, %r14
                        subq %r14, %rsp
                        ## return address handling
                        ## method body begins
                        ## new String
                        pushq %rbp
                        pushq %r12
                        movq $String..new, %r14
                        call *%r14
                        popq %r12
                        popq %rbp
                        movq %r13, %r14
                        call coolgetstr 
      movq %rax, %r13
                        movq %r13, 24(%r14)
                        movq %r14, %r13
.globl IO.in_string.end
IO.in_string.end:       ## method body ends
                        ## return address handling
                        movq %rbp, %rsp
                        popq %rbp
                        ret
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.globl IO.out_int
IO.out_int:             ## method definition
                        pushq %rbp
                        movq %rsp, %rbp
                        movq 24(%rbp), %r12
                        ## stack room for temporaries: 1
                        movq $8, %r14
                        subq %r14, %rsp
                        ## return address handling
                        ## fp[3] holds argument x (Int)
                        ## method body begins
                        movq 16(%rbp), %r13
                        movq $percent.d, %rdi
    movl %r13d, %eax
    cdqe
    movq %rax, %rsi
      movl $0, %eax
      call printf
                        movq %r12, %r13
.globl IO.out_int.end
IO.out_int.end:         ## method body ends
                        ## return address handling
                        movq %rbp, %rsp
                        popq %rbp
                        ret
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.globl IO.out_string
IO.out_string:          ## method definition
                        pushq %rbp
                        movq %rsp, %rbp
                        movq 16(%rbp), %r12
                        ## stack room for temporaries: 1
                        movq $8, %r14
                        subq %r14, %rsp
                        ## return address handling
                        ## fp[3] holds argument x (String)
                        ## method body begins
                        movq 24(%rbp), %r14
                        movq 24(%r14), %r13
                        movq %r13, %rdi
      call cooloutstr
                        movq %r12, %r13
.globl IO.out_string.end
IO.out_string.end:      ## method body ends
                        ## return address handling
                        movq %rbp, %rsp
                        popq %rbp
                        ret
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.globl String.concat
String.concat:          ## method definition
                        pushq %rbp
                        movq %rsp, %rbp
                        movq 16(%rbp), %r12
                        ## stack room for temporaries: 1
                        movq $8, %r14
                        subq %r14, %rsp
                        ## return address handling
                        ## fp[3] holds argument s (String)
                        ## method body begins
                        ## new String
                        pushq %rbp
                        pushq %r12
                        movq $String..new, %r14
                        call *%r14
                        popq %r12
                        popq %rbp
                        movq %r13, %r15
                        movq 24(%rbp), %r14
                        movq 24(%r14), %r14
                        movq 24(%r12), %r13
                        movq %r13, %rdi
      movq %r14, %rsi
      call coolstrcat
      movq %rax, %r13
                        movq %r13, 24(%r15)
                        movq %r15, %r13
.globl String.concat.end
String.concat.end:      ## method body ends
                        ## return address handling
                        movq %rbp, %rsp
                        popq %rbp
                        ret
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.globl String.length
String.length:          ## method definition
                        pushq %rbp
                        movq %rsp, %rbp
                        movq 16(%rbp), %r12
                        ## stack room for temporaries: 1
                        movq $8, %r14
                        subq %r14, %rsp
                        ## return address handling
                        ## method body begins
                        ## new Int
                        pushq %rbp
                        pushq %r12
                        movq $Int..new, %r14
                        call *%r14
                        popq %r12
                        popq %rbp
                        movq %r13, %r14
                        movq 24(%r12), %r13
                        movq %r13, %rdi
      movl $0, %eax
      call coolstrlen
      movq %rax, %r13
                        movq %r13, 24(%r14)
                        movq %r14, %r13
.globl String.length.end
String.length.end:      ## method body ends
                        ## return address handling
                        movq %rbp, %rsp
                        popq %rbp
                        ret
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.globl String.substr
String.substr:          ## method definition
                        pushq %rbp
                        movq %rsp, %rbp
                        movq 16(%rbp), %r12
                        ## stack room for temporaries: 1
                        movq $8, %r14
                        subq %r14, %rsp
                        ## return address handling
                        ## fp[4] holds argument i (Int)
                        ## fp[3] holds argument l (Int)
                        ## method body begins
                        ## new String
                        pushq %rbp
                        pushq %r12
                        movq $String..new, %r14
                        call *%r14
                        popq %r12
                        popq %rbp
                        movq %r13, %r15
                        movq 24(%rbp), %r14
                        movq 24(%r14), %r14
                        movq 32(%rbp), %r13
                        movq 24(%r13), %r13
                        movq 24(%r12), %r12
                        movq %r12, %rdi
      movq %r13, %rsi
      movq %r14, %rdx
      call coolsubstr
      movq %rax, %r13
                        cmpq $0, %r13
      jne l3
                        movq $string9, %r13
                        movq %r13, %rdi
      call cooloutstr
                        movl $0, %edi
      call exit
.globl l3
l3:                     movq %r13, 24(%r15)
                        movq %r15, %r13
.globl String.substr.end
String.substr.end:      ## method body ends
                        ## return address handling
                        movq %rbp, %rsp
                        popq %rbp
                        ret
                        ## ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.globl the.empty.string
the.empty.string:       # ""
.byte 0
.globl percent.d
percent.d : # "%ld"
.byte  37 # '%'
.byte 108 # 'l'
.byte 100 # 'd'
.byte 0
.globl percent.ld
percent.ld:             # "%ld"
.byte  32 # ' '
.byte  37 # '%'
.byte 108 # 'l'
.byte 100 # 'd'
.byte 0
.globl string1
string1:                #"Bool"
  .byte  66 # 'B'
  .byte 111 # 'o'
  .byte 111 # 'o'
  .byte 108 # 'l'
  .byte 0

  .globl string2
  string2 : # "IO"
  .byte  73 # 'I'
  .byte  79 # 'O'
  .byte 0

  .globl string3
  string3 : # "Int"
  .byte  73 # 'I'
  .byte 110 # 'n'
  .byte 116 # 't'
  .byte 0

  .globl string4
  string4 : # "Main"
  .byte  77 # 'M'
  .byte  97 # 'a'
  .byte 105 # 'i'
  .byte 110 # 'n'
  .byte 0

  .globl string5
  string5 : # "Object"
  .byte  79 # 'O'
  .byte  98 # 'b'
  .byte 106 # 'j'
  .byte 101 # 'e'
  .byte  99 # 'c'
  .byte 116 # 't'
  .byte 0

  .globl string6
  string6 : # "String"
  .byte  83 # 'S'
  .byte 116 # 't'
  .byte 114 # 'r'
  .byte 105 # 'i'
  .byte 110 # 'n'
  .byte 103 # 'g'
  .byte 0

  .globl string7
  string7 : # "abort\n"
  .byte  97 # 'a'
  .byte  98 # 'b'
  .byte 111 # 'o'
  .byte 114 # 'r'
  .byte 116 # 't'
  .byte  92 # '\'
  .byte 110 # 'n'
  .byte 0

  .globl string8
  string8 : # "Hello, world!\n"
  .byte  72 # 'H'
  .byte 101 # 'e'
  .byte 108 # 'l'
  .byte 108 # 'l'
  .byte 111 # 'o'
  .byte  44 # ','
  .byte  32 # ' '
  .byte 119 # 'w'
  .byte 111 # 'o'
  .byte 114 # 'r'
  .byte 108 # 'l'
  .byte 100 # 'd'
  .byte  33 # '!'
  .byte  92 # '\'
  .byte 110 # 'n'
  .byte 0

  .globl string9
  string9 : # "ERROR: 0: Exception: String.substr out of range\n"
  .byte  69 # 'E'
  .byte  82 # 'R'
  .byte  82 # 'R'
  .byte  79 # 'O'
  .byte  82 # 'R'
  .byte  58 # ':'
  .byte  32 # ' '
  .byte  48 # '0'
  .byte  58 # ':'
  .byte  32 # ' '
  .byte  69 # 'E'
  .byte 120 # 'x'
  .byte  99 # 'c'
  .byte 101 # 'e'
  .byte 112 # 'p'
  .byte 116 # 't'
  .byte 105 # 'i'
  .byte 111 # 'o'
  .byte 110 # 'n'
  .byte  58 # ':'
  .byte  32 # ' '
  .byte  83 # 'S'
  .byte 116 # 't'
  .byte 114 # 'r'
  .byte 105 # 'i'
  .byte 110 # 'n'
  .byte 103 # 'g'
  .byte  46 # '.'
  .byte 115 # 's'
  .byte 117 # 'u'
  .byte  98 # 'b'
  .byte 115 # 's'
  .byte 116 # 't'
  .byte 114 # 'r'
  .byte  32 # ' '
  .byte 111 # 'o'
  .byte 117 # 'u'
  .byte 116 # 't'
  .byte  32 # ' '
  .byte 111 # 'o'
  .byte 102 # 'f'
  .byte  32 # ' '
  .byte 114 # 'r'
  .byte  97 # 'a'
  .byte 110 # 'n'
  .byte 103 # 'g'
  .byte 101 # 'e'
  .byte  92 # '\'
  .byte 110 # 'n'
  .byte 0

                        .globl cooloutstr
  .type cooloutstr, @function
cooloutstr:
.LFB0:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq  %rsp, %rbp
  .cfi_def_cfa_register 6
  subq  $32, %rsp
  movq  %rdi, -24(%rbp)
  movl  $0, -4(%rbp)
  jmp .L2
.L5:
  movl  -4(%rbp), %eax
  cltq
  addq  -24(%rbp), %rax
  movzbl  (%rax), %eax
  cmpb  $92, %al
  jne .L3
  movl  -4(%rbp), %eax
  cltq
  addq  $1, %rax
  addq  -24(%rbp), %rax
  movzbl  (%rax), %eax
  cmpb  $110, %al
  jne .L3
  movq  stdout(%rip), %rax
  movq  %rax, %rsi
  movl  $10, %edi
  call  fputc
  addl  $2, -4(%rbp)
  jmp .L2
.L3:
  movl  -4(%rbp), %eax
  cltq
  addq  -24(%rbp), %rax
  movzbl  (%rax), %eax
  cmpb  $92, %al
  jne .L4
  movl  -4(%rbp), %eax
  cltq
  addq  $1, %rax
  addq  -24(%rbp), %rax
  movzbl  (%rax), %eax
  cmpb  $116, %al
  jne .L4
  movq  stdout(%rip), %rax
  movq  %rax, %rsi
  movl  $9, %edi
  call  fputc
  addl  $2, -4(%rbp)
  jmp .L2
.L4:
  movq  stdout(%rip), %rdx
  movl  -4(%rbp), %eax
  cltq
  addq  -24(%rbp), %rax
  movzbl  (%rax), %eax
  movsbl  %al, %eax
  movq  %rdx, %rsi
  movl  %eax, %edi
  call  fputc
  addl  $1, -4(%rbp)
.L2:
  movl  -4(%rbp), %eax
  cltq
  addq  -24(%rbp), %rax
  movzbl  (%rax), %eax
  testb %al, %al
  jne .L5
  movq  stdout(%rip), %rax
  movq  %rax, %rdi
  call  fflush
  leave
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
  .LFE0:
  .size cooloutstr, .-cooloutstr
.globl coolstrlen
  .type coolstrlen, @function
coolstrlen:
.LFB1:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq  %rsp, %rbp
  .cfi_def_cfa_register 6
  movq  %rdi, -24(%rbp)
  movl  $0, -4(%rbp)
  jmp .L7
.L8:
  movl  -4(%rbp), %eax
  addl  $1, %eax
  movl  %eax, -4(%rbp)
.L7:
  movl  -4(%rbp), %eax
  mov %eax, %eax
  addq  -24(%rbp), %rax
  movzbl  (%rax), %eax
  testb %al, %al
  jne .L8
  movl  -4(%rbp), %eax
  leave
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.LFE1:
  .size coolstrlen, .-coolstrlen
  .section  .rodata
.LC0:
  .string "%s%s"
  .text
.globl coolstrcat
  .type coolstrcat, @function
coolstrcat:
.LFB2:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq  %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  subq  $40, %rsp
  movq  %rdi, -40(%rbp)
  movq  %rsi, -48(%rbp)
  cmpq  $0, -40(%rbp)
  jne .L10
  .cfi_offset 3, -24
  movq  -48(%rbp), %rax
  jmp .L11
.L10:
  cmpq  $0, -48(%rbp)
  jne .L12
  movq  -40(%rbp), %rax
  jmp .L11
.L12:
  movq  -40(%rbp), %rax
  movq  %rax, %rdi
  call  coolstrlen
  movl  %eax, %ebx
  movq  -48(%rbp), %rax
  movq  %rax, %rdi
  call  coolstrlen
  leal  (%rbx,%rax), %eax
  addl  $1, %eax
  movl  %eax, -20(%rbp)
  movl  -20(%rbp), %eax
  cltq
  movl  $1, %esi
  movq  %rax, %rdi
  call  calloc
  movq  %rax, -32(%rbp)
  movl  $.LC0, %edx
  movl  -20(%rbp), %eax
  movslq  %eax, %rbx
  movq  -48(%rbp), %rsi
  movq  -40(%rbp), %rcx
  movq  -32(%rbp), %rax
  movq  %rsi, %r8
  movq  %rbx, %rsi
  movq  %rax, %rdi
  movl  $0, %eax
  call  snprintf
  movq  -32(%rbp), %rax
.L11:
  addq  $40, %rsp
  popq  %rbx
  leave
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.LFE2:
  .size coolstrcat, .-coolstrcat
  .section  .rodata
.LC1:
  .string ""
  .text
.globl coolgetstr
  .type coolgetstr, @function
coolgetstr:
.LFB3:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq  %rsp, %rbp
  .cfi_def_cfa_register 6
  subq  $32, %rsp
  movl  $1, %esi
  movl  $40960, %edi
  call  calloc
  movq  %rax, -16(%rbp)
  movl  $0, -4(%rbp)
.L20:
  movq  stdin(%rip), %rax
  movq  %rax, %rdi
  call  fgetc
  movl  %eax, -20(%rbp)
  cmpl  $-1, -20(%rbp)
  je  .L14
  cmpl  $10, -20(%rbp)
  jne .L15
.L14:
  cmpl  $0, -4(%rbp)
  je  .L16
  movl  $.LC1, %eax
  jmp .L17
.L16:
  movq  -16(%rbp), %rax
  jmp .L17
.L15:
  cmpl  $0, -20(%rbp)
  jne .L18
  movl  $1, -4(%rbp)
  jmp .L20
.L18:
  movq  -16(%rbp), %rax
  movq  %rax, %rdi
  call  coolstrlen
  mov %eax, %eax
  addq  -16(%rbp), %rax
  movl  -20(%rbp), %edx
  movb  %dl, (%rax)
  jmp .L20
.L17:
  leave
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.LFE3:
  .size coolgetstr, .-coolgetstr
.globl coolsubstr
  .type coolsubstr, @function
coolsubstr:
.LFB4:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq  %rsp, %rbp
  .cfi_def_cfa_register 6
  subq  $48, %rsp
  movq  %rdi, -24(%rbp)
  movq  %rsi, -32(%rbp)
  movq  %rdx, -40(%rbp)
  movq  -24(%rbp), %rax
  movq  %rax, %rdi
  call  coolstrlen
  movl  %eax, -4(%rbp)
  cmpq  $0, -32(%rbp)
  js  .L22
  cmpq  $0, -40(%rbp)
  js  .L22
  movq  -40(%rbp), %rax
  movq  -32(%rbp), %rdx
  addq  %rax, %rdx
  movl  -4(%rbp), %eax
  cltq
  cmpq  %rax, %rdx
  jle .L23
.L22:
  movl  $0, %eax
  jmp .L24
.L23:
  movq  -40(%rbp), %rdx
  movq  -32(%rbp), %rax
  addq  -24(%rbp), %rax
  movq  %rdx, %rsi
  movq  %rax, %rdi
  call  strndup
.L24:
  leave
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.LFE4:
  .size coolsubstr, .-coolsubstr

.globl start
_start:
.globl main
main:
movq $1, %rax
movq $1, %rbx
movq %rbx, %rcx
addq %rax, %rcx
pushq %r12
pushq %r13
pushq %r14
pushq 16(%rbp)
pushq %rcx
movq $IO.out_int, %r14
call *%r14
popq %rcx
popq %rbp
popq %r12
popq %r13
popq %r14
call exit
