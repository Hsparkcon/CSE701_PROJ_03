#pragma once
#include "PCH.hpp"

/**
 * @brief
 * OUTLIER_DETECTION class is a collection of member functions and variables
 * designed to differentiate outliers and inliers in the given data
 * (a collection of independent and dependent data of a linear system).
 *
 * @details
 * In CSE701_PROJ03, outlier detection is done by using
 * computation results of the ROBUST_REGRESSION class.
 *
 * OUTLIER_DETECTION class uses parameters of the line of best fit from
 * the ROBUST_REGRESSION class to compute one type of residuals to distinguish
 * outliers and inliers in the data.
 * Currently, the standardized residual is supported to indicate the data as
 * the standardized residual is a standard method for outlier detection in the field of statics.
 *
 * OUTLIER_DETECTION class uses a collection of weight data computed from
 * the ROBUST_REGRESSION class to distinguish outliers and inliers in the data.
 * Currently, the use of weight data is stopped due to not standardized results.
 *
 */
class OUTLIER_DETECTION
{
public:
    /**
     * @brief The default constructor for OUTLIER_DETECTION class, nothing to initialize.
     *
     */
    OUTLIER_DETECTION() {}

    /**
     * @brief The default destructor for OUTLIER_DETECTION class, no special action required.
     *
     */
    ~OUTLIER_DETECTION() {}

    /**
     * @brief
     * The function distinguishes inliers and outliers in the given data by using standardized residuals.
     * @details
     * The function follows a conservative way that it defines the data points as outliers
     * when the standardized residual is bigger than 2.
     * If the function follows a non-conservative way, the data point would be defined as outliers
     * when the standardized residual is bigger than 3.
     *
     * @param[in] x_observed A collection of observed data's independent variables (X-Axis).
     * @param[in] y_observed A collection of observed data's dependent variables (Y-Axis).
     * @param[in] m_slope A slope of line of best fit computed from linear regression method.
     * @param[in] b_intercept A intercept of line of best fit computed from linear regression method.
     * @param[out] num_detectded_outlier A number of outliers detected.
     * @param[out] x_outlier A collection of outliers in observed data's independent variables (X-Axis).
     * @param[out] y_outlier A collection of outliers in observed data's independent variables (Y-Axis).
     * @param[out] x_inlier A collection of inliers in observed data's independent variables (X-Axis).
     * @param[out] y_inlier A collection of inliers in observed data's dependent variables (Y-Axis).
     */
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
        validate_vector_length_match(x_observed, y_observed);

        uint32_t num_elements = static_cast<uint32_t>(x_observed.size());
        std::vector<double> standardized_residual(num_elements, 0);
        compute_standardized_residual(m_slope, b_intercept, x_observed, y_observed, standardized_residual);

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
        num_detectded_outlier = static_cast<uint32_t>(x_outlier.size());
    }

    /**
     * @brief The function computes standardized residual.
     *
     * @param[in] m_slope A slope of line of best fit computed from linear regression method.
     * @param[in] b_intercept A intercept of line of best fit computed from linear regression method.
     * @param[in] x_observed A collection of observed data's independent variables (X-Axis).
     * @param[in] y_observed A collection of observed data's dependent variables (Y-Axis).
     * @param[out] standardized_residual A collection of standardized residuals.
     */
    void compute_standardized_residual(
        const double m_slope,
        const double b_intercept,
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        std::vector<double> &standardized_residual)
    {
        validate_vector_length_match(x_observed, y_observed);
        validate_vector_length_match(x_observed, standardized_residual);

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

    /**
     * @brief
     * The function distinguishes inliers and outliers in the given data by using weight of data points.
     * @details
     * The function differentiates inliers and outliers using weight
     * computed during robust regression computation.
     * However, the non-standard method defines a data point as an outlier
     * when the point's weight is small enough to be not affective in regression computation.
     * The method was implemented to compare the result with outlier detection by standardized residual;
     * therefore, the function is not suggested.
     *
     * @param[in] x_observed A collection of observed data's independent variables (X-Axis).
     * @param[in] y_observed A collection of observed data's dependent variables (Y-Axis).
     * @param[in] w_weight A collection of weight of each variables in observed data.
     * @param[out] num_detectded_outlier A number of outliers detected.
     * @param[out] x_outlier A collection of outliers in observed data's independent variables (X-Axis).
     * @param[out] y_outlier A collection of outliers in observed data's independent variables (Y-Axis).
     * @param[out] x_inlier A collection of inliers in observed data's independent variables (X-Axis).
     * @param[out] y_inlier A collection of inliers in observed data's dependent variables (Y-Axis).
     */
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
        validate_vector_length_match(x_observed, y_observed);
        validate_vector_length_match(x_observed, w_weight);

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
        num_detectded_outlier = static_cast<uint32_t>(x_outlier.size());
    }

private:
    const double weight_tolerance = 1E-06;

    /**
     * @brief The function computes Root-mean-square deviation (RMSE)
     *
     * @param[in] r_residual The raw residual between observed data's dependent variables and predicted data (y = m*observed_independent_variable + b)
     * @param[in] num_parameter The number of parameters in observed data's independnet variables. In CSE701_PROJ_03, it is assumed to be 2.
     * @return double
     */
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

    /**
     * @brief The function computes raw-residual between observed data's dependent variables and predicted data (y = m*observed_independent_variable + b)
     *
     * @param[in] m_slope A slope of line of best fit computed from linear regression method.
     * @param[in] b_intercept A intercept of line of best fit computed from linear regression method.
     * @param[in] x_observed A collection of observed data's independent variables (X-Axis).
     * @param[in] y_observed A collection of observed data's dependent variables (Y-Axis).
     * @param[out] raw_residual A raw residual collection
     */
    void compute_raw_residual(
        const double m_slope,
        const double b_intercept,
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        std::vector<double> &raw_residual)
    {
        validate_vector_length_match(x_observed, y_observed);
        validate_vector_length_match(x_observed, raw_residual);

        uint32_t num_element = static_cast<uint32_t>(x_observed.size());
        std::vector<double> predicted_val(num_element, 0);
        for (uint32_t i = 0; i < num_element; i++)
        {
            predicted_val[i] = m_slope * x_observed[i] + b_intercept;
        }

        for (uint32_t i = 0; i < num_element; i++)
        {
            raw_residual[i] = y_observed[i] - predicted_val[i];
        }
    }

    /**
     * @brief The function computes leverage values of observed data's independent variables (X-Axis).
     *
     * @param[in] x_observed A collection of observed data's independent variables (X-Axis).
     * @param[out] h_leverage A leverage value collection.
     */
    void compute_leverage(
        const std::vector<double> &x_observed,
        std::vector<double> h_leverage)
    {
        validate_vector_length_match(x_observed, h_leverage);

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

    /**
     * @brief
     * The function validates the number of given data collections matches each other and
     * throws runtime error if there is a mismatch.
     *
     * @param vec_one collection of independent variables
     * @param vec_two collection of independent variables
     */
    void validate_vector_length_match(const std::vector<double> &vec_one, const std::vector<double> &vec_two)
    {
        if (vec_one.size() != vec_two.size())
        {
            std::string error_message =
                "OUTLIER DETECTION ERROR - VECTOR LENGTH MISMATCH\n"
                "Number of elements in given vector must be matched, but\n"
                "VECTOR ONE: " + std::to_string(vec_one.size()) + "\n"
                "VECTOR TWO: " + std::to_string(vec_two.size()) + "\n";
            throw std::runtime_error(error_message);
        }
    }
};