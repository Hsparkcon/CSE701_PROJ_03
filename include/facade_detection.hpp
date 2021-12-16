/**
 * The file contains facade version of outlier detection method.
 * The class FACADE_DETECTION inherits class OUTLIER_DETECTION with is-a relation
*/
#pragma once
#include "outlier_detection.hpp"

enum class DETECTION_METHOD
{
    WEIGHT,
    STANDARDIZED_RESIDUAL
};

DETECTION_METHOD validate_det_method(const std::string &target_method)
{
    std::map<std::string, DETECTION_METHOD> method_list{
        {"weight", DETECTION_METHOD::WEIGHT},
        {"standardized_residual", DETECTION_METHOD::STANDARDIZED_RESIDUAL}};

    auto iter_method_list = method_list.find(target_method);

    if (iter_method_list == method_list.end())
    {
        /*
            Throw error
        */
    }

    return iter_method_list->second;
}

class FACADE_DETECTION : public OUTLIER_DETECTION
{
public:
    FACADE_DETECTION() {}

    FACADE_DETECTION(
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        const double m_slope,
        const double b_intercept)
    {
        validate_input_length(
            static_cast<uint32_t>(x_observed.size()),
            static_cast<uint32_t>(y_observed.size()));

        this->m_x_observed = x_observed;
        this->m_y_observed = y_observed;
        this->m_m_slope = m_slope;
        this->m_b_intercept = b_intercept;
        this->ready_standardized_detection = true;
        this->ready_weight_detection = false;

        uint32_t num_data = static_cast<uint32_t>(x_observed.size());
        uint32_t num_expected_outlier = static_cast<uint32_t>(num_data * 0.25);
        uint32_t num_expected_inlier = static_cast<uint32_t>(num_data * 0.75);
        m_x_outliers.reserve(num_expected_outlier);
        m_y_outliers.reserve(num_expected_outlier);
        m_x_inliers.reserve(num_expected_inlier);
        m_y_inliers.reserve(num_expected_inlier);
    }

    FACADE_DETECTION(
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        const std::vector<double> &w_weight)
    {
        validate_input_length(
            static_cast<uint32_t>(x_observed.size()),
            static_cast<uint32_t>(y_observed.size()),
            static_cast<uint32_t>(w_weight.size()));
        this->m_x_observed = x_observed;
        this->m_y_observed = y_observed;
        this->m_w_weight = w_weight;
        this->ready_standardized_detection = false;
        this->ready_weight_detection = true;

        uint32_t num_data = static_cast<uint32_t>(x_observed.size());
        uint32_t num_expected_outlier = static_cast<uint32_t>(num_data * 0.25);
        uint32_t num_expected_inlier = static_cast<uint32_t>(num_data * 0.75);
        m_x_outliers.reserve(num_expected_outlier);
        m_y_outliers.reserve(num_expected_outlier);
        m_x_inliers.reserve(num_expected_inlier);
        m_y_inliers.reserve(num_expected_inlier);
    }

    FACADE_DETECTION(
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        const std::vector<double> &w_weight,
        const double m_slope,
        const double b_intercept)
    {
        validate_input_length(
            static_cast<uint32_t>(x_observed.size()),
            static_cast<uint32_t>(y_observed.size()),
            static_cast<uint32_t>(w_weight.size()));
        this->m_x_observed = x_observed;
        this->m_y_observed = y_observed;
        this->m_w_weight = w_weight;
        this->m_m_slope = m_slope;
        this->m_b_intercept = b_intercept;
        this->ready_standardized_detection = true;
        this->ready_weight_detection = true;

        uint32_t num_data = static_cast<uint32_t>(x_observed.size());
        uint32_t num_expected_outlier = static_cast<uint32_t>(num_data * 0.25);
        uint32_t num_expected_inlier = static_cast<uint32_t>(num_data * 0.75);
        m_x_outliers.reserve(num_expected_outlier);
        m_y_outliers.reserve(num_expected_outlier);
        m_x_inliers.reserve(num_expected_inlier);
        m_y_inliers.reserve(num_expected_inlier);
    }

    ~FACADE_DETECTION() {}

    void detect_by_std_residual()
    {
        if (ready_standardized_detection == false)
        {
            /*
                Throw logic error
            */
        }
        OUTLIER_DETECTION::detection_by_standardized_residual(
            m_x_observed,
            m_y_observed,
            m_m_slope,
            m_b_intercept,
            m_num_outliers,
            m_x_outliers,
            m_y_outliers,
            m_x_inliers,
            m_y_inliers);
    }

    void detect_by_weight()
    {
        if (ready_weight_detection == false)
        {
            /*
                Throw logic error
            */
        }
        OUTLIER_DETECTION::detection_by_weight(
            m_x_observed,
            m_y_observed,
            m_w_weight,
            m_num_outliers,
            m_x_outliers,
            m_y_outliers,
            m_x_inliers,
            m_y_inliers);
    }

    void proceed_detection(DETECTION_METHOD target_method)
    {
        switch (target_method)
        {
        case DETECTION_METHOD::STANDARDIZED_RESIDUAL:
            this->detect_by_std_residual();
            break;

        case DETECTION_METHOD::WEIGHT:
            this->detect_by_weight();
            break;

        default:
            break;
        }
    }

    uint32_t get_num_outlier() const
    {
        return this->m_num_outliers;
    }

    void get_outliers(std::vector<double> &x_outliers, std::vector<double> &y_outliers)
    {
        x_outliers = this->m_x_outliers;
        y_outliers = this->m_y_outliers;
    }

    void get_inliers(std::vector<double> &x_inliers, std::vector<double> &y_inliers)
    {
        x_inliers = this->m_x_inliers;
        y_inliers = this->m_y_inliers;
    }

private:
    void validate_input_length(uint32_t length_one, uint32_t length_two, uint32_t length_three = 0)
    {
        if (length_one != length_two)
        {
            /*
                throw parameter error
            */
        }

        if ((length_three != 0) && (length_one != length_three))
        {
            /*
                throw parameter error
            */
        }
    }

    bool ready_weight_detection = false;
    bool ready_standardized_detection = false;
    uint32_t m_num_outliers = 0;
    std::vector<double> m_x_observed;
    std::vector<double> m_y_observed;
    std::vector<double> m_w_weight;
    double m_m_slope;
    double m_b_intercept;
    std::vector<double> m_x_outliers;
    std::vector<double> m_y_outliers;
    std::vector<double> m_x_inliers;
    std::vector<double> m_y_inliers;
};