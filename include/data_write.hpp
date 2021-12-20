#pragma once
#include "PCH.hpp"

/**
 * @class WRITE_DATA
 * @brief WRITE_DATA class is designed to contain functions to write data required by the program.
 * @details
 * WRITE_DATA class supports the following data formats.
 *  .dvec - custom data format for the project, preferred when the use of a spreadsheet is not expected
 *  .csv - comma-separated variables format for users who wants to write data to be used with Excel, Matlab, or other spreadsheet-based data formats.
 *
 * Unlike READ_DATA class, WRITE_DATA class does not provide the SAFE/UNSAFE methods.
 * It provides the UNSAFE method (according to the term SAFE method used in READ_DATA class) only
 * as data to be written are passed with specific data type instead of reading expected data type from a file.
 * However, it still validates
 * the correctness of the file format to be written and
 * the length of data to be written
 * as minimum requirements.
 */
class DATA_WRITE
{
public:
    DATA_WRITE() {}
    virtual ~DATA_WRITE() {}

    /**
     * @brief
     * The function writes a .dvec file based on the received input vectors.
     *  - a collection of independent variables (X-Axis values)
     *  - a dependent variables (Y-Axis values)
     * The length of input vectors must match.
     * For result accuracy, the type of written data's element is 'double.'
     * Preferred when the use of a spreadsheet is not expected.
     *
     * @param[in] file_name file name to be written, it must contain file format .dvec
     * @param[in] vec_one collection of independent variables (X-Axis values) to be written
     * @param[in] vec_two collection of dependent variables (Y-Axis values) to be written
     * @return true
     * @return false
     */
    bool write_vec(const std::string file_name, const std::vector<double> &vec_one, const std::vector<double> &vec_two)
    {
        validate_is_vector_empty(vec_one, file_name + "_x");
        validate_is_vector_empty(vec_one, file_name + "_y");
        validate_vector_length_match(file_name, vec_one, vec_two);
        validate_file_format(file_name, ".dvec");

        std::ofstream write_vec_file;
        write_vec_file.open(file_name, std::ios::out);
        validate_is_file_created(write_vec_file, file_name);

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

    /**
     * @brief
     * The function writes a .csv file based on the received input vectors.
     *  - a collection of independent variables (X-Axis values)
     *  - a dependent variables (Y-Axis values)
     * The length of input vectors must match.
     * For result accuracy, the type of written data's element is 'double.'
     * Preferred when the use of a spreadsheet is expected.
     *
     * @param[in] file_name file name to be written, it must contain file format .csv
     * @param[in] vec_one collection of independent variables (X-Axis values) to be written
     * @param[in] vec_two collection of dependent variables (Y-Axis values) to be written
     * @return true
     * @return false
     */
    bool write_csv(const std::string file_name, const std::vector<double> &vec_one, const std::vector<double> &vec_two)
    {
        validate_is_vector_empty(vec_one, file_name + "_x");
        validate_is_vector_empty(vec_one, file_name + "_y");
        validate_vector_length_match(file_name, vec_one, vec_two);
        validate_file_format(file_name, ".csv");

        std::ofstream write_vec_file;
        write_vec_file.open(file_name, std::ios::out);
        validate_is_file_created(write_vec_file, file_name);

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

private:
    /**
     * @brief
     * The function validates a passed vector is empty or not and
     * throws a runtime error if the vector is empty.
     *
     * @param[in] input_vec Collection of value
     * @param[in] vec_name Type of data collection, it is better to _x or _y to denote the vector contains dependent/independent variables.
     */
    void validate_is_vector_empty(const std::vector<double> &input_vec, const std::string vec_name)
    {
        if (input_vec.empty() == true)
        {
            std::string error_message =
                "WRITE ERROR - NOTHING TO WRITE\n"
                "Input vector - " + vec_name + " - is empty; there is nothing to write.";
            throw std::runtime_error(error_message);
        }
    }

    /**
     * @brief
     * The function validates the number of given data collection matches each other and
     * throws runtime error if there is a mismatch.
     *
     * @param file_name name of file to be written
     * @param vec_one collection of independent variables (X-Axis values) to be written
     * @param vec_two collection of independent variables (Y-Axis values) to be written
     */
    void validate_vector_length_match(const std::string file_name, const std::vector<double> &vec_one, const std::vector<double> &vec_two)
    {
        if (vec_one.size() != vec_two.size())
        {
            std::string error_message =
                "WRITE ERROR - VECTOR LENGTH MISMATCH\n"
                "Cannot proceed writing " + file_name + "\n"
                "Number of elements in given vector must be matched, but\n"
                "X-data: " + std::to_string(vec_one.size()) + "\n"
                "Y-data: " + std::to_string(vec_two.size()) + "\n";
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
                "WRITE ERROR - INCORRECT FILE FORMAT\n"
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
                "WRITE ERROR - FAILED TO CREATE A FILE TO WRITE RESULT\n"
                "Failed to create" + file_name + ".\n";
            throw std::runtime_error(error_message);
        }
    }
};