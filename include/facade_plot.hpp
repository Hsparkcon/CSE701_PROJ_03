#pragma once
#include "outlier_plot.hpp"

class FACADE_PLOT : protected OUTLIER_PLOT
{
public:
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

    ~FACADE_PLOT() {}

    void draw_axis_line(RGB_COLOUR axis_colour, uint32_t line_thickness)
    {
        draw_axis(axis_colour, line_thickness);
    }

    void draw_observed_point(RGB_COLOUR marker_colour, uint32_t marker_size)
    {
        draw_data_points(m_x_observed, m_y_observed, marker_colour, marker_size);
    }

    void draw_outlier_point(RGB_COLOUR marker_colour, uint32_t marker_size)
    {
        draw_data_points(m_x_outlier, m_y_outlier, marker_colour, marker_size);
    }

    void draw_inlier_point(RGB_COLOUR marker_colour, uint32_t marker_size)
    {
        draw_data_points(m_x_inlier, m_y_inlier, marker_colour, marker_size);
    }

    void draw_line_of_best_fit(const RGB_COLOUR line, const uint32_t line_thickness)
    {
        draw_line(m_slope, m_intercept, line_thickness, line);
    }

    void draw_all()
    {
        this->draw_axis_line(m_colour_axis_default, m_thickness_axis_default);
        this->draw_line_of_best_fit(m_colour_blf_default, m_thickness_blf_default);
        this->draw_observed_point(m_colour_observed_default, m_radius_observed_default);
        this->draw_outlier_point(m_colour_outlier_default, m_radius_outlier_default);
        this->draw_inlier_point(m_colour_inlier_default, m_radius_inlier_default);
    }

    void generate_plot(const std::string file_name)
    {
        generate_result(file_name);
    }

private:
    BMP_OUT plot_result;

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