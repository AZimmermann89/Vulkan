#include "TifLoader.h"
#include <vector>

using namespace EngineCore;
using namespace Util;

bool TifLoader::LoadImage(const char * filePath)
{
    FILE* filePtr = nullptr;
    int result = fopen_s(&filePtr, ReturnAbsAssetPath(filePath).c_str(), "rb");

    if (result != 0 || filePtr == nullptr)
    {
        printf("ImageLoader: Error in opening file %s.", filePath);
        return false;
    }

    TIFHeader header;
    result = fread(&header, sizeof(TIFHeader), 1 , filePtr);

    if (result != 1 || header.fourtytwo != 42)
    {
        printf("ImageLoader: Error in reading header from file %s.", filePath);
        return false;
    }

    unsigned short numberOfIFDEntries{ 0 };
    result = fread(&numberOfIFDEntries, sizeof(unsigned short), 1, filePtr);
     short someShort = (short)numberOfIFDEntries;

    std::vector<TIFImageFileDirectoryEntry> imageFileDirEntries{};

    for (int i = 0; i<numberOfIFDEntries; i++)
    {
        TIFImageFileDirectoryEntry entry{};
        fread(&entry, sizeof(TIFImageFileDirectoryEntry), 1, filePtr);
        imageFileDirEntries.push_back(entry);
    }

//     BMPDIBHEADER_BM dibHeader;
//     if (IsHeaderType(header.type, "BM"))
//     {
//         result = fread(&dibHeader, sizeof(BMPDIBHEADER_BM), 1, (FILE*)filePtr);
//     }
//     else
//     {
//         printf("ImageLoader: Error, BMP Type not supported.");
//        return false;
//     }

    return true;
}

// 
// inline bool ImageLoader::IsHeaderType(unsigned char fileTypePtr[], const char* fileType)
// {
//   //  return memcmp(fileTypePtr, fileType, sizeof(BMPHeader::type)) == 0;
// }
// 