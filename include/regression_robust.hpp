#pragma once
#include "regression_basic.hpp"

/**
 * @brief
 * REGRESSION_ROBUST class is a collection of member function and variables used in the project.
 * REGRESSION_ROBUST class especially uses M-estimator for robust regression computation.
 * REGRESSION_ROBUST class member function "compute_weight()" is declared as pure weight function
 * that must be implemented at a derived class.
 */
class REGRESSION_ROBUST : public REGRESSION_BASIC
{
public:
    REGRESSION_ROBUST() {}

    /**
     * @brief
     * Construct a new REGRESSION_ROBUST object and initializes member variables including
     * size vectors that will be used during computation.
     *
     * @param[in] x_observed A collection of observed data's independent variables (X-Axis).
     * @param[in] y_observed A collection of observed data's dependent variables (Y-Axis).
     */
    REGRESSION_ROBUST(const std::vector<double> &x_observed, const std::vector<double> &y_observed)
        : m_x_observed(x_observed), m_y_observed(y_observed), m_num_data_points(static_cast<uint32_t>(x_observed.size()))
    {
        this->m_y_predicted = std::vector<double>(this->m_num_data_points, 0);
        this->m_r_residual = std::vector<double>(this->m_num_data_points, 0);
        this->m_h_leverage = std::vector<double>(this->m_num_data_points, 0);
        this->m_w_weight = std::vector<double>(this->m_num_data_points, 0);
        this->m_slope = 0;
        this->m_intercept = 0;
        this->m_num_iteration = 0;
    }

    virtual ~REGRESSION_ROBUST() {}

    /**
     * @brief Gets the approximate slope of the line of best fit.
     *
     * @return double
     */
    double get_slope() const
    {
        return this->m_slope;
    }

    /**
     * @brief Gets the approximate intercept of the line of best fit.
     *
     * @return double
     */
    double get_intercept() const
    {
        return this->m_intercept;
    }

    /**
     * @brief Gets the weight of observed data point computed during the robust regression process.
     *
     * @param[out] w_weight A collection of observed data's weight.
     */
    void get_weight(std::vector<double> &weight_retrived)
    {
        weight_retrived = this->m_w_weight;
    }

    /**
     * @brief Gets the number of iteration to complete the robust regression computation.
     *
     * @return double
     */
    uint32_t get_num_iteration() const
    {
        return this->m_num_iteration;
    }

    /**
     * @brief Proceed regression with the given data.
     *
     */
    void perform_regression()
    {
        double init_slope = 0;
        double init_intercept = 0;
        REGRESSION_BASIC::ols_regression(m_x_observed, m_y_observed, m_slope, m_intercept);
        REGRESSION_BASIC::compute_predict(init_slope, init_intercept, m_x_observed, m_y_predicted);
        this->init_weight(m_y_observed, m_y_predicted, m_w_weight);

        double x_mean = REGRESSION_BASIC::compute_MEAN(m_x_observed);
        double xx_sum = REGRESSION_BASIC::compute_xx_sum(m_x_observed);
        this->compute_leverage(x_mean, xx_sum, m_x_observed, m_h_leverage);

        double temp_m_slope = 0;
        double temp_b_intercept = 0;
        uint32_t num_iteration = 0;
        double residual_sum = REGRESSION_BASIC::residual_sum_of_squared(m_y_observed, m_y_predicted);
        while (residual_sum > residual_tolerance && num_iteration < iteration_limit)
        {
            double weight_sum = REGRESSION_BASIC::compute_arr_sum(m_w_weight);
            double x_weight = REGRESSION_BASIC::compute_xy_sum(m_w_weight, m_x_observed) / weight_sum;
            double y_weight = REGRESSION_BASIC::compute_xy_sum(m_w_weight, m_y_observed) / weight_sum;
            double temp_wxy = 0;
            double temp_wxx = 0;
            for (uint32_t iter = 0; iter < m_num_data_points; iter++)
            {
                temp_wxy += (m_w_weight[iter] * (m_x_observed[iter] - x_weight) * (m_y_observed[iter] - y_weight));
                temp_wxx += (m_w_weight[iter] * std::pow((m_x_observed[iter] - x_weight), 2));
            }
            temp_m_slope = temp_wxy / temp_wxx;
            temp_b_intercept = y_weight - (temp_m_slope * x_weight);

            REGRESSION_BASIC::compute_predict(temp_m_slope, temp_b_intercept, m_x_observed, m_y_predicted);
            REGRESSION_BASIC::compute_residual(m_y_observed, m_y_predicted, m_r_residual);

            double val_MAD = REGRESSION_BASIC::compute_MAD(m_r_residual);

            compute_weight(m_r_residual, m_h_leverage, val_MAD, m_w_weight);

            residual_sum = std::abs(REGRESSION_BASIC::compute_xy_sum(m_r_residual, m_w_weight));
            num_iteration++;
        }

        this->m_slope = temp_m_slope;
        this->m_intercept = temp_b_intercept;
        this->m_num_iteration = num_iteration;
    }

protected:
    virtual void compute_weight(
        const std::vector<double> &residual,
        const std::vector<double> &leverage,
        const double val_MAD,
        std::vector<double> &weight) = 0;

private:
    const double residual_tolerance = 1E-08;
    const uint32_t iteration_limit = 1000;

    std::vector<double> m_x_observed;
    std::vector<double> m_y_observed;
    std::vector<double> m_y_predicted;
    std::vector<double> m_r_residual;
    std::vector<double> m_h_leverage;
    std::vector<double> m_w_weight;

    uint32_t m_num_data_points;
    uint32_t m_num_iteration;
    double m_slope;
    double m_intercept;

    /**
     * @brief Initializes weight of observed data.
     *
     * @param[in] y_observed A collection of observed data's dependent variables (Y-Axis).
     * @param[in] y_predicted A collection of predicted dependent variables (Y-Axis).
     * @param[out] w_weight A collection of initialized weights.
     */
    void init_weight(
        const std::vector<double> &y_observed,
        const std::vector<double> &y_predicted,
        std::vector<double> &w_weight)
    {
        for (uint32_t iter = 0; iter < w_weight.size(); iter++)
        {
            w_weight[iter] = 1.0 / std::pow((y_observed[iter] - y_predicted[iter]), 2);
        }
    }

    /**
     * @brief Computes leverage of observed data.
     * 
     * @param[in] x_mean A average of observed data's independent variables (X-Axis).
     * @param[in] xx_sum A sum of pow(observed data's X-Axis, 2).
     * @param[in] x_observed A collection of observed data's independent variables (X-Axis).
     * @param[out] h_leverage A collection of observed data's leverage
     */
    void compute_leverage(
        const double x_mean,
        const double xx_sum,
        const std::vector<double> &x_observed,
        std::vector<double> h_leverage)
    {
        for (uint32_t iter = 0; iter < h_leverage.size(); iter++)
        {
            h_leverage[iter] = 1.0 / static_cast<double>(x_observed.size()) + (std::pow((x_observed[iter] - x_mean), 2) / xx_sum);
        }
    }
};