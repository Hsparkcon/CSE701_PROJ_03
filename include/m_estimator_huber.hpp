#pragma once
#include "regression_robust.hpp"

class M_ESTIMATOR_HUBER : public REGRESSION_ROBUST
{
public:
    M_ESTIMATOR_HUBER(
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        double custom_tunning = 0)
        : REGRESSION_ROBUST(x_observed, y_observed)
    {
        this->tunning_constant = (custom_tunning == 0) ? default_tunning_constant : custom_tunning;
    }

    ~M_ESTIMATOR_HUBER() {}

private:
    double tunning_constant = 1;
    const double default_tunning_constant = 1.345;

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
            weight[i] = 1.0 / std::max(1.0, std::abs(r_standardized[i]));
        }
    }
};