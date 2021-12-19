#pragma once
#include "PCH.hpp"

/**
 * @brief
 * BMP_HEADER class contains structure of header required for BMP file.
 * Each header structure is written based on the following links
 * - https://en.wikipedia.org/wiki/BMP_file_format
 * - http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm
 * - https://docs.fileformat.com/image/bmp/
 * - https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader
 * - https://solarianprogrammer.com/2018/11/19/cpp-reading-writing-bmp-images/
 *
 * BMP_HEADER class contains three header structures
 * - BMP_FILE_HEADER
 * - BMP_INFO_HEADER
 * - BMP_COLOUR_HEADER
 * In CSE701 Project 03, the plot functions that generate the .bmp file do not support colour transparency.
 * Therefore, the BMP_COLOUR_HEADER structure is not used in the project.
 * However, it is contained in BMP_HEADER class for future usage.
 */
class BMP_HEADER
{
public:
    /**
     * @brief default contructor
     *
     */
    BMP_HEADER() {}

    /**
     * @brief default destructor
     *
     */
    ~BMP_HEADER() {}

protected:
/*
    #pragma pack(push, 1) is used to prevent padding issue.
    with default setting, sizeof(BMP_FILE_HEADER) equals to 16 bytes even sum of size of every variable inside stucut is 14 bytes.
    It is because compiler adds extra 2 bytes at the end of struct to let the size is power of 4 bytes.
    It causes error in size of BMP header size that image viewer expect 54 bytes while actual size is 56 bytes.
    This will push every data in the image file (in binary) to right by 2bytes which will destory reqired structure.

    To prevent the problem,
        - unsigned char array with size 14 byes => unsigned char file_header[14] or
        - turn off automated padding option.
    can be used

    In this project,
    structure with #pragma pack(push, 1) is used for code readability (use structure with named variable).

    Note: https://solarianprogrammer.com/2018/11/19/cpp-reading-writing-bmp-images/
*/
#pragma pack(push, 1)
    /**
     * @brief
     * FILE_HEADER structure of .bmp format.
     * The size of the struct must be 14 bytes.
     * Must be aware of automated padding to prevent struct size expansion.
     */
    struct BMP_FILE_HEADER
    {
        uint16_t file_type{0x4D42}; // type BM in hex is 4D42, and 0x is for denoting hex.
        uint32_t file_size{0};      // file size in byte = size_of(BMP_FILE_HEADER) + size_of(BMP_INFO_HEADER) + size_of(IMAGE)
        uint16_t reserved1{0};      // always 0
        uint16_t reserved2{0};      // always 0
        uint32_t offset_data{0};    // start position of the pixel data in the file = size_of(BMP_FILE_HEADER) + size_of(BMP_INFO_HEADER) + 1
    };
#pragma pack(pop)

    /**
     * @brief
     * INFO_HEADER structure of .bmp format.
     * The size of the struct must be 40 bytes.
     */
    struct BMP_INFO_HEADER
    {
        uint32_t info_header_size{0}; // size of bmp info header struct
        int32_t pixel_width{0};       // width of bmp image
        int32_t pixel_height{0};      // height of bmp image
                                      /*
                                          Note why not uint32_t? (why value can be negative?)
                                          check - https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader
                                      */

        uint16_t planes{1};            // number of planes of target device = 1
        uint16_t bit_per_pixel{0};     // Number of bits per pixel. For uncompressed image bpp = avg of bit per pixel
        uint32_t bit_compression{0};   // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images
        uint32_t byte_size_image{0};   // Size of image in byte. The value can be set to 0 if it is uncompressed RGB bmp image.
        int32_t pixels_per_meter_x{0}; // Horizontal resolution of the target device
        int32_t pixels_per_meter_y{0}; // Vertical resolution of the target device
        uint32_t colours_used{0};      // Num of colour indices in the colour table. 0 for the max num of colours allowed by bit_count
        uint32_t colours_important{0}; // Num of colours use for bmp displaying. 0 for all colour are used
    };

    /**
     * @brief
     * COLOUR_HEADER of .bmp format.
     * The size of the struct must be 24 bytes.
     *
     */
    struct BMP_COLOUR_HEADER
    {
        uint32_t red_mask{0x00ff0000};          // Bit mask for the red channel = 255 0 0 in RGB order
        uint32_t green_mask{0x0000ff00};        // Bit mask for the green channel  = 0 255 0 in RGB order
        uint32_t blue_mask{0x000000ff};         // Bit mask for the blue channel = 0 0 255 in RGB order
        uint32_t alpha_mask{0xff000000};        // Bit mask for the alpha channel = 255 0 0 0 = transparency of colour
        uint32_t colour_space_type{0x73524742}; // Default "sRGB" (0x73524742) => s = 73 R = 52 G = 47 B = 42
        uint32_t unused[16]{0};                 // Unused data for sRGB color space
    };

private:
};