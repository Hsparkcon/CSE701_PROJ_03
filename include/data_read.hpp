#pragma once
#include "PCH.hpp"

/**
 * @class READ_DATA
 * @brief READ_DATA class is designed to contain functions to load data required by the program.
 * @details
 *  READ_DATA class supports the following data formats.
 *  .dvec - custom data format for the project, preferred when the use of a spreadsheet is not expected
 *  .csv - comma-separated variables format for users who wants to load data from Excel, Matlab, or other spreadsheet-based data formats.
 *
 * UNSAFE or SAFE
 *  The keyword UNSAFE and SAFE distinguish that the loading method checks loaded data is following the required data format.
 *  For example, load method with
 *  - SAFE keyword will check that there are two data in each line of loaded file, and each data is number while
 *  - UNSAFE keyword will load data without validation.
 *  SAFE method is preferred when the input data is generated manually - i.e.) entire data is typed by hand.
 *  UNSAFE method is preferred when the input data is generated by software - i.e.) entire data is generated by Matlab
 */
class READ_VEC
{
public:
    READ_VEC() {}
    virtual ~READ_VEC() {}

    /**
     * @brief
     * The function loads .dvec format file, and
     * it returns vector x containing independent data and vector y containing dependent data
     * without checking the data format in the file.
     * For accuracy in computation, the type of loaded data's element is 'double'.
     *
     * @param[in] file_name Path to the file that will be loaded.
     * @param[out] vec_one The vector that stores the independent values (X-Axis) of the observed data.
     * @param[out] vec_two The vector that stores the independent values (Y-Axis) of the observed data.
     * @return true When data load is succeeded.
     * @return false When data load is failed.
     */
    bool load_vec_UNSAFE(const std::string file_name, std::vector<double> &vec_one, std::vector<double> &vec_two)
    {
        validate_target_is_exist(file_name);
        validate_target_is_file(file_name);
        validate_target_format(file_name, ".dvec");

        std::ifstream load_vec;
        load_vec.open(file_name, std::ios::in);
        validate_file_is_opened(load_vec, file_name);

        std::string read_line;
        while (load_vec.peek() == '%')
        {
            std::getline(load_vec, read_line);
        }

        uint32_t vec_len = 0;
        load_vec >> vec_len;

        double temp_val_one;
        double temp_val_two;
        vec_one = std::vector<double>(vec_len, 0);
        vec_two = std::vector<double>(vec_len, 0);
        for (uint32_t iter = 0; iter < vec_len; iter++)
        {
            load_vec >> temp_val_one >> temp_val_two;
            vec_one[iter] = temp_val_one;
            vec_two[iter] = temp_val_two;
        }
        load_vec.close();

        return true;
    }

    /**
     * @brief
     * The function loads .csv format file, and
     * it returns vector x containing independent data and vector y containing dependent data
     * without checking the data format in the file.
     * For accuracy in computation, the type of loaded data's element is 'double'.
     *
     * @param[in] file_name Path to the file that will be loaded.
     * @param[out] vec_one The vector that stores the independent values (X-Axis) of the observed data.
     * @param[out] vec_two The vector that stores the independent values (Y-Axis) of the observed data.
     * @return true When data load is succeeded.
     * @return false When data load is failed.
     */
    bool load_csv_UNSAFE(const std::string file_name, std::vector<double> &vec_one, std::vector<double> &vec_two)
    {
        validate_target_is_exist(file_name);
        validate_target_is_file(file_name);
        validate_target_format(file_name, ".csv");


        std::ifstream load_csv;
        load_csv.open(file_name, std::ios::in);
        validate_file_is_opened(load_csv, file_name);

        std::string read_line;
        while (load_csv.peek() == '%')
        {
            std::getline(load_csv, read_line);
        }

        uint32_t vec_len = 0;
        load_csv >> vec_len;

        double temp_val_one;
        char delimeter;
        double temp_val_two;
        vec_one = std::vector<double>(vec_len, 0);
        vec_two = std::vector<double>(vec_len, 0);
        for (uint32_t iter = 0; iter < vec_len; iter++)
        {
            load_csv >> temp_val_one >> delimeter >> temp_val_two;
            vec_one[iter] = temp_val_one;
            vec_two[iter] = temp_val_two;
        }
        load_csv.close();

        return true;
    }

    /**
     * @brief
     * The function loads .dvec format file, and
     * it returns vector x containing independent data and vector y containing dependent data
     * with checking the data format in the file.
     * For accuracy in computation, the type of loaded data's element is 'double'.
     *
     * @param[in] file_name Path to the file that will be loaded.
     * @param[out] vec_one The vector that stores the independent values (X-Axis) of the observed data.
     * @param[out] vec_two The vector that stores the independent values (Y-Axis) of the observed data.
     * @return true When data load is succeeded.
     * @return false When data load is failed.
     */
    bool load_vec_SAFE(const std::string file_name, std::vector<double> &vec_one, std::vector<double> &vec_two)
    {
        return false;
    }

    /**
     * @brief
     * The function loads .csv format file, and
     * it returns vector x containing independent data and vector y containing dependent data
     * with checking the data format in the file.
     * For accuracy in computation, the type of loaded data's element is 'double'.
     *
     * @param[in] file_name Path to the file that will be loaded.
     * @param[out] vec_one The vector that stores the independent values (X-Axis) of the observed data.
     * @param[out] vec_two The vector that stores the independent values (Y-Axis) of the observed data.
     * @return true When data load is succeeded.
     * @return false When data load is failed.
     */
    bool load_csv_SAFE(const std::string file_name, std::vector<double> &vec_one, std::vector<double> &vec_two)
    {
        return false;
    }

private:
    /**
     * @brief
     *  The function validates the existence of the received path and
     *  throws a "runtime exception" if the path does not exist.
     *
     * @param[in] file_name The path to the targeted file.
     */
    void validate_target_is_exist(const std::string &file_name)
    {
        std::filesystem::path file_path(file_name);
        if (std::filesystem::exists(file_path) == false)
        {
            std::string error_message =
                "READ ERROR - FILE DOES NOT EXIST.\n"
                "There is no such file exists at the given path.\n"
                "Received path - " + file_name + "\n";
            throw std::invalid_argument(error_message);
        }
    }

    /**
     * @brief
     *  The function validates the targeted path is a file and
     *  throws a "runtime exception" if the path is not a file.
     *
     * @param[in] file_name The path to the targeted file.
     */
    void validate_target_is_file(const std::string &file_name)
    {
        std::filesystem::path file_path(file_name);
        if (std::filesystem::is_regular_file(file_path) == false)
        {
            std::string error_message =
                "READ ERROR - INCORRECT INPUT.\n"
                "Input needs to be path to a file\n"
                "But the given path - " + file_name + " - is not a file.\n";
            throw std::invalid_argument(error_message);
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
    void validate_target_format(const std::string file_name, const std::string target_format)
    {
        std::filesystem::path file_path(file_name);
        if (file_path.extension() != target_format)
        {
            std::string error_message =
                "READ ERROR - INCORRECT FILE FORMAT.\n"
                "Input file format needs to be " + target_format + "\n"
                "But received file - " + file_name + "- format is " + file_path.extension().string() + "\n";
            throw std::invalid_argument(error_message);
        }
    }

    /**
     * @brief
     *  The function validates the targeted file is opened and 
     *  throws a "runtime exception" if the targeted file is failed to be opened.
     *
     * @param opened_file Variable that points opened file.
     * @param file_name Path to the targeted data to provide which file is failed to be opened.
     */
    void validate_file_is_opened(const std::ifstream &opened_file, const std::string file_name)
    {
        if (opened_file.is_open() == false)
        {
            std::string error_message =
                "READ ERROR - FAILED TO OPEN A FILE.\n"
                "Please check " + file_name + " is correct.\n";
            throw std::runtime_error(error_message);
        }
    }
};