#pragma once
#include "outlier_plot.hpp"

/**
 * @brief
 *  FACADE_PLOT class is a simplified version of OUTLIER_PLOT class.
 *  FACADE_PLOT class adds xy-axis, line of best fit, and observed/inlier/outlier data points in the plot.
 *
 * @details
 *  FACADE_PLOT class allows users not to worry about
 *  image size initialization, computation process and others as long as
 *  the required data can be appropriately provided.
 *  Use of FACADE_PLOT class is suggested instead of OUTLIER_PLOT class
 *  if the user does not plan add additional data into the output plot.
 *  FACADE_PLOT class does not have validation function as validation will be done by OUTLIER_PLOT class.
 *  FACADE_PLOT class inherits class OUTLIER_DETECTION with is-a relation.
 */
class FACADE_PLOT : protected OUTLIER_PLOT
{
public:
    /**
     * @brief Construct a new FACADE_PLOT object and initializes entire data to generate output.
     *
     * @param[in] x_observed A collection of observed data's independent variables (X-Axis).
     * @param[in] y_observed A collection of observed data's dependent variables (Y-Axis).
     * @param[in] x_outlier A collection of outliers in observed data in X-Axis.
     * @param[in] y_outlier A collection of outliers in observed data in Y-Axis.
     * @param[in] x_inlier A collection of inliers in observed data in X-Axis.
     * @param[in] y_inlier A collection of inliers in observed data in Y-Axis.
     * @param[in] slope A slope of line of best fit computed from linear regression method.
     * @param[in] intercept A intercept of line of best fit computed from linear regression method.
     */
    FACADE_PLOT(
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        const std::vector<double> &x_outlier,
        const std::vector<double> &y_outlier,
        const std::vector<double> &x_inlier,
        const std::vector<double> &y_inlier,
        const double slope,
        const double intercept) : OUTLIER_PLOT(x_observed, y_observed),
                                  m_x_observed(x_observed),
                                  m_y_observed(y_observed),
                                  m_x_outlier(x_outlier),
                                  m_y_outlier(y_outlier),
                                  m_x_inlier(x_inlier),
                                  m_y_inlier(y_inlier),
                                  m_slope(slope),
                                  m_intercept(intercept)
    {
    }

    /**
     * @brief The default destructor, no special action required.
     *
     */
    ~FACADE_PLOT() {}

    /**
     * @brief Adds xy-axis line to the plot
     *
     * @param[in] axis_colour RGB colour data of axis line
     * @param[in] line_thickness Thickness of xy-axis in pixel. If the value is zero, the thickness would be 1 pixel.
     */
    void draw_axis_line(RGB_COLOUR axis_colour, uint32_t line_thickness)
    {
        draw_axis(axis_colour, line_thickness);
    }

    /**
     * @brief Adds observed data to the plot.
     *
     * @param[in] marker_colour RGB colour data of marker.
     * @param[in] marker_size Radius of marker. If the value is zero, the size would be 1 pixel.
     */
    void draw_observed_point(RGB_COLOUR marker_colour, uint32_t marker_size)
    {
        draw_data_points(m_x_observed, m_y_observed, marker_colour, marker_size);
    }

    /**
     * @brief Adds outlier data to the plot.
     *
     * @param[in] marker_colour RGB colour data of marker.
     * @param[in] marker_size Radius of marker. If the value is zero, the size would be 1 pixel.
     */
    void draw_outlier_point(RGB_COLOUR marker_colour, uint32_t marker_size)
    {
        draw_data_points(m_x_outlier, m_y_outlier, marker_colour, marker_size);
    }

    /**
     * @brief Adds inlier data to the plot
     *
     * @param[in] marker_colour RGB colour data of marker.
     * @param[in] marker_size Radius of marker. If the value is zero, the size would be 1 pixel.
     */
    void draw_inlier_point(RGB_COLOUR marker_colour, uint32_t marker_size)
    {
        draw_data_points(m_x_inlier, m_y_inlier, marker_colour, marker_size);
    }

    /**
     * @brief Adds line of best fit to the plot
     *
     * @param[in] line_colour RGB colour data of line.
     * @param[in] line_thickness Thickness of line in pixel. If the value is zero, the thickness would be 1 pixel.
     */
    void draw_line_of_best_fit(const RGB_COLOUR line_colour, const uint32_t line_thickness)
    {
        draw_line(m_slope, m_intercept, line_thickness, line_colour);
    }

    /**
     * @brief Adds entire contents to the plot with defaust colour and size setting.
     * @details Suggested to be used when entire content is wanted.
     * 
     */
    void draw_all()
    {
        this->draw_axis_line(m_colour_axis_default, m_thickness_axis_default);
        this->draw_line_of_best_fit(m_colour_blf_default, m_thickness_blf_default);
        this->draw_observed_point(m_colour_observed_default, m_radius_observed_default);
        this->draw_outlier_point(m_colour_outlier_default, m_radius_outlier_default);
        this->draw_inlier_point(m_colour_inlier_default, m_radius_inlier_default);
    }

    /**
     * @brief Generates BMP output with given name.
     * 
     * @param[in] file_name Name of the file to be generated, it must include file format (.bmp) as part of the name.
     * 
     */
    void generate_plot(const std::string file_name)
    {
        generate_result(file_name);
    }

private:
    std::vector<double> m_x_observed;
    std::vector<double> m_y_observed;
    std::vector<double> m_x_outlier;
    std::vector<double> m_y_outlier;
    std::vector<double> m_x_inlier;
    std::vector<double> m_y_inlier;

    double m_slope;
    double m_intercept;

    uint32_t m_thickness_axis_default = 2;
    uint32_t m_radius_observed_default = 3;
    uint32_t m_radius_outlier_default = 2;
    uint32_t m_radius_inlier_default = 2;
    uint32_t m_thickness_blf_default = 2;

    RGB_COLOUR m_colour_axis_default{0, 0, 0};
    RGB_COLOUR m_colour_observed_default{0, 0, 0};
    RGB_COLOUR m_colour_outlier_default{255, 0, 0};
    RGB_COLOUR m_colour_inlier_default{255, 255, 0};
    RGB_COLOUR m_colour_blf_default{0, 0, 255};
};