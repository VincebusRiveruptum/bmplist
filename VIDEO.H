#include "vgaregs.h"
#include <dos.h>

void set200pxMode(void);
void putPixelX(int, int, char);
unsigned char getPixelX(int, int);
void setPal(char color, unsigned char r, unsigned char g, unsigned char b);
void drawPalette();
void setTXTMode();

#define PAGE_SIZE 16000
#define NUM_PAGES 4
unsigned char currentPage = 0;
unsigned char nextPage = 1;

/*
 Set_320x200X();                                                                                                                            ��
 Inicializa el Modo 13X de 320x200 a 256 colores en sistema 1x4.
*/

#pragma aux set_video_mode = \
    "cld"                    \
    "mov ax, 0x0013",        \
    "int 0x10";

#pragma aux clear_screen =                                   \
    "mov eax, 0x00"    /* Zero-fill the register */          \
    "mov ecx, 16000"   /* 64000 bytes / 4 = 16000 dwords */  \
    "mov edi, 0xA0000" /* VGA memory segment for mode 13h */ \
    "rep stosd"        /* Fill VGA memory with zeros */      \
    modify[eax ecx edi];

void set200pxMode()             // This sets to mode X
{
    set_video_mode(); // Call the BIOS to set mode 13h

    // Set VGA registers (these remain the same as in Borland C)
     OutPortw(SEQU_ADDR, 0x0604);
     OutPortw(CRTC_ADDR, 0xE317);
     OutPortw(CRTC_ADDR, 0x0014);
     OutPortw(SEQU_ADDR, 0x0F02);

    clear_screen(); // Call the clear screen function
}

/*
 PutPixelX();
 Coloca un punto en la primera p�gina en (X,Y) de color color.
*/

#pragma aux put_pixel =                                    \
    "mov edi, 0xA0000" /* Set edi to VGA memory segment */ \
    "add edi, eax"     /* Add the offset to edi */         \
    "mov al, dl"       /* Move color into al */            \
    "stosb"            /* Store byte at VGA memory */      \
    parm[eax][dl]      /* eax for offset, dl for color */  \
    modify[edi al];    /* Registers modified */

void putPixelX(int x, int y, char color)
{
    unsigned long offs;

    // Set the VGA plane and calculate the offset
    OutPortb(SEQU_ADDR, 0x02);
    OutPortb(SEQU_ADDR + 1, 0x01 << (x & 3));

    offs = (y << 6) + (y << 4) + (x >> 2) + (PAGE_SIZE * nextPage); // Equivalent to y*320 + x/4 in mode 13h

    put_pixel(offs, color); // Place the pixel
}

/* Page buffering functions */

void setPage(unsigned char page) {
    unsigned long start_addr = (page * PAGE_SIZE);

    OutPortb(CRTC_ADDR, 0x0C);        // CRTC register 0x0C (high byte of start address)
    OutPortb(CRTC_ADDR + 1, (start_addr >> 8));
    OutPortb(CRTC_ADDR, 0x0D);        // CRTC register 0x0D (low byte of start address)
    OutPortb(CRTC_ADDR + 1, start_addr & 0xFF);
}

void flipPage() {
    //while((InPortb(SEQU_ADDR) & 0x08) == 1 );
    currentPage = nextPage;
    setPage(currentPage); // Perform the page flip
    nextPage = (nextPage + 1) % NUM_PAGES;
    
}

void setPal(char color, unsigned char r, unsigned char g, unsigned char b)
{
    OutPortb(0x3c8, color);
    OutPortb(0x3c9, r);
    OutPortb(0x3c9, g);
    OutPortb(0x3c9, b);
}

#pragma aux set_txt_mode =  \
    "xor ax, ax",           \
            "int 0x16",     \
            "mov ax, 0x03", \
            "int 0x10";

void setTXTMode()
{
    set_txt_mode(); // Switch to text mode
}