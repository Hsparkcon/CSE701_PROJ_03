#pragma once
#include "PCH.hpp"
#include "bmp_header.hpp"
#include "rgb_colour.hpp"

class BMP_OUT : public BMP_HEADER
{
public:
    BMP_OUT()
    {
        /*
            default constructor need to be deleted
        */
    }

    BMP_OUT(const uint32_t image_width, const uint32_t image_height)
    {
        this->set_size(image_width, image_height);
    }

    void write_bmp_image(const std::string file_name)
    {
        std::ofstream write_image;
        write_image.open(file_name, std::ios::out | std::ios::binary);

        if (write_image.is_open() == false)
        {
            throw std::runtime_error("Failed to create a bmp file.");
        }

        this->set_file_header();
        this->set_info_header();
        write_image.write(reinterpret_cast<char *>(&m_file_header), size_file_header);
        write_image.write(reinterpret_cast<char *>(&m_info_header), size_info_header);

        for (const auto &row : this->m_pixel_colour_data)
        {
            for (const auto &pixel : row)
            {
                char8_t colour[3] = {pixel.get_blue(), pixel.get_green(), pixel.get_red()};
                write_image.write(reinterpret_cast<char *>(colour), 3);
            }
            write_image.write(reinterpret_cast<char *>(bmp_padding), required_padding);
        }

        write_image.close();
    }

    uint32_t get_width() const
    {
        return this->m_image_width;
    }

    uint32_t get_height() const
    {
        return this->m_image_height;
    }

    void get_size(uint32_t &image_width, uint32_t &image_height)
    {
        image_width = this->get_width();
        image_height = this->get_height();
    }

    void set_size(const uint32_t image_width, const uint32_t image_height)
    {
        this->m_image_width = image_width;
        this->m_image_height = image_height;
        this->required_padding = this->compute_padding();
        RGB_COLOUR temp_colour;
        temp_colour.set_white();
        m_pixel_colour_data.resize(image_height, std::vector<RGB_COLOUR>(image_width, temp_colour));
    }

    RGB_COLOUR get_pixel_colour(const uint32_t x, const uint32_t y) const
    {
        return m_pixel_colour_data[y][x];
    }

    void set_pixel_colour(const uint32_t x, const uint32_t y, const RGB_COLOUR &colour)
    {
        m_pixel_colour_data[y][x] = colour;
    }

    void set_image_white()
    {
        RGB_COLOUR temp_colour;
        temp_colour.set_white();
        for (auto &row : this->m_pixel_colour_data)
        {
            for (auto &pixel_data : row)
            {
                pixel_data = temp_colour;
            }
        }
    }

    void set_image_black()
    {
        RGB_COLOUR temp_colour;
        temp_colour.set_black();
        for (auto &row : this->m_pixel_colour_data)
        {
            for (auto &pixel_data : row)
            {
                pixel_data = temp_colour;
            }
        }
    }

    void set_image_with(const RGB_COLOUR &colour)
    {
        for (auto &row : this->m_pixel_colour_data)
        {
            for (auto &pixel_data : row)
            {
                pixel_data = colour;
            }
        }
    }

private:
    uint32_t m_image_width;
    uint32_t m_image_height;
    std::vector<std::vector<RGB_COLOUR>> m_pixel_colour_data;

    const uint32_t size_file_header = 14; // in bytes
    const uint32_t size_info_header = 40; // in bytes
    BMP_FILE_HEADER m_file_header;
    BMP_INFO_HEADER m_info_header;
    BMP_COLOUR_HEADER m_colour_header;

    uint32_t required_padding;
    char8_t bmp_padding[3] = {0, 0, 0};
    
    uint32_t compute_padding()
    {
        return (4 - (this->m_image_width * 3) % 4) % 4;
        /*
            Bytes required by colour = image_width * sum(bytes used by each colour channel) = image_width * 3
            Bytes over = Bytes required by colour % 4
            Bytes left = 4 - Bytes over
            Preventing case Bytes left equals 0 = Bytes left % 4
        */
    }

    void set_file_header()
    {
        uint32_t size_total = size_file_header + size_info_header + (m_image_width * m_image_height * 3) + (compute_padding() * m_image_height);
        m_file_header.file_type = 0x4D42;
        m_file_header.file_size = size_total;
        m_file_header.reserved1 = 0;
        m_file_header.reserved1 = 0;
        m_file_header.offset_data = size_file_header + size_info_header;
    }

    void set_info_header()
    {
        m_info_header.info_header_size = this->size_info_header;
        m_info_header.pixel_width = this->m_image_width;
        m_info_header.pixel_height = this->m_image_height;
        m_info_header.planes = 1;
        m_info_header.bit_per_pixel = 24;
        m_info_header.bit_compression = 0;
        m_info_header.bit_size_image = 0;
        m_info_header.pixels_per_meter_x = 0;
        m_info_header.pixels_per_meter_y = 0;
        m_info_header.bit_colours_used = 0;
        m_info_header.bit_colours_important = 0;
    }

    void set_colour_header()
    {
        /*
            not planned to use.
        */
    }
};