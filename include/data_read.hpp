/**
 * The file contains data input functions required by the project.
*/

#pragma once
#include "PCH.hpp"

class READ_VEC
{
public:
    READ_VEC(){}
    virtual ~READ_VEC(){}

    bool load_vec_UNSAFE(std::string file_name, std::vector<double> &output_vec)
    {
        std::ifstream load_vec;
        load_vec.open(file_name, std::ios::in);
        if (load_vec.is_open() == false)
        {
            std::cout << "Failed to open: " << file_name << "\n"
                      << "Please check " << file_name << " is exist.\n"
                      << std::endl;
            return false;
        }

        std::string read_line;
        while (load_vec.peek() == '%')
        {
            std::getline(load_vec, read_line);
        }

        uint32_t vec_len = 0;
        load_vec >> vec_len;

        double temp_val;
        output_vec.reserve(vec_len);
        output_vec = std::vector<double>(vec_len, 0);
        for (uint32_t iter = 0; iter < vec_len; iter++)
        {
            load_vec >> temp_val;
            output_vec[iter] = temp_val;
        }
        load_vec.close();

        return true;
    }

    bool load_vec_SAFE(std::string file_name, std::vector<double> &output_vec){
        return false;
    }
};