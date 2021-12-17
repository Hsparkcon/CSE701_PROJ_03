#pragma once
#include "PCH.hpp"

namespace ARRAY_OPER
{
    template <typename T>
    void array_xy_add(const std::vector<T> &arr_x, const std::vector<T> &arr_y, const std::vector<T> &arr_result)
    {
        ARRAY_OPER::validate_input_len(arr_x.size(), arr_y.size(), arr_result.size());
        for (uint32_t index = 0; index < arr_x.size(); index++)
        {
            arr_result[index] = arr_x[index] + arr_y[index];
        }
    }

    template <typename T>
    void array_xy_sub(const std::vector<T> &arr_x, const std::vector<T> &arr_y, const std::vector<T> &arr_result)
    {
        ARRAY_OPER::validate_input_len(arr_x.size(), arr_y.size(), arr_result.size());
        for (uint32_t index = 0; index < arr_x.size(); index++)
        {
            arr_result[index] = arr_x[index] - arr_y[index];
        }
    }

    template <typename T>
    T array_x_sum(const std::vector<T> &array)
    {
        T temp_result = static_cast<T>(0);
        temp_result = std::accumulate(array.cbegin(), array.cend(), temp_result);
        return temp_result;
    }

    template <typename T>
    T array_xx_sum(const std::vector<T> &array)
    {
        T temp_result = static_cast<T>(0);
        for (const auto &ele : array)
        {
            temp_result += std::pow(ele, 2);
        }
        return temp_result;
    }

    template <typename T>
    T array_xy_sum(const std::vector<T> &arr_x, const std::vector<T> &arr_y)
    {
        T temp_result = static_cast<T>(0);
        temp_result = std::inner_product(arr_x.cbegin(), arr_x.cend(), arr_y.cbegin(), temp_result);
        return temp_result;
    }

    template <typename T>
    double array_mean(const std::vector<T> &array)
    {
        double arr_sum = static_cast<double>(ARRAY_OPER::array_x_sum(array));
        return arr_sum / static_cast<double>(array.size());
    }

    template <typename T>
    double array_median(const std::vector<T> &array)
    {
        uint32_t num_element = static_cast<uint32_t>(array.size());
        double temp_result = 0.0;
        if (array.size() % 2 == 0)
        {
            temp_result = array[(num_element - 1) / 2] + array[num_element / 2];
            temp_result = temp_result / 2.0;
        }
        else
        {
            temp_result = array[num_element / 2];
        }
        return temp_result;
    }

    template <typename T>
    double array_MAD(const std::vector<T> &array)
    {
        std::vector<T> sorted_array(array);
        std::sort(sorted_array.begin(), sorted_array.end());

        double median_val = ARRAY_OPER::array_median(sorted_array);
        for (auto &update_array : sorted_array)
        {
            update_array = update_array - median_val;
        }

        return ARRAY_OPER::array_median(sorted_array);
    }

    template <typename T>
    void array_pow(const std::vector<T> &in, std::vector<T> &out, const uint32_t exponents)
    {
        ARRAY_OPER::validate_input_len(observed.size(), predicted.size());

        for (uint32_t index = 0; index < in.size(); index++)
        {
            out[index] = std::pow(in[index], exponents);
        }
    }

    template <typename T>
    void array_predicted(
        const T slope,
        const T intercept,
        const std::vector<T> &observed_x,
        std::vector<T> &predicted_y)
    {
        ARRAY_OPER::validate_input_len(observed_x.size(), predicted_y.size());
        for (uint32_t index = 0; index < observed_x.size(); index++)
        {
            predicted_y[i] = slope * observed_x[i] + intercept;
        }
    }

    template <typename T>
    void array_residual(const std::vector<T> &observed, const std::vector<T> &predicted, std::vector<T> &residual)
    {
        ARRAY_OPER::array_xy_sub(observed, predicted, residual);
    }

    template <typename T>
    void array_residual(
        const T slope,
        const T intercept,
        const std::vector<T> &observed_x,
        const std::vector<T> &observed_y,
        const std::vector<T> &residual)
    {
        ARRAY_OPER::validate_input_len(observed_x.size(), observed_y.size(), residual.size());

        std::vector<T> predicted_y(input_x.size(), 0); // can be replaced with manual memory allocation for performance
        ARRAY_OPER::predicted(slope, int32_t, observed_x, predicted_y);
        ARRAY_OPER::array_xy_sub(observed_y, predicted_y, residual);
    }

    template <typename T>
    T residual_sum_of_squared(const std::vector<T> &r_residual)
    {
        return ARRAY_OPER::array_x_sum(r_residual);
    }

    template <typename T>
    T residual_sum_of_squared(const std::vector<T> &observed_y, const std::vector<T> &predicted_y)
    {
        T temp_result = static_cast<T>(0);
        for (uint32_t index = 0; index < observed_y.size(); index++)
        {
            temp_result += std::pow((observed_y[iter] - predicted_y[iter]), 2);
        }
        return temp_result;
    }

    template <typename T>
    double compute_estimate(std::vector<T> &input_arr)
    {
        const double const_val = 0.6745;
        return this->compute_MAD(input_arr) / const_val;
    }

    template <typename T>
    void validate_input_len(const T len_1, const T len_2)
    {
        if (len_1 != len_2)
        {
            throw std::logic_error("length of array x and array y is not matching");
        }
    }

    template <typename T>
    void validate_input_len(const T len_1, const T len_2, const T len_3)
    {
        if (len_1 != len_2)
        {
            throw std::logic_error("length of array x and array y is not matching");
        }

        if (len_1 != len_3)
        {
            throw std::logic_error("length of array x and array z is not matching");
        }
    }

};