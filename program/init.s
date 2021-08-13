    .section .text.entry
    .globl _start
_start:
    li      t0, 0x800
    csrw    mstatus, t0
    auipc   t0, 0x0
    addi    t0, t0, 0x10
    csrw    mepc, t0
    mret

_s_mode_entry:
    li     sp, 0x80200000

    call init_HS_page_table

    # test whether the page table works fine
    li t0, 0x80202000
    li t1, 0xa0a1a2a3c4c5c6c7
    sd t1, 0(t0)
    li t1, 0x1111222233334444
    sd t1, 8(t0)
    li t1, 0xa0a1a2a3c4c5c6c7
    sd t1, 16(t0)
    li t1, 0xccccccccaaaaaaaa
    sd t1, 24(t0)

    li t0, 0xC0202000
    ld t2, 0(t0)
    ld t2, 8(t0)
    ld t2, 16(t0)
    ld t2, 24(t0)

    call set_ds_csr

    # test whether the stage 1 DS works fine     
    li t0, 0xD0202000
    ld t2, 0(t0)
    ld t2, 8(t0)
    ld t2, 16(t0)
    ld t2, 24(t0)

    call init_guest_page_table

    li      t0, 0x1 << 8;  
    csrw    sstatus, t0
    li      t0, 0x1 << 7;
    csrw    0x600, t0    
    auipc   t0, 0x0
    addi    t0, t0, 0x10
    csrw    sepc, t0
    sret

_h_mode_entry:
    li     sp, 0x80180000

    li t0, 0x80202000
    ld t2, 0(t0)
    ld t2, 8(t0)
    ld t2, 16(t0)
    ld t2, 24(t0)

    li t0, 0x180202000
    ld t2, 0(t0)
    ld t2, 8(t0)
    ld t2, 16(t0)
    ld t2, 24(t0)

    li t0, 0x190202000
    ld t2, 0(t0)
    ld t2, 8(t0)
    ld t2, 16(t0)
    ld t2, 24(t0)

    call init_VS_page_table
    call set_ds_csr_guest

    li t0, 0x80202000
    ld t2, 0(t0)
    ld t2, 8(t0)
    ld t2, 16(t0)
    ld t2, 24(t0)

    li t0, 0x40202000
    ld t2, 0(t0)
    ld t2, 8(t0)
    ld t2, 16(t0)
    ld t2, 24(t0)

    li t0, 0x00202000
    ld t2, 0(t0)
    ld t2, 8(t0)
    ld t2, 16(t0)
    ld t2, 24(t0)

    li t0, 0x60202000
    ld t2, 0(t0)
    ld t2, 8(t0)
    ld t2, 16(t0)
    ld t2, 24(t0)

    li t0, 0x70202000
    ld t2, 0(t0)
    ld t2, 8(t0)
    ld t2, 16(t0)
    ld t2, 24(t0)

    call end
