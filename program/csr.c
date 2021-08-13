void set_ds_csr(){
    // set DS [base, limit, offset] for HS and guest-host

    // for HS, va->pa
    // [0xD000_0000, 0xD080_0000) -> [0x8000_0000, 0x8080_0000)

    unsigned long base = 0xD0000000;
    base |= 0x1;
    unsigned long limit = 0xD0800000;
    unsigned long offset = (0xD0000000-0x80000000);
    offset |= 0x1;

    __asm__("csrw 0x181,%0;\n\t"
            "csrw 0x182,%1;\n\t"
            "csrw 0x183,%2;\n\t"
            :
            :"r"(base),"r"(limit),"r"(offset)
            :);

    // for guest, gPA->hPA
    // [0x19000_0000, 0x19080_0000) -> [0x8000_0000, 0x8080_0000)
    base = 0x190000000 | 0x1;
    limit = 0x190800000;
    offset = (0x190000000-0x80000000) | 0x1;

    __asm__("csrw 0x681,%0;\n\t"
            "csrw 0x682,%1;\n\t"
            "csrw 0x683,%2;\n\t"
            :
            :"r"(base),"r"(limit),"r"(offset)
            :);
}

void set_ds_csr_guest(){
    // set DS [base, limit, offset] for HS and guest-host

    // for VS, gVA->gPA
    // [0x60000_0000, 0x7080_0000) -> [0x18000_0000, 0x19080_0000)

    unsigned long base = 0x60000000;
    base |= 0x1;
    unsigned long limit = 0x70800000;
    unsigned long offset = (0x180000000-0x60000000);

    __asm__("csrw 0x181,%0;\n\t"
            "csrw 0x182,%1;\n\t"
            "csrw 0x183,%2;\n\t"
            :
            :"r"(base),"r"(limit),"r"(offset)
            :);
}