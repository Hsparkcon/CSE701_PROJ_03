#pragma once
#include "regression_robust.hpp"

/**
 * @brief
 * M_ESTIMATOR_LOGISTIC class implements weight function (pure virtual) of REGRESSION_ROBUST with Andrew M-Estimator.
 * M_ESTIMATOR_LOGISTIC class contains tunning constant for Andrew M-Estimator.
 *
 */
class M_ESTIMATOR_ANDREWS : public REGRESSION_ROBUST
{
public:
    /**
     * @brief Constructs ROBUST_REGRESSION object with weight function driven from Andrew M-Estimator.
     *
     * @param x_observed  A collection of observed data's independent variables (X-Axis).
     * @param y_observed  A collection of observed data's dependent variables (Y-Axis).
     * @param custom_tunning Tunning constant, by default predefined value will be used.
     */
    M_ESTIMATOR_ANDREWS(
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        double custom_tunning = 0)
        : REGRESSION_ROBUST(x_observed, y_observed)
    {
        this->tunning_constant = (custom_tunning == 0) ? default_tunning_constant : custom_tunning;
    }

    ~M_ESTIMATOR_ANDREWS() {}

private:
    double tunning_constant = 1;
    const double default_tunning_constant = 1.339;

    /**
     * @brief Computes weight of observed data points.
     *
     * @param[in] residual A collection of raw residual, the difference between observed and predicted.
     * @param[in] leverage A leverage value collection.
     * @param[in] val_MAD A value of median absolute deviation.
     * @param[out] weight A collection of weight of observed data computed.
     */
    void compute_weight(
        const std::vector<double> &residual,
        const std::vector<double> &leverage,
        const double val_MAD,
        std::vector<double> &weight)
    {
        // s = estimate of the standard deviation of the error term = val_MAD / 0.6745
        double const_val = tunning_constant * val_MAD / 0.6745;
        std::vector<double> r_standardized(residual.size(), 0);
        for (uint32_t i = 0; i < residual.size(); i++)
        {
            r_standardized[i] = residual[i] / (const_val * std::sqrt(1.0 - leverage[i]));
        }

        for (uint32_t i = 0; i < residual.size(); i++)
        {
            weight[i] = (std::abs(r_standardized[i]) < std::numbers::pi) ? std::sin(r_standardized[i]) / r_standardized[i] : 0;
        }
    }
};