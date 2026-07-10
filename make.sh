LCC=/home/max/Programs/GameBoyDev/gbdk/bin/lcc

# delete previous files
rm *.gb

# compile .c files into .o files
$LCC -c -o main.o src/main.c
$LCC -c -o head_sprite.o sprites/head_sprite.c

# compile a .gb file from the ocmpiled .o files
$LCC -o Snake.gb main.o head_sprite.o

# delete intermediate files created for the compilation process
rm *.asm
rm *.lst
rm *.ihx
rm *.sym
rm *.o