#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

#define byte unsigned char
#define word unsigned short
#define dword unsigned int
#define qword unsigned long


struct bitmapHeader {
    unsigned char bfType[2];
    dword bfSize;
    word bfReserved1;
    word bfReserved2;
    dword bfOffBits;
    //40 byte header
    dword biSize;
    dword biWidth;
    dword biHeight;
    word biPlanes;
    word biBitCount;
    dword biCompression;
    dword biSizeImage;
    dword biXPelsPerMeter;
    dword biYPelsPerMeter;
    dword biClrUsed;
    dword biClrImportant;
};

void print_bitmapHeader(struct bitmapHeader *p) {
    printf("BM = %c%c.\n", p->bfType[0], p->bfType[1]);
    printf("File length : %db.\n",p->bfSize);
    printf("RSVD1 %x, RSVD2 %x.\n",p->bfReserved1, p->bfReserved2);
    printf("Offset ");
}


int main(int argc, char *argv[]) {

    ifstream fileInput(argv[1]);
    struct bitmapHeader _bmpHeader;
    fileInput.read((char *)&_bmpHeader, sizeof(struct bitmapHeader));
    fileInput.close();

    print_bitmapHeader(&_bmpHeader);

    cout << " byte " << sizeof(byte) << endl;
    cout << " word " << sizeof(word) << endl;
    cout << " dword " << sizeof(dword) << endl;
    cout << " qword " << sizeof(qword) << endl;
    cout << " bitmap Header " << sizeof(struct bitmapHeader) << endl;
    return 0;
}
