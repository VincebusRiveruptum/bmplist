
#include "video.h"

    
void setTXTMode(){
    setTXTModeASM();
};

// Setting mode x
void set200pxMode(){
    setVideoMode13(); // Call the BIOS to set mode 13h

    // Set VGA registers (these remain the same as in Borland C)
    outPortw(SEQU_ADDR, 0x0604);
    outPortw(CRTC_ADDR, 0xE317);
    outPortw(CRTC_ADDR, 0x0014);
    outPortw(SEQU_ADDR, 0x0F02);

    clearScreen(); // Call the clear screen function
}

#pragma aux putPixelASM =                                    \
    "mov edi, 0xA0000" /* Set edi to VGA memory segment */ \
    "add edi, eax"     /* Add the offset to edi */         \
    "mov al, dl"       /* Move color into al */            \
    "stosb"            /* Store byte at VGA memory */      \
    parm[eax][dl]      /* eax for offset, dl for color */  \
    modify[edi al];    /* Registers modified */

void putPixelX(int x, int y, char color){
    unsigned long offs;

    // Set the VGA plane and calculate the offset
    outPortb(SEQU_ADDR, 0x02);
    outPortb(SEQU_ADDR + 1, 0x01 << (x & 3));

    offs = (y << 6) + (y << 4) + (x >> 2) + (PAGE_SIZE * nextPage); // Equivalent to y*320 + x/4 in mode 13h

    putPixelASM(offs, color); // Place the pixel
}

// Page buffering functions
void setPage(unsigned char page) {
    unsigned long start_addr = (page * PAGE_SIZE);

    outPortb(CRTC_ADDR, 0x0C);        // CRTC register 0x0C (high byte of start address)
    outPortb(CRTC_ADDR + 1, (start_addr >> 8));
    outPortb(CRTC_ADDR, 0x0D);        // CRTC register 0x0D (low byte of start address)
    outPortb(CRTC_ADDR + 1, start_addr & 0xFF);
}

void flipPage() {
    //while((InPortb(SEQU_ADDR) & 0x08) == 1 );
    currentPage = nextPage;
    setPage(currentPage); // Perform the page flip
    nextPage = (nextPage + 1) % NUM_PAGES;
    
}

void setPal(char color, unsigned char r, unsigned char g, unsigned char b){
    outPortb(0x3c8, color);
    outPortb(0x3c9, r);
    outPortb(0x3c9, g);
    outPortb(0x3c9, b);
}
