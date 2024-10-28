# BMPLIST - BITMAP file handling, Doubly linked list and VGA Graphics programming experiment

This small program just a the title says, opens a list of bmp files and store them on a doubly linked list, each frame is animated using VGA Mode X and double-buffering.

On the future i'll work on more IO functions such as keyboard and mouse handling, maybe sound and disk caching too, currently i need to adquire more skill on the graphics topic, better x86-32 ASM understanding and memory managment with protected mode.

To getting it run you need:
    - Any DOS environment, i used DOSBOX.
    - Watcom C 10.6
    - Some files to draw, already there are some on JUMP folder.

After installing WATCOM C, on the root folder of the repo just run WCL386 BMPLIST.C BMP.C VIDEO.C DATA.C
and wait to finish compile. After compiling just run the generated exe.
