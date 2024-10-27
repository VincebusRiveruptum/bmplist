
/*
    BMP, mode X and doubly linked list test by Vincebus Riveruptum
    2024.

    ASM functions based on santiago romero's vga tutorial 
    and converted them to 32 bit with CHATGPT.

    Compiled with WATCOM C 10.6
    wcl386 bmptest2.c

*/

#include "data.h"
#include "types.h"
#include "video.h"
#include "bmp.h"

// Main loop

int main(int argc, char *argv[])
{

    // BMP list loading,,,
    BMPfile *firstFile = loadBMPfile(".\\jump\\frame1.bmp");
    unsigned long gameTicks = 0;
    unsigned long index = 0;

    addBMPtoList(&bmpList, firstFile->bmpData);
    addBMPtoList(&bmpList, loadBMPfile(".\\jump\\frame2.bmp")->bmpData);
    addBMPtoList(&bmpList, loadBMPfile(".\\jump\\frame3.bmp")->bmpData);
    addBMPtoList(&bmpList, loadBMPfile(".\\jump\\frame4.bmp")->bmpData);
    addBMPtoList(&bmpList, loadBMPfile(".\\jump\\frame5.bmp")->bmpData);
    addBMPtoList(&bmpList, loadBMPfile(".\\jump\\frame6.bmp")->bmpData);
    addBMPtoList(&bmpList, loadBMPfile(".\\jump\\frame7.bmp")->bmpData);
    addBMPtoList(&bmpList, loadBMPfile(".\\jump\\frame8.bmp")->bmpData);
    addBMPtoList(&bmpList, loadBMPfile(".\\jump\\frame9.bmp")->bmpData);
    addBMPtoList(&bmpList, loadBMPfile(".\\jump\\frame10.bmp")->bmpData);
    addBMPtoList(&bmpList, loadBMPfile(".\\jump\\frame11.bmp")->bmpData);
    addBMPtoList(&bmpList, loadBMPfile(".\\jump\\frame12.bmp")->bmpData);
    addBMPtoList(&bmpList, loadBMPfile(".\\jump\\frame13.bmp")->bmpData);
    addBMPtoList(&bmpList, loadBMPfile(".\\jump\\frame14.bmp")->bmpData);
    addBMPtoList(&bmpList, loadBMPfile(".\\jump\\frame15.bmp")->bmpData);

    printf("\nFiles loaded : %d", bmpList->length);

    getch();

    set200pxMode();

    setPalette(firstFile->bmpData->palette);

    while (gameTicks < 600)
    {
            drawBitmap(&(getNodeByIndex(&bmpList, index)->data), 1, 1, 256);

            if (index == bmpList->length)
            {
                index = 0;
            }
            else
            {
                index++;
            }
         
        

        flipPage(); 
        gameTicks++;
    }

    setTXTMode();

    printf("\n96 Tears...");

    free(bmpList);
    free(globalPalette);
    return 0;
}