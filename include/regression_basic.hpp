#pragma once
#include "PCH.hpp"

/**
 * @brief
 * REGRESSION_BASIC class is a collection of member functions and variables
 * that are generally used in linear regression computation.
 * REGRESSION_BASIC class is designed to minimize duplicated function and variables.
 * REGRESSION_BASIC class can be templatized in future to handle different number type data.
 *
 */
class REGRESSION_BASIC
{
public:
    /**
     * @brief Default constructor, no initialization is required.
     *
     */
    REGRESSION_BASIC() {}

    /**
     * @brief Default constructor, no special action is required.
     *
     */
    ~REGRESSION_BASIC() {}

    /**
     * @brief Performs Ordinary Least Square regression and returns approximated parameters of line of best fit.
     *
     * @param[in] arr_x A collection of observed data's X-Coordinate.
     * @param[in] arr_y A collection of observed data's Y-Coordinate.
     * @param[out] m_slope An approximated slope of linear system.
     * @param[out] b_intercept An approximated intercept of linear system.
     */
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

    /**
     * @brief Computes predicted data (Y-Axis) of linear system based on
     * - approximated slope
     * - approximated intercept
     * - observed X-axis coordinate.
     *
     * @param[in] m_slope An approximated slope of linear system.
     * @param[in] b_intercept An approximated intercept of linear system.
     * @param[in] x_observed A collection of observed data's X-Coordinate.
     * @param[out] y_predicted A collection of predicted data of linear system.
     */
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

    /**
     * @brief Computes sum of elements in the given array.
     *
     * @param[in] arr A collection of number elements
     * @return double
     */
    double compute_arr_sum(const std::vector<double> &arr)
    {
        double sum_array = std::accumulate(arr.cbegin(), arr.cend(), 0.0);
        return sum_array;
    }

    /**
     * @brief Computes sum of pow(element, 2) in the given array.
     *
     * @param[in] arr A collection of number elements
     * @return double
     */
    double compute_xx_sum(const std::vector<double> &arr)
    {
        double temp_sum = 0.0;
        for (uint32_t i = 0; i < arr.size(); i++)
        {
            temp_sum += std::pow(arr[i], 2);
        }
        return temp_sum;
    }

    /**
     * @brief Computes inner product of two arrays
     *
     * @param[in] arr_x Input array one
     * @param[in] arr_y Input array two
     * @return double
     */
    double compute_xy_sum(const std::vector<double> &arr_x, const std::vector<double> &arr_y)
    {
        double sum_array = std::inner_product(arr_x.cbegin(), arr_x.cend(), arr_y.cbegin(), 0.0);
        return sum_array;
    }

    /**
     * @brief Computes average of elements in the given array.
     *
     * @param[in] input_arr A collection of number elements
     * @return double
     */
    double compute_MEAN(const std::vector<double> &input_arr)
    {
        double sum_array = std::accumulate(input_arr.cbegin(), input_arr.cend(), 0);
        return sum_array / static_cast<double>(input_arr.size());
    }

    /**
     * @brief Computes the median value of the input array
     *
     * @param[in] input_arr A collection of sorted number elements
     * @return double
     */
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

    /**
     * @brief Computes the median absolute deviation value of array.
     *
     * @param[in] input_arr A collection of number elements
     * @return double
     */
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

    /**
     * @brief Computes the raw residual based on
     * - Approximated slope of linear system
     * - Approximated slope of intercept system
     * - Observed data's x-coordinate data
     * - Observed data's y-coordinate data
     *
     * @param[in] m_slope An approximated slope of linear system.
     * @param[in] b_intercept An approximated intercept of linear system.
     * @param[in] observed_x A collection of observed data's X-Coordinate.
     * @param[in] observed_y A collection of observed data's Y-Coordinate.
     * @param[out] residual A collection of raw residual.
     */
    void compute_residual(double m_slope, double b_intercept, std::vector<double> &observed_x, std::vector<double> &observed_y, std::vector<double> &residual)
    {
        std::vector<double> predicted_val(observed_x.size(), 0); // can be replaced with manual memory allocation for performance
        for (uint32_t i = 0; i < observed_x.size(); i++)
        {
            predicted_val[i] = m_slope * observed_x[i] + b_intercept;
        }

        for (uint32_t i = 0; i < observed_x.size(); i++)
        {
            residual[i] = observed_y[i] - predicted_val[i];
        }
    }

    /**
     * @brief Computes the raw residual based on
     * - Observed data's y-coordinate data
     * - Predicted data
     *
     * @param[in] y_observed A collection of observed data's Y-Coordinate.
     * @param[in] y_predicted A collection of predicted data.
     * @param[out] residual A collection of raw residual.
     */
    void compute_residual(const std::vector<double> &y_observed, const std::vector<double> &y_predicted, std::vector<double> &residual)
    {
        for (uint32_t i = 0; i < y_predicted.size(); i++)
        {
            residual[i] = y_observed[i] - y_predicted[i];
        }
    }

    /**
     * @brief Computes the sum of squared residual
     *
     * @param[in] r_residual A collection of residual data
     * @return double
     */
    double residual_sum_of_squared(std::vector<double> &r_residual)
    {
        return compute_xx_sum(r_residual);
    }

    /**
     * @brief Computes the sum of squared residual
     *
     * @param[in] y_observed A collection of observed data's Y-Coordinate.
     * @param[in] y_predicted A collection of predicted data.
     * @return double
     */
    double residual_sum_of_squared(std::vector<double> &y_observed, std::vector<double> &y_predicted)
    {
        double result = 0;
        for (uint32_t iter = 0; iter < y_observed.size(); iter++)
        {
            result += std::pow((y_observed[iter] - y_predicted[iter]), 2);
        }
        return result;
    }

    /**
     * @brief Computes the sum of L1 norm
     *
     * @param[in] y_observed A collection of observed data's Y-Coordinate.
     * @param[in] y_predicted A collection of predicted data.
     * @return double
     */
    double residual_sum_L1_norm(std::vector<double> &y_observed, std::vector<double> &y_predicted)
    {
        double result = 0;
        for (uint32_t iter = 0; iter < y_observed.size(); iter++)
        {
            result += std::abs(y_observed[iter] - y_predicted[iter]);
        }
        return result;
    }
};