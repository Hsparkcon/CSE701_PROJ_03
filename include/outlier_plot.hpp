#pragma once
#include "bmp_out.hpp"

class OUTLIER_PLOT
{
public:
    OUTLIER_PLOT(const std::vector<double> &x_observed, const std::vector<double> &y_observed) : m_x_observed(x_observed), m_y_observed(y_observed)
    {
        this->init_image();
    }

    ~OUTLIER_PLOT() {}

    void draw_axis(const RGB_COLOUR axis_colour, const uint32_t axis_thickness)
    {
        uint32_t graph_zero_y = compute_coordinate(0, m_zero_pos_y, m_actual_height, m_graph_height);
        for (uint32_t x_axis = 0; x_axis < m_graph_width; x_axis++)
        {
            draw_marker(x_axis, graph_zero_y, axis_thickness, axis_colour);
        }

        uint32_t graph_zero_x = compute_coordinate(0, m_zero_pos_x, m_actual_width, m_graph_width);
        for (uint32_t y_axis = 0; y_axis < m_graph_height; y_axis++)
        {
            draw_marker(graph_zero_x, y_axis, axis_thickness, axis_colour);
        }
    }

    void draw_line(const double slope, const double intercept, const uint32_t line_thickness, const RGB_COLOUR &line_colour)
    {
        uint32_t scaled_intercept =
            compute_coordinate(intercept, m_zero_pos_y, m_actual_height, m_graph_height);

        uint32_t graph_y = 0;
        for (uint32_t x = 0; x < m_graph_width; x++)
        {
            graph_y = static_cast<uint32_t>(slope) * x + scaled_intercept;
            draw_marker(x, graph_y, line_thickness, line_colour);
        }
    }

    void draw_data_points(const std::vector<double> &arr_x, const std::vector<double> &arr_y, const RGB_COLOUR &marker_colour, const uint32_t marker_radius)
    {
        uint32_t x_coordinate = 0;
        uint32_t y_coordinate = 0;
        for (uint32_t i = 0; i < arr_x.size(); i++)
        {
            compute_coordinates(arr_x[i], arr_y[i], x_coordinate, y_coordinate);
            draw_marker(x_coordinate, y_coordinate, marker_radius, marker_colour);
        }
    }

    void generate_result(const std::string file_name)
    {
        plot_result.write_bmp_image(file_name);
    }

private:
    const uint32_t max_dimension = 1500;

    BMP_OUT plot_result;

    std::vector<double> m_x_observed;
    std::vector<double> m_y_observed;
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
        m_x_min = get_min_value(x_observed);
        m_x_max = get_max_value(x_observed);
        m_y_min = get_min_value(y_observed);
        m_y_max = get_max_value(y_observed);

        m_zero_pos_x = compute_zero_position(m_x_min, m_x_max);
        m_zero_pos_y = compute_zero_position(m_y_min, m_y_max);

        m_actual_width = compute_dimension(m_x_min, m_x_max);
        m_actual_height = compute_dimension(m_y_min, m_y_max);

        if (m_actual_width > m_actual_height)
        {
            m_graph_width = max_dimension;
            m_graph_height = m_actual_height / m_actual_width * max_dimension;
        }
        else if (m_actual_width < m_actual_height)
        {
            m_graph_width = m_actual_width / m_actual_height * max_dimension;
            m_graph_height = max_dimension;
        }
        else
        {
            m_graph_width = max_dimension;
            m_graph_height = max_dimension;
        }
    }

    void compute_coordinates(const double act_x, const double act_y, uint32_t &graph_x, uint32_t &graph_y)
    {
        graph_x = compute_coordinate(act_x, m_zero_pos_x, m_actual_width, m_graph_width);
        graph_y = compute_coordinate(act_y, m_zero_pos_y, m_actual_height, m_graph_height);
    }

    uint32_t compute_coordinate(const double actual_pos, const double zero_pos, const double actual_len, const uint32_t graph_len)
    {
        double graph_position = 0;
        graph_position = ((actual_pos + zero_pos) * static_cast<double>(graph_len)) / actual_len;
        return static_cast<uint32_t>(std::round(graph_position));
    }

    void draw_marker(const uint32_t x_coordi, const uint32_t y_coordi, const uint32_t marker_radius, const RGB_COLOUR &marker_colour)
    {
        uint32_t marker_width_start = x_coordi < marker_radius ? x_coordi : x_coordi - marker_radius;
        uint32_t marker_width_end = (x_coordi + marker_radius > m_graph_width) ? x_coordi : x_coordi + marker_radius;

        uint32_t marker_height_start = y_coordi < marker_radius ? y_coordi : y_coordi - marker_radius;
        uint32_t marker_height_end = (y_coordi + marker_radius > m_graph_height) ? y_coordi : y_coordi + marker_radius;

        for (uint32_t y = marker_height_start; y < marker_height_end; y++)
        {
            for (uint32_t x = marker_width_start; x < marker_width_end; x++)
            {
                plot_result.set_pixel_colour(x, y, marker_colour);
            }
        }
    }

    void init_image()
    {
        set_dimension(m_x_observed, m_y_observed);
        plot_result.set_size(m_graph_width, m_graph_height);
    }
};