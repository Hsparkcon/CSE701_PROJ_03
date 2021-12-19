/**
 * The file contains facade version of outlier detection method.
 * The class FACADE_REGRESSION inherits class REGRESSION_ROBUST and its derived classes with is-a relation
 */
#pragma once
#include "PCH.hpp"
#include "regression_robust.hpp"
#include "m_estimator_andrews.hpp"
#include "m_estimator_bisquare.hpp"
#include "m_estimator_cauchy.hpp"
#include "m_estimator_fair.hpp"
#include "m_estimator_huber.hpp"
#include "m_estimator_logistic.hpp"
#include "m_estimator_talwar.hpp"
#include "m_estimator_welsch.hpp"

enum class REGRESSION_METHOD
{
    ANDREWS,
    BISQUARE,
    CAUCHY,
    FAIR,
    HUBER,
    LOGISTIC,
    TALWAR,
    WELSCH
};

REGRESSION_METHOD validate_reg_method(const std::string &target_method)
{
    std::map<std::string, REGRESSION_METHOD> method_list{
        {"andrews", REGRESSION_METHOD::ANDREWS},
        {"bisquare", REGRESSION_METHOD::BISQUARE},
        {"cauchy", REGRESSION_METHOD::CAUCHY},
        {"fair", REGRESSION_METHOD::FAIR},
        {"huber", REGRESSION_METHOD::HUBER},
        {"logistic", REGRESSION_METHOD::LOGISTIC},
        {"talwar", REGRESSION_METHOD::TALWAR},
        {"welsch", REGRESSION_METHOD::WELSCH}};

    auto iter_method_list = method_list.find(target_method);

    if (iter_method_list == method_list.end())
    {
        /*
            Throw error
        */
    }

    return iter_method_list->second;
}

class FACADE_REGRESSION
{
public:
    FACADE_REGRESSION() {}
    FACADE_REGRESSION(std::vector<double> &x_observed, std::vector<double> &y_observed, REGRESSION_METHOD target_method)
    {
        this->validate_input_len(static_cast<uint32_t>(x_observed.size()), static_cast<uint32_t>(y_observed.size()));

        this->m_x_observed = x_observed;
        this->m_y_observed = y_observed;
        this->m_target_method = target_method;

        this->m_w_weight = std::vector<double>(x_observed.size(), 0);
        this->m_m_slope = 0.0;
        this->m_b_intercept = 0.0;
    }
    ~FACADE_REGRESSION() {}

    void proceed_regression()
    {
        REGRESSION_ROBUST *regression = nullptr;
        switch (this->m_target_method)
        {
        case REGRESSION_METHOD::ANDREWS:
            regression = new M_ESTIMATOR_ANDREWS(m_x_observed, m_y_observed);
            break;

        case REGRESSION_METHOD::BISQUARE:
            regression = new M_ESTIMATOR_BISQUARE(m_x_observed, m_y_observed);
            break;

        case REGRESSION_METHOD::CAUCHY:
            regression = new M_ESTIMATOR_CAUCHY(m_x_observed, m_y_observed);
            break;

        case REGRESSION_METHOD::FAIR:
            regression = new M_ESTIMATOR_FAIR(m_x_observed, m_y_observed);
            break;

        case REGRESSION_METHOD::HUBER:
            regression = new M_ESTIMATOR_HUBER(m_x_observed, m_y_observed);
            break;

        case REGRESSION_METHOD::LOGISTIC:
            regression = new M_ESTIMATOR_LOGISTIC(m_x_observed, m_y_observed);
            break;

        case REGRESSION_METHOD::TALWAR:
            regression = new M_ESTIMATOR_TALWAR(m_x_observed, m_y_observed);
            break;

        case REGRESSION_METHOD::WELSCH:
            regression = new M_ESTIMATOR_WELSCH(m_x_observed, m_y_observed);
            break;

        default:
            break;
        }

        regression->perform_regression_v2();

        m_m_slope = regression->get_slope();
        m_b_intercept = regression->get_intercept();
        regression->get_weight(m_w_weight);

        delete regression;
        regression = nullptr;
    }

    void set_input(std::vector<double> &x_observed, std::vector<double> &y_observed)
    {
        this->validate_input_len(static_cast<uint32_t>(x_observed.size()), static_cast<uint32_t>(y_observed.size()));
        this->m_x_observed = x_observed;
        this->m_y_observed = y_observed;
    }

    void set_method(REGRESSION_METHOD target_method)
    {
        this->m_target_method = target_method;
    }

    void get_estimates(double &m_slope, double &b_intercept)
    {
        m_slope = this->get_m_slope();
        b_intercept = this->get_b_intercept();
    }

    double get_m_slope() const
    {
        return this->m_m_slope;
    }

    double get_b_intercept() const
    {
        return this->m_b_intercept;
    }

    void get_w_weight(std::vector<double> w_weight)
    {
        w_weight = this->m_w_weight;
    }

private:
    REGRESSION_METHOD m_target_method;
    double m_m_slope;
    double m_b_intercept;
    std::vector<double> m_x_observed;
    std::vector<double> m_y_observed;
    std::vector<double> m_w_weight;

    void validate_input_len(uint32_t x_length, uint32_t y_length)
    {
        if (x_length != y_length)
        {
            // throw logic error
        }
    }
};