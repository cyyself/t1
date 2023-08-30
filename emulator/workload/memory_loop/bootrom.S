#define LOAD_ADDR  0x20000020
#define STORE_ADDR 0x20000020
.section .text.start, "ax", @progbits
.globl _start
_start:
  csrr a0, mcycle
  li a1, STORE_ADDR
  li a2, LOAD_ADDR
  lw a2, 0(a2)
  mv a3, a2
  sw a0, 0(a1)
  j _start