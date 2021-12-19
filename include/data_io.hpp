/**
 * The file contains data input/output functions required by the project.
 * 
 */
#pragma once
#include "data_read.hpp"
#include "data_write.hpp"

/**
 * @brief
 * ENUM CLASS that contains variables to distinguish SAFE and UNSAFE data loading/writing method.
 */
enum class IO_MODE
{
    UNSAFE,
    SAFE
};

/**
 * @class DATA_IO
 * @brief
 * DATA_IO class is a collection of data read/write functions used in the project.
 * The class is written for convenience purposes that read, and therefore,
 * the read/write methods can be accessed directly without using DATA_IO class.
 * However, it automatically chooses the type of method (SAFE/UNSAFE),
 * the use of DATA_IO class is preferred to safety.
 * DATA_IO class does not contain a validation process as
 * validation processes will be done in DATA_READ and DATA_WRITE classes.
 * DATA_IO class uses DATA_READ and DATA_WRITE classes with has-a relation.
 */
class DATA_IO
{
public:
    /**
     * @brief Construct a new data io object
     *
     * @param io_method defines that the data load/write will be done in SAFE/UNSAFE mode.
     */
    DATA_IO(IO_MODE io_method) : m_io_method(io_method)
    {
    }

    ~DATA_IO() {}

    /**
     * @brief
     * The function loads .dvec format file and returns two vectorss containing
     * - a collection of independent variables (X-Axis values)
     * - a collection of dependent variables (Y-Axis values)
     *
     * @param[in] file_name name of file to be loaded
     * @param[out] output_vec_one a collection of independent variables (X-Axis values)
     * @param[out] output_vec_two - a collection of dependent variables (Y-Axis values)
     * @return true
     * @return false
     */
    bool load_vec(const std::string file_name, std::vector<double> &output_vec_one, std::vector<double> &output_vec_two)
    {
        bool load_result = true;
        switch (m_io_method)
        {
        case IO_MODE::SAFE:
            // load_result = r_vec.load_vec_SAFE(file_name, output_vec_one, output_vec_two);
            break;
        case IO_MODE::UNSAFE:
            load_result = r_vec.load_vec_UNSAFE(file_name, output_vec_one, output_vec_two);
            break;
        }
        return load_result;
    }

    /**
     * @brief
     * The function loads .csv format file and returns two vectors containing
     * - a collection of independent variables (X-Axis values)
     * - a collection of dependent variables (Y-Axis values)
     *
     * @param[in] file_name name of file to be loaded
     * @param[out] output_vec_one a collection of independent variables (X-Axis values)
     * @param[out] output_vec_two - a collection of dependent variables (Y-Axis values)
     * @return true
     * @return false
     */
    bool load_csv(const std::string file_name, std::vector<double> &output_vec_one, std::vector<double> &output_vec_two)
    {
        bool load_result = true;
        switch (m_io_method)
        {
        case IO_MODE::SAFE:
            // load_result = r_vec.load_csv_SAFE(file_name, output_vec_one, output_vec_two);
            break;
        case IO_MODE::UNSAFE:
            load_result = r_vec.load_csv_UNSAFE(file_name, output_vec_one, output_vec_two);
            break;
        }
        return load_result;
    }

    /**
     * @brief
     * The function writes .dvec format file based on given two vectors containing
     * - a collection of independent variables (X-Axis values)
     * - a collection of dependent variables (Y-Axis values)
     *
     * @param[in] file_name name of file to be written
     * @param[in] output_vec_one a collection of independent variables (X-Axis values)
     * @param[in] output_vec_two a collection of dependent variables (Y-Axis values)
     * @return true
     * @return false
     */
    bool write_vec(const std::string file_name, const std::vector<double> &output_vec_one, const std::vector<double> &output_vec_two)
    {
        w_vec.write_vec(file_name, output_vec_one, output_vec_two);
        return true;
    }

    /**
     * @brief
     * The function writes .csv format file based on given two vectors containing
     * - a collection of independent variables (X-Axis values)
     * - a collection of dependent variables (Y-Axis values)
     *
     * @param[in] file_name name of file to be written
     * @param[in] output_vec_one a collection of independent variables (X-Axis values)
     * @param[in] output_vec_two a collection of dependent variables (Y-Axis values)
     * @return true
     * @return false
     */
    bool write_csv(const std::string file_name, const std::vector<double> &output_vec_one, const std::vector<double> &output_vec_two)
    {
        w_vec.write_csv(file_name, output_vec_one, output_vec_two);
        return true;
    }

    /**
     * @brief Get the io method object
     *
     */
    void get_io_method() const
    {
        std::cout << "Current loading method is ";
        print_mode();
    }

    /**
     * @brief Set the io method object
     *
     * @param new_mode targeted io method
     */
    void set_io_method(IO_MODE new_mode)
    {
        get_io_method();
        this->m_io_method = new_mode;
        get_io_method();
    }

private:
    IO_MODE m_io_method;
    READ_VEC r_vec;
    WRITE_VEC w_vec;

    /**
     * @brief The print current IO mode of the object.
     *
     */
    void print_mode() const
    {
        switch (m_io_method)
        {
        case IO_MODE::SAFE:
            std::cout << "SAFE" << std::endl;
            break;

        case IO_MODE::UNSAFE:
            std::cout << "UNSAFE" << std::endl;
            break;
        }
    }
};