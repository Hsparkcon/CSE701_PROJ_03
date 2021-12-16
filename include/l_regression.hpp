/**
 * The file contains least square regression methods with array operations for the project.
 * The L_REGRESSION class will be seperated into ARRAY_OPERATION and OLS_REGRESSION classes
*/
#pragma once
#include "PCH.hpp"

class L_REGRESSION
{
public:
    L_REGRESSION() {}
    ~L_REGRESSION() {}

    void ols_regression(
        const std::vector<double> &arr_x,
        const std::vector<double> &arr_y,
        double &m_slope, double &b_intercept)
    {

        uint32_t num_points = static_cast<uint32_t>(arr_x.size());
        double x_sum = this->compute_arr_sum(arr_x);
        double y_sum = this->compute_arr_sum(arr_y);
        double xx_xum = this->compute_xx_sum(arr_x);
        double xy_sum = this->compute_xy_sum(arr_x, arr_y);

        m_slope = (num_points * xy_sum - x_sum * y_sum) / (num_points * xx_xum - std::pow(x_sum, 2));
        b_intercept = (y_sum - m_slope * x_sum) / num_points;
    }

    void compute_predict(
        const double m_slope,
        const double b_intercept,
        const std::vector<double> &x_observed,
        std::vector<double> &y_predicted)
    {
        for (uint32_t iter = 0; iter < y_predicted.size(); iter++)
        {
            y_predicted[iter] = (m_slope * x_observed[iter]) + b_intercept;
        }
    }

    double compute_arr_sum(const std::vector<double> &arr)
    {
        double sum_array = std::accumulate(arr.cbegin(), arr.cend(), 0.0);
        return sum_array;
    }

    double compute_xx_sum(const std::vector<double> &arr)
    {
        double temp_sum = 0.0;
        for (uint32_t i = 0; i < arr.size(); i++)
        {
            temp_sum += std::pow(arr[i], 2);
        }
        return temp_sum;
    }

    double compute_xy_sum(const std::vector<double> &arr_x, const std::vector<double> &arr_y)
    {
        double sum_array = std::inner_product(arr_x.cbegin(), arr_x.cend(), arr_y.cbegin(), 0.0);
        return sum_array;
    }

    double compute_MEAN(const std::vector<double> &input_arr)
    {
        double sum_array = std::accumulate(input_arr.cbegin(), input_arr.cend(), 0);
        return sum_array / static_cast<double>(input_arr.size());
    }

    double compute_MEDIAN(const std::vector<double> &input_arr)
    {
        uint32_t num_elements = static_cast<uint32_t>(static_cast<uint32_t>(input_arr.size()));
        double result = 0.0;
        if (input_arr.size() % 2 == 0)
        {
            result = (input_arr[(num_elements - 1) / 2] + input_arr[num_elements / 2]) / 2.0;
        }
        else
        {
            result = input_arr[num_elements / 2];
        }
        return result;
    }

    double compute_MAD(const std::vector<double> &input_arr)
    {

        std::vector<double> sorted_arr(input_arr);
        std::sort(sorted_arr.begin(), sorted_arr.end());

        double median_val = this->compute_MEDIAN(sorted_arr);

        for (auto update_arr : sorted_arr)
        {
            update_arr = update_arr - median_val;
        }

        return this->compute_MEDIAN(sorted_arr);
    }

    double compute_estimate(std::vector<double> &input_arr)
    {
        const double const_val = 0.6745;
        return this->compute_MAD(input_arr) / const_val;
    }

    void compute_residual(double m_slope, double b_intercept, std::vector<double> &input_x, std::vector<double> &input_y, std::vector<double> &ouput_residual)
    {
        std::vector<double> predicted_val(input_x.size(), 0); // can be replaced with manual memory allocation for performance
        for (uint32_t i = 0; i < input_x.size(); i++)
        {
            predicted_val[i] = m_slope * input_x[i] + b_intercept;
        }

        for (uint32_t i = 0; i < input_x.size(); i++)
        {
            ouput_residual[i] = input_y[i] - predicted_val[i];
        }
    }

    void compute_residual(const std::vector<double> &y_observed, const std::vector<double> &y_predicted, std::vector<double> &residual)
    {
        for (uint32_t i = 0; i < y_predicted.size(); i++)
        {
            residual[i] = y_observed[i] - y_predicted[i];
        }
    }

    double residual_sum_of_squared(std::vector<double> &r_residual)
    {
        return compute_xx_sum(r_residual);
    }

    double residual_sum_of_squared(std::vector<double> &y_observed, std::vector<double> &y_predicted)
    {
        double result = 0;
        for (uint32_t iter = 0; iter < y_observed.size(); iter++)
        {
            result += std::pow((y_observed[iter] - y_predicted[iter]), 2);
        }
        return result;
    }

    double residual_sum_L1_norm(std::vector<double> &y_observed, std::vector<double> &y_predicted)
    {
        double result = 0;
        for (uint32_t iter = 0; iter < y_observed.size(); iter++)
        {
            result += std::abs(y_observed[iter] - y_predicted[iter]);
        }
        return result;
    }

protected:
    double weight_threshold = 1e-06;
    uint32_t iteration_limit = 500;

private:
};