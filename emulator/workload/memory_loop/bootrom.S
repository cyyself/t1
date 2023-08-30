#define STORE_ADDR 0x30000000
.section .text.start, "ax", @progbits
.globl _start
_start:
  csrr a0, mcycle
  li a1, STORE_ADDR
  sw a0, 0(a1)
  j _start