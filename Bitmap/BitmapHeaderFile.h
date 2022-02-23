#ifndef COMPUTACAOGRAFICA_BITMAPHEADERFILE_H
#define COMPUTACAOGRAFICA_BITMAPHEADERFILE_H

#include <cstdint>

#pragma pack(2)
struct BitmapHeaderFile{
    char header[2]{'B','M'};
    uint32_t filesize;
    uint32_t reserved{0};
    uint32_t dataOffset;
};
#endif
