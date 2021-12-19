/**
 * The file contains data output functions required by the project.
 */
#pragma once
#include "PCH.hpp"

class WRITE_VEC
{
public:
    WRITE_VEC() {}
    virtual ~WRITE_VEC() {}

    bool write_vec_UNSAFE(std::string file_name, std::vector<double> &output_vec)
    {
        std::ofstream write_vec_file;
        write_vec_file.open(file_name, std::ios::out);
        if (write_vec_file.is_open() == false)
        {
            std::cout << "Failed to generate: " << file_name << "\n";
            return false;
        }

        std::string output_line;
        output_line = std::to_string(output_vec.size());
        write_vec_file << output_line << "\n";

        for (uint32_t iter = 0; iter < output_vec.size(); iter++)
        {
            write_vec_file << std::to_string(output_vec[iter]) << "\n";
        }
        write_vec_file.close();
        return true;
    }

    bool write_vec_UNSAFE(std::string file_name, std::vector<double> &vec_one, std::vector<double> &vec_two)
    {
        std::ofstream write_vec_file;
        write_vec_file.open(file_name, std::ios::out);
        if (write_vec_file.is_open() == false)
        {
            std::cout << "Failed to generate: " << file_name << "\n";
            return false;
        }

        std::string output_line;
        output_line = std::to_string(vec_one.size());
        write_vec_file << output_line << "\n";

        for (uint32_t iter = 0; iter < vec_one.size(); iter++)
        {
            write_vec_file << std::to_string(vec_one[iter]) << " " << std::to_string(vec_two[iter]) << "\n";
        }
        write_vec_file.close();
        return true;
    }

    bool write_csv_UNSAFE(std::string file_name, std::vector<double> &vec_one, std::vector<double> &vec_two)
    {
        std::ofstream write_vec_file;
        write_vec_file.open(file_name, std::ios::out);
        if (write_vec_file.is_open() == false)
        {
            std::cout << "Failed to generate: " << file_name << "\n";
            return false;
        }

        std::string output_line;
        output_line = std::to_string(vec_one.size());
        write_vec_file << output_line << "\n";

        for (uint32_t iter = 0; iter < vec_one.size(); iter++)
        {
            write_vec_file << std::to_string(vec_one[iter]) << ", " << std::to_string(vec_two[iter]) << "\n";
        }
        write_vec_file.close();
        return true;
    }

    bool write_vec_SAFE(std::string file_name, std::vector<double> &output_vec)
    {
        return false;
    }

private:
};