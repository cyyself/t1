SECTIONS
{
    RAM_BASE = 0x20000000; /* ... but actually position independent */

    . = RAM_BASE;
    .text.start : { *(.text.start) }
}
