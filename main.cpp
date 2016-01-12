#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


#define byte unsigned char /* 1 */

union _word {
 char array[2];
 unsigned short all;
};

union _dword {
 char array[4];
 unsigned int all;
};


struct TbitmapHeader {
    _word bfType;
    _dword bfSize;
    _word bfReserved1;
    _word bfReserved2;
    _dword bfOffBits;
    //40 byte header
    _dword biSize;
    _dword biWidth;
    _dword biHeight;
    _word biPlanes;
    _word biBitCount;
    _dword biCompression;
    _dword biSizeImage;
    _dword biXPelsPerMeter;
    _dword biYPelsPerMeter;
    _dword biClrUsed;
    _dword biClrImportant;
};

void print_hex_array(char *array, unsigned int size) {
     unsigned int i;
     printf("%lu: ", array);
     for (i=0; i<size; i++) {
         printf("%2.2x",array[i]);
     }
     printf(" (%db)\n",size);
}

void print_bitmapHeader(struct TbitmapHeader *p) {
    printf("bfType ", p->bfType);
    print_hex_array(p->bfType.array, sizeof(p->bfType.array));
    printf("bfSize ",p->bfSize);
    print_hex_array(p->bfSize.array, sizeof(p->bfSize.array));
    printf("RSVD1 %4.4x\nRSVD2 %4.4x - ",p->bfReserved1, p->bfReserved2);
    print_hex_array(p->bfReserved2.array, sizeof(p->bfReserved2.array));
    printf("Offset %d[%2.2x] - ",p->bfOffBits,p->bfOffBits);
    print_hex_array(p->bfOffBits.array, sizeof(p->bfOffBits.array));
    // ---
    printf("biSize %4.4x - ", p->biSize);
    print_hex_array(p->biSize.array, sizeof(p->biSize.array));
    printf("biWidth %4.4x - ", p->biWidth);
    print_hex_array(p->biWidth.array, sizeof(p->biWidth.array));
}

struct Ttest {
     _word a,b,c;
};


int main(int argc, char *argv[]) {

    int fileInput;
    struct TbitmapHeader  *bitmapHeader;
    struct Ttest test;
    unsigned char array[sizeof(TbitmapHeader)];
    int i;


    printf("a ");
    print_hex_array(test.a.array, sizeof(test.a.array));
    printf("b ");
    print_hex_array(test.b.array, sizeof(test.b.array));
    printf("c ");
    print_hex_array(test.c.array, sizeof(test.c.array));

    fileInput = open(argv[1], O_RDONLY);
    read(fileInput, array, sizeof(TbitmapHeader));
    printf("Readed %d.\n", sizeof(TbitmapHeader));
    for (i=0; i<sizeof(TbitmapHeader); i++ ) {
        printf("%2.2x", array[i]);
        if (i%2 == 1) printf(" ");
    }
    printf("\n");
    close(fileInput);

    bitmapHeader = (struct TbitmapHeader *)&array;


    print_bitmapHeader(bitmapHeader);

    return 0;
}
