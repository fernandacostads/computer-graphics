#include "Bitmap.hpp"
#include "BitmapHeaderFile.h"
#include "BitmapHeaderInfo.h"
#include <iostream>
#include <fstream>

Bitmap::Bitmap(int width, int height) : width(width), height(height), pixels(new float[height*width*3]()){}

void Bitmap::setPixel(int x, int y, float red, float green, float blue) {
    float *aux = pixels;
    aux+=(y*3)*width+(x*3);
    aux[0] = red;
    aux[1] = green;
    aux[2] = blue;
}

bool Bitmap::save(string fileName) {
    BitmapHeaderInfo headerInfo;
    char b = 'B';
    char m = 'M';
    int filesize = sizeof(BitmapHeaderFile) + sizeof(BitmapHeaderInfo) + (height*width*3);
    int reserved = 0;
    int dataOffset = sizeof(BitmapHeaderFile) + sizeof(BitmapHeaderInfo);
    headerInfo.height = height;
    headerInfo.width = width;

    FILE* file;
    file = fopen(fileName.c_str(), "wb");

    if(!file){
        return false;
    }

    fwrite((const void*)&b, sizeof(char), 1, file);
    fwrite((const void*)&m, sizeof(char), 1, file);
    fwrite((const void*)&filesize, sizeof(int), 1, file);
    fwrite((const void*)&reserved, sizeof(int), 1, file);
    fwrite((const void*)&dataOffset, sizeof(int), 1, file);

    fwrite((const void*)&headerInfo, sizeof(BitmapHeaderInfo), 1, file);
    fwrite((const void*)pixels, (size_t)height*width*3, 1, file);

    fclose(file);

    return true;
}
float* Bitmap::getPixels(){
    return pixels;
}
