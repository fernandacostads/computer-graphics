#ifndef COMPUTACAOGRAFICA_BITMAP_HPP
#define COMPUTACAOGRAFICA_BITMAP_HPP


#include <cstdint>
#include <string>
#include <memory>
using namespace std;
class Bitmap {
public:
    Bitmap(int width, int height);
    void setPixel(int x, int y, float red, float green, float blue);
    bool save(string fileName);
    float* getPixels();
private:
    int width{0};
    int height{0};
    float *pixels{nullptr};
};


#endif
