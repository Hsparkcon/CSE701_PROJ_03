/**
 * The file contains facade version of outlier detection method.
 * 
 */
#pragma once
#include "outlier_detection.hpp"

/**
 * @brief
 * ENUM CLASS that contains variables to choose outlier detection method.
 */
enum class DETECTION_METHOD
{
    WEIGHT,
    STANDARDIZED_RESIDUAL
};

/**
 * @brief
 * Validates chosen method given through command-line argument is correct.
 * It throws a runtime exception if such a method does not exist.
 *
 * @param[in] target_method targeted method
 * @return DETECTION_METHOD
 */
DETECTION_METHOD validate_det_method(const std::string &target_method)
{
    std::map<std::string, DETECTION_METHOD> method_list{
        {"weight", DETECTION_METHOD::WEIGHT},
        {"standardized_residual", DETECTION_METHOD::STANDARDIZED_RESIDUAL}};

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
 *  FACADE_DETECTION class is a simplified version of OUTLIER_DETECTION class.
 *
 * @details
 *  FACADE_DETECTION class allows users not to worry about
 *  vector initialization, computation process and others as long as
 *  the required data can be appropriately provided.
 *  Use of FACADE_DETECTION class is suggested instead of OUTLIER_DETECTION class
 *  if the user does not plan to change internal computation methods.
 *  FACADE_DETECTION class inherits class OUTLIER_DETECTION with is-a relation.
 */
class FACADE_DETECTION : public OUTLIER_DETECTION
{
public:
    /**
     * @brief The default constructor, needs to be deleted.
     *
     */
    FACADE_DETECTION()
    {
        this->ready_standardized_detection = false;
        this->ready_weight_detection = false;
    }

    /**
     * @brief
     * Constructs a new FACADE_DETECTION object and initializes the object is ready for
     * outlier detection by standardized residual.
     * @details
     * Standard method follows conservative way, and suggested to be used.
     *
     * @param[in] x_observed A collection of observed data's independent variables (X-Axis).
     * @param[in] y_observed A collection of observed data's dependent variables (Y-Axis).
     * @param[in] m_slope A slope of line of best fit computed from linear regression method.
     * @param[in] b_intercept A intercept of line of best fit computed from linear regression method.
     */
    FACADE_DETECTION(
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        const double m_slope,
        const double b_intercept)
    {
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

    /**
     * @brief
     * Constructs a new FACADE_DETECTION object and initializes the object is ready for
     * outlier detection by weight.
     * @details
     * Non-standard method, implemented for test purpose and not suggested to be used.
     *
     * @param[in] x_observed A collection of observed data's independent variables (X-Axis).
     * @param[in] y_observed A collection of observed data's dependent variables (Y-Axis).
     * @param[in] w_weight A collection of weight of each variables in observed data.
     */
    FACADE_DETECTION(
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        const std::vector<double> &w_weight)
    {
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

    /**
     * @brief
     * Constructs a new FACADE_DETECTION object and initializes the object is ready for
     * outlier detection by both standardized residual and weight.
     *
     * @param[in] x_observed A collection of observed data's independent variables (X-Axis).
     * @param[in] y_observed A collection of observed data's dependent variables (Y-Axis).
     * @param[in] w_weight A collection of weight of each variables in observed data.
     * @param[in] m_slope A slope of line of best fit computed from linear regression method.
     * @param[in] b_intercept A intercept of line of best fit computed from linear regression method.
     */
    FACADE_DETECTION(
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        const std::vector<double> &w_weight,
        const double m_slope,
        const double b_intercept)
    {
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

    /**
     * @brief The default destructor, no special action required.
     *
     */
    ~FACADE_DETECTION() {}

    /**
     * @brief
     * Proceeds outlier detection based on a chosen method.
     * @details
     * The object must be initialized for the chosen method or for all methods.
     * Otherwise it will throw a runtime error.
     *
     * @param target_method
     */
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

    /**
     * @brief Return the number of detected outliers.
     *
     * @return uint32_t
     */
    uint32_t get_num_outlier() const
    {
        return this->m_num_outliers;
    }

    /**
     * @brief Get the collection of detected outliers.
     *
     * @param[out] x_outliers A collection of outliers in observed data's independent variables (X-Axis).
     * @param[out] y_outliers A collection of outliers in observed data's dependent variables (Y-Axis).
     */
    void get_outliers(std::vector<double> &x_outliers, std::vector<double> &y_outliers)
    {
        x_outliers = this->m_x_outliers;
        y_outliers = this->m_y_outliers;
    }

    /**
     * @brief Get the collection of detected inliers.
     *
     * @param[out] x_inliers A collection of inliers in observed data's independent variables (X-Axis).
     * @param[out] y_inliers A collection of inliers in observed data's dependent variables (Y-Axis).
     */
    void get_inliers(std::vector<double> &x_inliers, std::vector<double> &y_inliers)
    {
        x_inliers = this->m_x_inliers;
        y_inliers = this->m_y_inliers;
    }

private:
    uint32_t m_num_outliers = 0;
    double m_m_slope;
    double m_b_intercept;
    std::vector<double> m_x_observed;
    std::vector<double> m_y_observed;
    std::vector<double> m_w_weight;
    std::vector<double> m_x_outliers;
    std::vector<double> m_y_outliers;
    std::vector<double> m_x_inliers;
    std::vector<double> m_y_inliers;
    bool ready_weight_detection = false;
    bool ready_standardized_detection = false;

    /**
     * @brief
     * Proceeds outlier detection process by standardized residual.
     * @details
     * The object must be initialized for a detection by standardized residual process.
     * Otherwise, it will throw a runtime error.
     *
     */
    void detect_by_std_residual()
    {
        if (ready_standardized_detection == false)
        {
            std::string error_message =
                "FACADE DETECTION ERROR - CANNOT PROCEED WITH OUTLIER DETECTION.\n"
                "Use of standardized detection is chosen, but the object is not initialized for it.\n";
            throw std::runtime_error(error_message);
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

    /**
     * @brief
     * Proceeds outlier detection process by weight data.
     * @details
     * The object must be initialized for a detection by weight process.
     * Otherwise, it will throw a runtime error.
     *
     */
    void detect_by_weight()
    {
        if (ready_weight_detection == false)
        {
            std::string error_message =
                "FACADE DETECTION ERROR - CANNOT PROCEED WITH OUTLIER DETECTION.\n"
                "Use of weight detection is chosen, but the object is not initialized for it.\n";
            throw std::runtime_error(error_message);
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
};