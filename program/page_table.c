void init_HS_page_table(){
    unsigned long* pte;
    unsigned long next_empty=0x80400000;
    unsigned long cur = 0x80000000;

    // PA Map
    // [0x8000_0000, ...] program
    // [..., 0x8020_0000] stack
    // [0x8020_0000, 0x8040_0000] free and empty
    // [0x8040_0000, 0x8050_0000] page table (set by host)
    // [0x8050_0000, 0x8060_0000] page table (set by host)
    // [0x8060_0000, 0x8080_0000] page table (set by guest)

        // hVA                         -> hPA
    // [0x8000_0000, 0x8080_0000) -> [0x8000_0000, 0x8080_0000)
    // [0xC000_0000, 0xC080_0000) -> [0x8000_0000, 0x8080_0000)

    // the paddr of first stage page table
    unsigned long ppn0 = next_empty;
    next_empty += 0x1000;

    // set page table of vaddr [0x8000_0000, 0x8080_0000) 
    for(int i = 2; i< 3; i++){
        // set pointer to first stage page table entry
        pte = (unsigned long*)(ppn0+i*8);   
        
        // alloc and assign a empty page frame as 2nd stge page table
        unsigned long ppn1 = next_empty;
        next_empty += 0x1000;
        
        // fill the 1st pte with the paddr of 2nd page table
        *pte = ppn1 >> 2;
        *pte |= (unsigned long)0x1;

        for(int j = 0; j < 4; j++){
            // set pointer to 2nd stage page table entry
            pte = (unsigned long*)(ppn1+j*8);   
            
            // alloc and assign a empty page frame as 3rd stge page table
            unsigned long ppn2 = next_empty;
            next_empty += 0x1000;
            
            // fill the 2nd pte with the paddr of 3rd page table
            *pte = ppn2 >> 2;
            *pte |= (unsigned long)0x1;

            for(int k=0; k<512;k++){
                // set pointer to 3rd stage page table entry
                pte = (unsigned long*)(ppn2+k*8);   
                
                // fill the 3rd pte with the final paddr of data
                *pte = cur >> 2;
                cur += 0x1000;
                *pte |= (unsigned long)0xcf;
            }
        }
    }

    cur = 0x80000000;
    // set page table of vaddr [0xC000_0000, 0xC080_0000)
    for(int i = 3; i< 4; i++){
        // set pointer to first stage page table entry
        pte = (unsigned long*)(ppn0+i*8);   
        
        // alloc and assign a empty page frame as 2nd stge page table
        unsigned long ppn1 = next_empty;
        next_empty += 0x1000;
        
        // fill the 1st pte with the paddr of 2nd page table
        *pte = ppn1 >> 2;
        *pte |= (unsigned long)0x1;

        for(int j = 0; j < 4; j++){
            // set pointer to 2nd stage page table entry
            pte = (unsigned long*)(ppn1+j*8);   
            
            // alloc and assign a empty page frame as 3rd stge page table
            unsigned long ppn2 = next_empty;
            next_empty += 0x1000;
            
            // fill the 2nd pte with the paddr of 3rd page table
            *pte = ppn2 >> 2;
            *pte |= (unsigned long)0x1;

            for(int k=0; k<512;k++){
                // set pointer to 3rd stage page table entry
                pte = (unsigned long*)(ppn2+k*8);   
                
                // fill the 3rd pte with the final paddr of data
                *pte = cur >> 2;
                cur += 0x1000;
                *pte |= (unsigned long)0xcf;
            }
        }
    }

    unsigned long satp;
    satp =0x80400000 >> 12;
    satp |= 0x8000000000000000;

    __asm__ ("csrw satp,%0;\n\t"
              "sfence.vma;"
                :
                :"r"(satp)
                :
            );
}

void init_VS_page_table(){
    unsigned long* pte;
    unsigned long next_empty=0x190600000;
    unsigned long cur = 0x80000000;

    // PA Map
    // [0x8000_0000, ...] program
    // [..., 0x8020_0000] stack
    // [0x8020_0000, 0x8040_0000] free and empty
    // [0x8040_0000, 0x8050_0000] page table (set by host)
    // [0x8050_0000, 0x8060_0000] page table (set by host)
    // [0x8060_0000, 0x8080_0000] page table (set by guest)

        // gVA                         -> gPA
    // [0x8000_0000, 0x8080_0000) -> [0x8000_0000, 0x8080_0000)
    // [0x4000_0000, 0x4080_0000) -> [0x18000_0000, 0x18080_0000)
    // [0x0000_0000, 0x0080_0000) -> [0x19000_0000, 0x19080_0000)

    // the paddr of first stage page table
    unsigned long ppn0 = next_empty;
    next_empty += 0x1000;

    // set page table of vaddr [0x8000_0000, 0x8080_0000) 
    for(int i = 2; i< 3; i++){
        // set pointer to first stage page table entry
        pte = (unsigned long*)(ppn0+i*8);   
        
        // alloc and assign a empty page frame as 2nd stge page table
        unsigned long ppn1 = next_empty;
        next_empty += 0x1000;
        
        // fill the 1st pte with the paddr of 2nd page table
        *pte = ppn1 >> 2;
        *pte |= (unsigned long)0x1;

        for(int j = 0; j < 4; j++){
            // set pointer to 2nd stage page table entry
            pte = (unsigned long*)(ppn1+j*8);   
            
            // alloc and assign a empty page frame as 3rd stge page table
            unsigned long ppn2 = next_empty;
            next_empty += 0x1000;
            
            // fill the 2nd pte with the paddr of 3rd page table
            *pte = ppn2 >> 2;
            *pte |= (unsigned long)0x1;

            for(int k=0; k<512;k++){
                // set pointer to 3rd stage page table entry
                pte = (unsigned long*)(ppn2+k*8);   
                
                // fill the 3rd pte with the final paddr of data
                *pte = cur >> 2;
                cur += 0x1000;
                *pte |= (unsigned long)0xcf;
            }
        }
    }
    
    // set page table of vaddr [0x4000_0000, 0x4080_0000)
    cur = 0x180000000;
    for(int i = 1; i< 2; i++){
        // set pointer to first stage page table entry
        pte = (unsigned long*)(ppn0+i*8);   
        
        // alloc and assign a empty page frame as 2nd stge page table
        unsigned long ppn1 = next_empty;
        next_empty += 0x1000;
        
        // fill the 1st pte with the paddr of 2nd page table
        *pte = ppn1 >> 2;
        *pte |= (unsigned long)0x1;

        for(int j = 0; j < 4; j++){
            // set pointer to 2nd stage page table entry
            pte = (unsigned long*)(ppn1+j*8);   
            
            // alloc and assign a empty page frame as 3rd stge page table
            unsigned long ppn2 = next_empty;
            next_empty += 0x1000;
            
            // fill the 2nd pte with the paddr of 3rd page table
            *pte = ppn2 >> 2;
            *pte |= (unsigned long)0x1;

            for(int k=0; k<512;k++){
                // set pointer to 3rd stage page table entry
                pte = (unsigned long*)(ppn2+k*8);   
                
                // fill the 3rd pte with the final paddr of data
                *pte = cur >> 2;
                cur += 0x1000;
                *pte |= (unsigned long)0xcf;
            }
        }
    }

    // set page table of vaddr [0x0000_0000, 0x0080_0000)
    cur = 0x190000000;
    for(int i = 0; i< 1; i++){
        // set pointer to first stage page table entry
        pte = (unsigned long*)(ppn0+i*8);   
        
        // alloc and assign a empty page frame as 2nd stge page table
        unsigned long ppn1 = next_empty;
        next_empty += 0x1000;
        
        // fill the 1st pte with the paddr of 2nd page table
        *pte = ppn1 >> 2;
        *pte |= (unsigned long)0x1;

        for(int j = 0; j < 4; j++){
            // set pointer to 2nd stage page table entry
            pte = (unsigned long*)(ppn1+j*8);   
            
            // alloc and assign a empty page frame as 3rd stge page table
            unsigned long ppn2 = next_empty;
            next_empty += 0x1000;
            
            // fill the 2nd pte with the paddr of 3rd page table
            *pte = ppn2 >> 2;
            *pte |= (unsigned long)0x1;

            for(int k=0; k<512;k++){
                // set pointer to 3rd stage page table entry
                pte = (unsigned long*)(ppn2+k*8);   
                
                // fill the 3rd pte with the final paddr of data
                *pte = cur >> 2;
                cur += 0x1000;
                *pte |= (unsigned long)0xcf;
            }
        }
    }

    unsigned long satp;
    satp =0x190600000 >> 12;
    satp |= 0x8000000000000000;

    __asm__ ("csrw satp,%0;\n\t"
              "sfence.vma;"
                :
                :"r"(satp)
                :
            );
}

void init_guest_page_table(){
    unsigned long* pte;
    unsigned long next_empty=0x80500000;
    unsigned long cur = 0x80000000;

    // gPA                          -> hPA
    // [0x8000_0000, 0x8080_0000)   -> [0x8000_0000, 0x8080_0000)
    // [0x18000_0000, 0x18080_0000) -> [0x8000_0000, 0x8080_0000)

    // through DS
    // [0x19000_0000, 0x19080_0000) -> [0x8000_0000, 0x8080_0000)

    unsigned long ppn0 = next_empty;
    next_empty += (0x1000<<2); // for sv39x4

    // set page table of gpaddr [0x18000_0000, 0x18080_0000) 
    for(int i = 2; i< 7; i+=4){
        cur = 0x80000000;
        // set pointer to first stage page table entry
        pte = (unsigned long*)(ppn0+i*8);   
        
        // alloc and assign a empty page frame as 2nd stge page table
        unsigned long ppn1 = next_empty;
        next_empty += 0x1000;
        
        // fill the 1st pte with the paddr of 2nd page table
        *pte = ppn1 >> 2;
        *pte |= (unsigned long)0x1;

        for(int j = 0; j < 4; j++){
            // set pointer to 2nd stage page table entry
            pte = (unsigned long*)(ppn1+j*8);   
            
            // alloc and assign a empty page frame as 3rd stge page table
            unsigned long ppn2 = next_empty;
            next_empty += 0x1000;
            
            // fill the 2nd pte with the paddr of 3rd page table
            *pte = ppn2 >> 2;
            *pte |= (unsigned long)0x1;

            for(int k=0; k<512;k++){
                // set pointer to 3rd stage page table entry
                pte = (unsigned long*)(ppn2+k*8);   
                
                // fill the 3rd pte with the final paddr of data
                *pte = cur >> 2;
                cur += 0x1000;
                *pte |= (unsigned long)0xdf;
            }
        }
    }

    unsigned long hgatp;
    hgatp =0x80500000 >> 12;
    hgatp |= 0x8000000000000000;

    __asm__ ("csrw 0x680,%0;\n\t" // csrw hgatp
            ".word 0x62000073;"         // hfence.gvma
            :
            :"r"(hgatp)
            :
        );
}

