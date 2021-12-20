#pragma once
#include "PCH.hpp"
#include "bmp_header.hpp"
#include "rgb_colour.hpp"

/**
 * @brief
 * BMP_OUT class contains funtions requires to modify and generate a .bmp file.
 * BMP_OUT class provides basic functions to write a .bmp file,
 * that does not support advanced functions such as image scaling or colour transparency.
 * For personal convenience, the BMP_OUT class uses a 2D vector instead of a 1D vector to
 * store pixels' colour data. Please be aware of it that many tutorials online use 1D vectors.
 *
 * BMP_OUT class is written based on
 * - https://www.youtube.com/watch?v=vqT5j38bWGg
 * - https://solarianprogrammer.com/2018/11/19/cpp-reading-writing-bmp-images/
 */
class BMP_OUT : public BMP_HEADER
{
public:
    /**
     * @brief
     * Construct a new BMP_OUT object without dimension initialization,
     * which needs to be used only when dimension initialization cannot be done at
     * the initialization phase of a class that uses BMP_OUT class.
     * Size of image must be initialized with member function
     * set_size() as soon as dimension is computed.
     *
     */
    BMP_OUT()
    {
        /*
            Do nothing
        */
    }

    /**
     * @brief Construct a new BMP_OUT object, and initialize sizes of an image to be created.
     *
     * @param[in] image_width Width of an image to be created.
     * @param[in] image_height Height of an image to be created.
     */
    BMP_OUT(const uint32_t image_width, const uint32_t image_height)
    {
        this->set_size(image_width, image_height);
    }

    /**
     * @brief Generates .bmp file with current pixel data based on the given name.
     *
     * @param[in] file_name Name of file to be generated, it must contain file format .bmp
     */
    void write_bmp_image(const std::string file_name)
    {
        validate_is_vector_empty();
        validate_file_format(file_name, ".bmp");

        std::ofstream write_image;
        write_image.open(file_name, std::ios::out | std::ios::binary);
        validate_is_file_created(write_image, file_name);

        this->set_file_header();
        write_image.write(reinterpret_cast<char *>(&m_file_header), size_file_header);

        this->set_info_header();
        write_image.write(reinterpret_cast<char *>(&m_info_header), size_info_header);

        for (const auto &row : this->m_pixel_colour_data)
        {
            for (const auto &pixel : row)
            {
                char8_t colour[3] = {pixel.get_blue(), pixel.get_green(), pixel.get_red()};
                write_image.write(reinterpret_cast<char *>(colour), 3);
            }
            write_image.write(reinterpret_cast<char *>(m_bmp_padding), m_required_padding);
        }
        write_image.close();
    }

    /**
     * @brief Returns the width of the image to be generated.
     *
     * @return uint32_t
     */
    uint32_t get_width() const
    {
        return this->m_image_width;
    }

    /**
     * @brief Returns the height of the image to be generated.
     *
     * @return uint32_t
     */
    uint32_t get_height() const
    {
        return this->m_image_height;
    }

    /**
     * @brief Returns the dimension of the image to be generated.
     *
     * @param[out] image_width The width of the image to be generated.
     * @param[out] image_height The height of the image to be generated.
     */
    void get_size(uint32_t &image_width, uint32_t &image_height)
    {
        image_width = this->get_width();
        image_height = this->get_height();
    }

    /**
     * @brief
     *  Set/Resize the dimesion of the image to be generated.
     *  WARNING - IT WILL REMOVE PRE-EXISTING PIXEL DATA.
     *
     * @param[in] image_width The width of the image to be generated.
     * @param[in] image_height The height of the image to be generated.
     */
    void set_size(const uint32_t image_width, const uint32_t image_height)
    {
        m_image_width = image_width;
        m_image_height = image_height;
        m_required_padding = this->compute_padding();
        RGB_COLOUR temp_colour;
        temp_colour.set_white();
        m_pixel_colour_data.resize(image_height, std::vector<RGB_COLOUR>(image_width, temp_colour));
    }

    /**
     * @brief Returns the RGB colour data of the targeted image coordinate.
     *
     * @param[in] x Targeted pixel's x-axis coordinate in pixel unit.
     * @param[in] y Targeted pixel's y-axis coordinate in pixel unit.
     * @return RGB_COLOUR
     */
    RGB_COLOUR get_pixel_colour(const uint32_t x, const uint32_t y) const
    {
        return m_pixel_colour_data[y][x];
    }

    /**
     * @brief Set the RGB colour data of the targeted image coordinate with the given RGB_COLOUR data.
     *
     * @param[in] x Targeted pixel's x-axis coordinate in pixel unit.
     * @param[in] y Targeted pixel's y-axis coordinate in pixel unit.
     * @param[in] colour RGB colour data
     */
    void set_pixel_colour(const uint32_t x, const uint32_t y, const RGB_COLOUR &colour)
    {
        m_pixel_colour_data[y][x] = colour;
    }

    /**
     * @brief Set every pixel in the image with white colour.
     *
     */
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

    /**
     * @brief Set every pixel in the image with black colour.
     *
     */
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

    /**
     * @brief Set every pixel in the image with given RGB colour data.
     *
     * @param colour RGB colour data to fill the image.
     */
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
    uint32_t m_required_padding;
    uint8_t m_bmp_padding[3] = {0, 0, 0};

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

    /**
     * @brief Set the file header of BMP file based on current information.
     *
     */
    void set_file_header()
    {
        uint32_t size_total = size_file_header + size_info_header + (m_image_width * m_image_height * 3) + (compute_padding() * m_image_height);
        m_file_header.file_type = 0x4D42;
        m_file_header.file_size = size_total;
        m_file_header.reserved1 = 0;
        m_file_header.reserved1 = 0;
        m_file_header.offset_data = size_file_header + size_info_header;
    }

    /**
     * @brief Set the infomation header of BMP file based on current information.
     *
     */
    void set_info_header()
    {
        m_info_header.info_header_size = this->size_info_header;
        m_info_header.pixel_width = this->m_image_width;
        m_info_header.pixel_height = this->m_image_height;
        m_info_header.planes = 1;
        m_info_header.bit_per_pixel = 24;
        m_info_header.bit_compression = 0;
        m_info_header.byte_size_image = 0;
        m_info_header.pixels_per_meter_x = 0;
        m_info_header.pixels_per_meter_y = 0;
        m_info_header.colours_used = 0;
        m_info_header.colours_important = 0;
    }

    /**
     * @brief Set the colour header of BMP file based on current information, but not used
     *
     */
    void set_colour_header()
    {
        /*
            Not used in the project.
        */
    }

    /**
     * @brief
     * The function validates a targeted coordinate is accessible.
     * Simply it checks targeted pixel coordinate is not bigger than the dimension of an image.
     * 
     * @param x Targeted X-coordinate in pixel.
     * @param y Targeted Y-coordinate in pixel.
     */
    void validate_coordinate(const uint32_t x, const uint32_t y){
        
        if(x > m_image_width || y > m_image_height){
            std::string error_message =
                "BMP ERROR - CANNOT ACCESS THE TARGETED COORDINATE.\n"
                "The target coordinate cannot be bigger than the image size.\n"
                "IMAGE WIDTH  : " + std::to_string(m_image_width) + "\n"
                "IMAGE HEIGHT : " + std::to_string(m_image_height) + "\n"
                "But the targeted coordinate is\n"
                "X-coordinate :" + std::to_string(x) + "\n"
                "Y-coordinate :" + std::to_string(y) + "\n";
            throw std::runtime_error(error_message);
        }
    }

    /**
     * @brief
     * The function validates a vector that contains pixel data is empty or not and
     * throws a runtime error if the vector is empty.
     *
     */
    void validate_is_vector_empty()
    {
        if (m_pixel_colour_data.empty() == true)
        {
            std::string error_message =
                "BMP ERROR - NO DATA TO GENERATE .BMP FILE\n"
                "There is no PIXEL DATA to write .bmp file is empty.\n";
            throw std::runtime_error(error_message);
        }
    }

    /**
     * @brief
     * The function validates the file format is correct and
     * throws a "runtime exception" if the format is not supported.
     *
     * @param[in] file_name The path to the targeted file.
     * @param[in] target_format The required file format.
     */
    void validate_file_format(const std::string file_name, const std::string target_format)
    {
        std::filesystem::path file_path(file_name);
        if (file_path.extension() != target_format)
        {
            std::string error_message =
                "BMP ERROR - INCORRECT FILE FORMAT.\n"
                "Input file format needs to be " + target_format + "\n"
                "But received file - " + file_name + "- format is " + file_path.extension().string() + "\n";
            throw std::invalid_argument(error_message);
        }
    }

    /**
     * @brief
     * The function validates files to be written is generated or not and
     * throws a runtime exception if file generation is failed.
     *
     * @param created_file object that points the file needed to be created
     * @param file_name name of file needed to be created
     */
    void validate_is_file_created(const std::ofstream &created_file, const std::string &file_name)
    {
        if (created_file.is_open() == false)
        {
            std::string error_message =
                "BMP ERROR - FAILED TO CREATE A .BMP FILE TO PLOT RESULT.\n"
                "Failed to create" + file_name + ".\n";
            throw std::runtime_error(error_message);
        }
    }
};