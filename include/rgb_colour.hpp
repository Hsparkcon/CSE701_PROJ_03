#pragma once
#include "PCH.hpp"

struct RGB_COLOUR
{
private:
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;

public:
    RGB_COLOUR()
    {
        this->set_black();
    }

    RGB_COLOUR(uint8_t red, uint8_t green, uint8_t blue)
    {
        this->set_colour(red, green, blue);
    }

    ~RGB_COLOUR() {}

    void set_colour(uint8_t red, uint8_t green, uint8_t blue)
    {
        m_red = red;
        m_green = green;
        m_blue = blue;
    }

    void set_black()
    {
        m_red = 0;
        m_green = 0;
        m_blue = 0;
    }

    void set_white()
    {
        m_red = 255;
        m_green = 255;
        m_blue = 255;
    }

    uint8_t get_red() const
    {
        return this->m_red;
    }

    uint8_t get_green() const
    {
        return this->m_green;
    }

    uint8_t get_blue() const
    {
        return this->m_blue;
    }
};