/**
 * The file contains data input/output functions required by the project.
 * The class DATA_IO uses DATA_READ and DATA_WRITE classes with has-a relation.
*/
#pragma once
#include "data_read.hpp"
#include "data_write.hpp"

enum class IO_MODE
{
    UNSAFE,
    SAFE
};

class DATA_IO
{
public:
    DATA_IO(IO_MODE io_method) : m_io_method(io_method)
    {
    }

    ~DATA_IO() {}

    bool load_vec(std::string file_name, std::vector<double> &output_vec)
    {
        bool load_result = true;
        switch (m_io_method)
        {
        case IO_MODE::SAFE:
            load_result = r_vec.load_vec_SAFE(file_name, output_vec);
            break;
        case IO_MODE::UNSAFE:
            load_result = r_vec.load_vec_UNSAFE(file_name, output_vec);
            break;
        }
        return load_result;
    }

    bool write_vec(std::string file_name, std::vector<double> &output_vec)
    {
        switch (m_io_method)
        {
        case IO_MODE::SAFE:
            w_vec.write_vec_SAFE(file_name, output_vec);
            break;
        case IO_MODE::UNSAFE:
            w_vec.write_vec_UNSAFE(file_name, output_vec);
            break;
        }
        return true;
    }

    void check_io_method() const
    {
        std::cout << "Current loading method is ";
        print_mode();
    }

    void set_io_method(IO_MODE new_mode)
    {
        check_io_method();
        this->m_io_method = new_mode;
        print_mode();
    }

private:
    IO_MODE m_io_method;
    READ_VEC r_vec;
    WRITE_VEC w_vec;

    void print_mode() const;
};