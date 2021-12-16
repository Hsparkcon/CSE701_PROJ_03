#pragma once
#include "bmp_out.hpp"

class OUTLIER_DRAW
{
public:
    OUTLIER_DRAW(
        const std::vector<double> &x_observed,
        const std::vector<double> &y_observed,
        const std::vector<double> &x_outlier,
        const std::vector<double> &y_outlier,
        const std::vector<double> &x_inlier,
        const std::vector<double> &y_inlier) : m_x_observed(x_observed),
                                               m_y_observed(y_observed),
                                               m_x_outlier(x_outlier),
                                               m_y_outlier(y_outlier),
                                               m_x_inlier(x_inlier),
                                               m_y_inlier(y_inlier)

    {
    }
    ~OUTLIER_DRAW() {}

    void init_image()
    {
        set_dimension(this->m_x_observed, this->m_y_observed);
        plot_result.set_size(this->m_graph_width, this->m_graph_height);
        plot_result.set_image_black();
    }

    void draw_result()
    {
        this->draw_axis();

        RGB_COLOUR line_colour(255, 255, 0);
        this->draw_line(2, 3, 1, line_colour);

        this->draw_observed();
        this->draw_outlier();
        plot_result.write_bmp_image("testing_plot.bmp");
    }

    void draw_line(const double slope, const double intercept, const uint32_t line_thickness, const RGB_COLOUR &line_colour)
    {

        uint32_t scaled_intercept =
            this->compute_coordinate(intercept, this->m_zero_pos_y, this->m_actual_height, this->m_graph_height);

        uint32_t graph_y = 0;
        for (uint32_t x = 0; x < this->m_graph_width; x++)
        {
            graph_y = static_cast<uint32_t>(slope) * x + scaled_intercept;
            draw_marker(x, graph_y, line_thickness, line_colour);
        }
    }

    void draw_axis()
    {
        uint32_t graph_zero_y = compute_coordinate(0, this->m_zero_pos_y, this->m_actual_height, this->m_graph_height);

        for (uint32_t x_axis = 0; x_axis < this->m_graph_width; x_axis++)
        {
            RGB_COLOUR observed_marker{255, 255, 255};
            plot_result.set_pixel_colour(x_axis, graph_zero_y, observed_marker);
        }

        uint32_t graph_zero_x = compute_coordinate(0, this->m_zero_pos_x, this->m_actual_width, this->m_graph_width);
        for (uint32_t y_axis = 0; y_axis < this->m_graph_height; y_axis++)
        {
            RGB_COLOUR observed_marker{255, 255, 255};
            plot_result.set_pixel_colour(graph_zero_x, y_axis, observed_marker);
        }
    }

    void draw_marker(const uint32_t x_coordi, const uint32_t y_coordi, const uint32_t marker_radius, const RGB_COLOUR &marker_colour)
    {
        uint32_t marker_width_start = x_coordi < marker_radius ? x_coordi : x_coordi - marker_radius;
        uint32_t marker_width_end = (x_coordi + marker_radius > this->m_graph_width) ? x_coordi : x_coordi + marker_radius;

        uint32_t marker_height_start = y_coordi < marker_radius ? y_coordi : y_coordi - marker_radius;
        uint32_t marker_height_end = (y_coordi + marker_radius > this->m_graph_height) ? y_coordi : y_coordi + marker_radius;

        for (uint32_t y = marker_height_start; y < marker_height_end; y++)
        {
            for (uint32_t x = marker_width_start; x < marker_width_end; x++)
            {
                plot_result.set_pixel_colour(x, y, marker_colour);
            }
        }
    }

    void draw_observed()
    {
        uint32_t x_coordinate = 0;
        uint32_t y_coordinate = 0;
        RGB_COLOUR observed_marker{255, 255, 255};
        for (uint32_t i = 0; i < m_x_observed.size(); i++)
        {
            this->compute_coordinates(m_x_observed[i], m_y_observed[i], x_coordinate, y_coordinate);
            this->draw_marker(x_coordinate, y_coordinate, 1, observed_marker);
        }
    }

    void draw_outlier()
    {
        uint32_t x_coordinate = 0;
        uint32_t y_coordinate = 0;
        RGB_COLOUR outlier_marker{255, 0, 0};
        for (uint32_t i = 0; i < m_x_outlier.size(); i++)
        {

            this->compute_coordinates(m_x_outlier[i], m_y_outlier[i], x_coordinate, y_coordinate);
            this->draw_marker(x_coordinate, y_coordinate, 5, outlier_marker);
        }
    }

    void draw_inlier()
    {
        uint32_t x_coordinate = 0;
        uint32_t y_coordinate = 0;
        RGB_COLOUR inlier_marker{0, 255, 255};
        for (uint32_t i = 0; i < m_x_outlier.size(); i++)
        {
            this->compute_coordinates(m_x_inlier[i], m_y_inlier[i], x_coordinate, y_coordinate);
            plot_result.set_pixel_colour(x_coordinate, y_coordinate, inlier_marker);
        }
    }

private:
    BMP_OUT plot_result;

    const uint32_t max_dimension = 1510;

    std::vector<double> m_x_observed;
    std::vector<double> m_y_observed;
    std::vector<double> m_x_outlier;
    std::vector<double> m_y_outlier;
    std::vector<double> m_x_inlier;
    std::vector<double> m_y_inlier;

    uint32_t m_graph_width;
    uint32_t m_graph_height;

    double m_actual_width;
    double m_actual_height;
    double m_zero_pos_x;
    double m_zero_pos_y;
    double m_x_min;
    double m_x_max;
    double m_y_min;
    double m_y_max;

    double get_min_value(const std::vector<double> &input_vec)
    {
        double curr_min = input_vec[0];
        for (const auto &element : input_vec)
        {
            curr_min = curr_min < element ? curr_min : element;
        }
        return curr_min;
    }

    double get_max_value(const std::vector<double> &input_vec)
    {
        double curr_max = input_vec[0];
        for (const auto &element : input_vec)
        {
            curr_max = curr_max > element ? curr_max : element;
        }
        return curr_max;
    }

    double compute_dimension(double dim_min, double dim_max)
    {
        if (dim_max <= 0)
        {
            return std::abs(dim_min);
        }
        else if (dim_min >= 0)
        {
            return dim_max;
        }
        else if (dim_max > 0 && dim_min < 0)
        {
            return dim_max - dim_min;
        }

        return 0;
    }

    double compute_zero_position(double dim_min, double dim_max)
    {
        if (dim_max <= 0)
        {
            return std::abs(dim_min);
        }
        else if (dim_min >= 0)
        {
            return 0;
        }
        else if (dim_max > 0 && dim_min < 0)
        {
            return std::abs(dim_min);
        }

        return 0;
    }

    void set_dimension(const std::vector<double> &x_observed, const std::vector<double> &y_observed)
    {
        this->m_x_min = this->get_min_value(x_observed);
        this->m_x_max = this->get_max_value(x_observed);
        this->m_y_min = this->get_min_value(y_observed);
        this->m_y_max = this->get_max_value(y_observed);

        this->m_zero_pos_x = this->compute_zero_position(this->m_x_min, this->m_x_max);
        this->m_zero_pos_y = this->compute_zero_position(this->m_y_min, this->m_y_max);
        this->m_actual_width = this->compute_dimension(this->m_x_min, this->m_x_max);
        this->m_actual_height = this->compute_dimension(this->m_y_min, this->m_y_max);

        if (this->m_actual_width > this->m_actual_height)
        {
            this->m_graph_width = this->max_dimension;
            this->m_graph_height = this->m_actual_height / this->m_actual_width * this->max_dimension;
        }
        else if (this->m_actual_width < this->m_actual_height)
        {
            this->m_graph_width = this->m_actual_width / this->m_actual_height * this->max_dimension;
            this->m_graph_height = this->max_dimension;
        }
        else
        {
            this->m_graph_width = this->max_dimension;
            this->m_graph_height = this->max_dimension;
        }
    }

    void compute_coordinates(const double act_x, const double act_y, uint32_t &graph_x, uint32_t &graph_y)
    {
        graph_x = this->compute_coordinate(act_x, this->m_zero_pos_x, this->m_actual_width, this->m_graph_width);
        graph_y = this->compute_coordinate(act_y, this->m_zero_pos_y, this->m_actual_height, this->m_graph_height);
    }

    uint32_t compute_coordinate(const double actual_pos, const double zero_pos, const double actual_len, const uint32_t graph_len)
    {
        double graph_position = 0;
        graph_position = ((actual_pos + zero_pos) * static_cast<double>(graph_len)) / actual_len;
        return static_cast<uint32_t>(graph_position);
    }
};