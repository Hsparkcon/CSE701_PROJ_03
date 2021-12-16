#pragma once
#include "PCH.hpp"

class OUTLIER_DETECTION
{
public:
    OUTLIER_DETECTION() {}
    ~OUTLIER_DETECTION() {}

    void detection_by_standardized_residual(
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        const double m_slope,
        const double b_intercept,
        uint32_t &num_detectded_outlier,
        std::vector<double> &x_outlier,
        std::vector<double> &y_outlier,
        std::vector<double> &x_inlier,
        std::vector<double> &y_inlier)
    {
        uint32_t num_elements = static_cast<uint32_t>(x_observed.size());
        std::vector<double> standardized_residual(num_elements, 0);
        compute_standardized_residual(x_observed, y_observed, m_slope, b_intercept, standardized_residual);

        for (uint32_t iter = 0; iter < num_elements; iter++)
        {
            if (standardized_residual[iter] > 2)
            {
                x_outlier.push_back(x_observed[iter]);
                y_outlier.push_back(y_observed[iter]);
            }
            else
            {
                x_inlier.push_back(x_observed[iter]);
                y_inlier.push_back(y_observed[iter]);
            }
        }
        x_outlier.shrink_to_fit();
        y_outlier.shrink_to_fit();
        x_inlier.shrink_to_fit();
        y_inlier.shrink_to_fit();
        num_detectded_outlier = static_cast<uint32_t>(x_outlier.size());
    }

    void detection_by_weight(
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        const std::vector<double> &w_weight,
        uint32_t &num_detectded_outlier,
        std::vector<double> &x_outlier,
        std::vector<double> &y_outlier,
        std::vector<double> &x_inlier,
        std::vector<double> &y_inlier)
    {
        for (uint32_t iter = 0; iter < w_weight.size(); iter++)
        {
            if (w_weight[iter] < 1)
            {
                x_outlier.push_back(x_observed[iter]);
                y_outlier.push_back(y_observed[iter]);
            }
            else
            {
                x_inlier.push_back(x_observed[iter]);
                y_inlier.push_back(y_observed[iter]);
            }
        }
        x_outlier.shrink_to_fit();
        y_outlier.shrink_to_fit();
        x_inlier.shrink_to_fit();
        y_inlier.shrink_to_fit();
        num_detectded_outlier = static_cast<uint32_t>(x_outlier.size());
    }

private:
    const double weight_tolerance = 1E-06;

    double compute_RMSE(
        const std::vector<double> &r_residual,
        const uint32_t num_parameter)
    {
        double temp_result = 0.0;
        for (const auto &residual : r_residual)
        {
            temp_result += std::pow(residual, 2);
        }
        temp_result = temp_result / (static_cast<double>(r_residual.size()) - num_parameter);
        temp_result = std::sqrt(temp_result);
        return temp_result;
    }

    void compute_raw_residual(
        const double m_slope,
        const double b_intercept,
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        std::vector<double> &ouput_residual)
    {
        uint32_t num_element = static_cast<uint32_t>(x_observed.size());
        std::vector<double> predicted_val(num_element, 0);
        for (uint32_t i = 0; i < num_element; i++)
        {
            predicted_val[i] = m_slope * x_observed[i] + b_intercept;
        }

        for (uint32_t i = 0; i < num_element; i++)
        {
            ouput_residual[i] = y_observed[i] - predicted_val[i];
        }
    }

    void compute_leverage(
        const std::vector<double> &x_observed,
        std::vector<double> h_leverage)
    {
        uint32_t num_elements = static_cast<uint32_t>(x_observed.size());

        double x_mean = 0.0;
        x_mean = std::accumulate(x_observed.cbegin(), x_observed.cend(), 0.0);
        x_mean = x_mean / num_elements;

        double xx_sum = 0.0;
        for (const auto x_ele : x_observed)
        {
            xx_sum += std::pow(x_ele, 2);
        }

        for (uint32_t iter = 0; iter < num_elements; iter++)
        {
            h_leverage[iter] = 1.0 / static_cast<double>(x_observed.size()) + (std::pow((x_observed[iter] - x_mean), 2) / xx_sum);
        }
    }

    void compute_standardized_residual(
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        const double m_slope,
        const double b_intercept,
        std::vector<double> &standardized_residual)
    {
        uint32_t num_elements = static_cast<uint32_t>(x_observed.size());

        std::vector<double> raw_residuals(num_elements, 0);
        this->compute_raw_residual(m_slope, b_intercept, x_observed, y_observed, raw_residuals);

        std::vector<double> h_leverage(num_elements, 0);
        this->compute_leverage(x_observed, h_leverage);

        double rmse = this->compute_RMSE(raw_residuals, 2);

        for (uint32_t iter = 0; iter < num_elements; iter++)
        {
            standardized_residual[iter] =
                raw_residuals[iter] / std::sqrt(rmse * (1 - h_leverage[iter]));
        }
    }
};