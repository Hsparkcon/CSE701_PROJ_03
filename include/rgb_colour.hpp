#pragma once
#include "PCH.hpp"

/**
 * @brief
 * RGB_COLOUR struct is user-defined struct used to store RGB colour data of pixel.
 *
 * @details
 * Each colour channel uses uint8_t to data of store a value.
 * RGB stores colour data by using three colour channels
 * - RED
 * - GREEN
 * - BLUE
 *
 * Each channel stores an integer value range between 0 to 255.
 * When each channel's value is near 0, the colour becomes black.
 * When each channel's value is near 255, the colour becomes white.
 * When one channel has a value near 255 while the other is near 0,
 * the colour becomes the colour of the channel with a high value.
 *
 * For more detail, please read
 * https://en.wikipedia.org/wiki/RGB_color_model
 *
 */
struct RGB_COLOUR
{
private:
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;

public:
    /**
     * @brief Construct a new RGB_COLOUR object initialized with black colour.
     *
     */
    RGB_COLOUR()
    {
        this->set_black();
    }

    /**
     * @brief Construct a new RGB_COLOUR object initialized with given colour data.
     *
     * @param red value of the red colour channel
     * @param green value of the green colour channel
     * @param blue value of the blue colour channel
     */
    RGB_COLOUR(uint8_t red, uint8_t green, uint8_t blue)
    {
        this->set_colour(red, green, blue);
    }

    ~RGB_COLOUR() {}

    /**
     * @brief Set the colour value with given colour data.
     *
     * @param red value of the red colour channel
     * @param green value of the green colour channel
     * @param blue value of the blue colour channel
     */
    void set_colour(uint8_t red, uint8_t green, uint8_t blue)
    {
        m_red = red;
        m_green = green;
        m_blue = blue;
    }

    /**
     * @brief Set the colour value to black.
     *
     */
    void set_black()
    {
        m_red = 0;
        m_green = 0;
        m_blue = 0;
    }

    /**
     * @brief Set the colour value to white.
     *
     */
    void set_white()
    {
        m_red = 255;
        m_green = 255;
        m_blue = 255;
    }

    /**
     * @brief Returns the value of the red colour channel.
     *
     * @return uint8_t
     */
    uint8_t get_red() const
    {
        return this->m_red;
    }

    /**
     * @brief Returns the value of the green colour channel.
     *
     * @return uint8_t
     */
    uint8_t get_green() const
    {
        return this->m_green;
    }

    /**
     * @brief Returns the value of the blue colour channel.
     *
     * @return uint8_t
     */
    uint8_t get_blue() const
    {
        return this->m_blue;
    }
};