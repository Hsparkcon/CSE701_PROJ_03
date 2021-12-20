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

/**
 * @brief
 * ENUM CLASS that contains variables to choose robust regression method.
 */
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

/**
 * @brief
 * Validates chosen method given through command-line argument is correct.
 * It throws a runtime exception if such a method does not exist in the predefined list.
 *
 * @param[in] target_method targeted method
 * @return DETECTION_METHOD
 */
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
        std::string error_message =
            "INPUT ARGUMENT ERROR - THERE IS NO SUCH METHOD.\n"
            "Input must match with predefined methods while\n"
            "given - " +
            target_method + " - does not exist.\n"
                            "Please choose the correct method based on the instruction by executing the program without parameters.";
        throw std::runtime_error(error_message);
    }

    return iter_method_list->second;
}

/**
 * @brief
 *  FACADE_REGRESSION class is a simplified version of REGRESSION_ROBUST class.
 *
 * @details
 *  FACADE_DETECTION class allows users not to worry about
 *  vector initialization, computation process and others as long as
 *  the required data can be appropriately provided.
 *  Use of FACADE_DETECTION class is suggested instead of REGRESSION_ROBUST class
 *  if the user does not plan to change internal computation methods or to use a custom weight function
 *  FACADE_REGRESSION class uses REGRESSION_ROBUST with has-a relation.
 */
class FACADE_REGRESSION
{
public:
    /**
     * @brief The default constructor, constructs a new FACADE_REGRESSION object that is not initialized.
     * If it is used, the member variables must be initialized with the member function
     * - set_method()
     * - set_observed.
     *
     */
    FACADE_REGRESSION()
    {
        m_is_data_initialized = false;
        m_is_method_initialized = false;
    }

    /**
     * @brief Construct a new FACADE_REGRESSION object that is fully initialized member variables.
     *
     * @param[in] x_observed A collection of observed data's independent variables (X-Axis).
     * @param[in] y_observed A collection of observed data's dependent variables (Y-Axis).
     * @param[in] target_method Weight function that will be used for robust regression computation.
     */
    FACADE_REGRESSION(
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        const REGRESSION_METHOD target_method)
    {
        m_is_data_initialized = true;
        m_is_method_initialized = true;

        this->m_x_observed = x_observed;
        this->m_y_observed = y_observed;
        this->m_target_method = target_method;

        this->m_w_weight = std::vector<double>(x_observed.size(), 0);
        this->m_m_slope = 0.0;
        this->m_b_intercept = 0.0;
    }

    /**
     * @brief The default destructor, no special action required.
     *
     */
    ~FACADE_REGRESSION() {}

    /**
     * @brief
     * Perfroms robust regression with the initialized member variables.
     * Must be used after initialization; otherwise, it would throw a runtime error.
     *
     */
    void proceed_regression()
    {
        validate_data_initialization();
        validate_method_initialization();

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

        regression->perform_regression();

        m_m_slope = regression->get_slope();
        m_b_intercept = regression->get_intercept();
        regression->get_weight(m_w_weight);

        delete regression;
        regression = nullptr;
    }

    /**
     * @brief Sets the new data for robust regression computation.
     *
     * @param[in] x_observed A collection of observed data's independent variables (X-Axis).
     * @param[in] y_observed A collection of observed data's dependent variables (Y-Axis).
     */
    void set_observed(const std::vector<double> &x_observed, const std::vector<double> &y_observed)
    {
        this->m_x_observed = x_observed;
        this->m_y_observed = y_observed;
    }

    /**
     * @brief Set the other weight function for robust regression computation.
     *
     * @param target_method Weight function listed in REGRESSION_METHOD.
     */
    void set_method(const REGRESSION_METHOD target_method)
    {
        this->m_target_method = target_method;
    }

    /**
     * @brief Gets the estimates of the line of best fit.
     *
     * @param[out] m_slope A slope of line of best fit.
     * @param[out] b_intercept A intercept of line of best fit.
     */
    void get_estimates(double &m_slope, double &b_intercept)
    {
        m_slope = this->get_m_slope();
        b_intercept = this->get_b_intercept();
    }

    /**
     * @brief Gets the approximate slope of the line of best fit.
     *
     * @return double
     */
    double get_m_slope() const
    {
        return this->m_m_slope;
    }

    /**
     * @brief Gets the approximate intercept of the line of best fit.
     *
     * @return double
     */
    double get_b_intercept() const
    {
        return this->m_b_intercept;
    }

    /**
     * @brief Gets the weight of observed data point computed during the robust regression process.
     *
     * @param[out] w_weight A collection of observed data's weight.
     */
    void get_w_weight(std::vector<double> &w_weight)
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

    bool m_is_data_initialized;
    bool m_is_method_initialized;

    /**
     * @brief
     * Validates the data for regression computation is initialized.
     * If not initialized, it throws a runtime error.
     *
     */
    void validate_data_initialization()
    {
        if (m_is_data_initialized == false)
        {
            std::string error_message =
                "FACADE REGRESSION ERROR - DATA NOT INITIALIZED\n"
                "Observed data is not initialized.\n";
            throw std::runtime_error(error_message);
        }
    }

    /**
     * @brief
     * Validates the weight function for regression computation is chosen.
     * If not initialized, it throws a runtime error.
     *
     */
    void validate_method_initialization()
    {
        if (m_is_method_initialized == false)
        {
            std::string error_message =
                "FACADE REGRESSION ERROR - WEIGHT FUNCTION NOT CHOSEN.\n"
                "Weight function for regression method is not chosen.\n";
            throw std::runtime_error(error_message);
        }
    }
};