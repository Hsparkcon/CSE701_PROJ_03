#pragma once
#include "bmp_out.hpp"

/**
 * @brief
 * OUTLIER_PLOT class is a collection of member functions and variables designed to
 * generate BMP files to provide visualized output for CSE701_PROJ03.
 * @details
 * OUTLIER_PLOT class provides fundmental functions to plot data using BMP_OUT class.
 * OUTLIER_PLOT class is implemented for users who cannot use third-party tools to
 * create visualized result from the computation result.
 * OUTLIER_PLOT class is not suitable for general purposes, and
 * the output results may be less accurate compared to the well-known open-source libraries plotting method.
 * Most validation process will be done by BMP_OUT class;
 * therefore, OUTLIER_PLOT does not have validation function except vectors length match check.
 *
 */
class OUTLIER_PLOT
{
public:
    /**
     * @brief
     * The constructor constructs a new OUTLIER_PLOT object, and
     * receives data points to be plotted and initializes the size of the image to be generated.
     * @details
     * Once the image size is initialized, a collection of data points that has
     * values bigger than the minimum value of the initial input
     * values smaller than the maximum value of the initial input
     * can be added, but the opposite case cannot be added.
     *
     * It automatically scales data points to be matched to image pixel coordinates.
     * The process is necessary to be plot data but may cause inaccuracy due to
     * rounding error required to convert double type value into integer type value.
     *
     * @param[in] x_observed A collection of observed data's independent variables (X-Axis).
     * @param[in] y_observed A collection of observed data's dependent variables (Y-Axis).
     */
    OUTLIER_PLOT(const std::vector<double> &x_observed, const std::vector<double> &y_observed) : m_x_observed(x_observed), m_y_observed(y_observed)
    {
        this->init_image();
    }

    /**
     * @brief The default destructor, no special action is required.
     *
     */
    ~OUTLIER_PLOT() {}

    /**
     * @brief The function adds xy-axis to the output..
     *
     * @param[in] axis_colour The RGB colour data to define colour of xy-axis.
     * @param[in] axis_thickness The thickness of the xy-axis in pixel unit. If the value is zero, the thickness would be 1 pixel.
     */
    void draw_axis(const RGB_COLOUR &axis_colour, const uint32_t axis_thickness)
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

    /**
     * @brief
     * The function draws linear-line accross the image.
     * @details
     * As the class is designed to visualize linear regression results,
     * it draws a line with the following relationship only.
     * y = m * x + b where
     * m = Slope of the line to be drawn
     * b = Internally scaled intercept of line to be drawn
     * x = Images width pixel
     *
     * @param[in] slope slope of line to be drawn
     * @param[in] intercept intercept of line to be drawn
     * @param[in] line_thickness Thickness of the line in pixel unit. If the value is zero, the thickness would be 1 pixel.
     * @param[in] line_colour RGB colour data to define colour of the line.
     */
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

    /**
     * @brief The function draws points at the targeted coordinates on the image.
     *
     * @param arr_x A collection of points in X-axis
     * @param arr_y A collection of points in Y-axis
     * @param marker_colour RGB colour data to define colour of the point.
     * @param marker_radius Radius of marker to be drawn in pixel unit. If the value is zero, the size would be 1 pixel.
     */
    void draw_data_points(const std::vector<double> &arr_x, const std::vector<double> &arr_y, const RGB_COLOUR &marker_colour, const uint32_t marker_radius)
    {
        validate_vector_length_match(arr_x, arr_y);

        uint32_t x_coordinate = 0;
        uint32_t y_coordinate = 0;
        for (uint32_t i = 0; i < arr_x.size(); i++)
        {
            compute_coordinates(arr_x[i], arr_y[i], x_coordinate, y_coordinate);
            draw_marker(x_coordinate, y_coordinate, marker_radius, marker_colour);
        }
    }

    /**
     * @brief The function generates BMP output with given name.
     *
     * @param file_name Name of the file to be generated, it must include file format (.bmp) as part of the name.
     */
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

    /**
     * @brief Finds the minimum value in the given vector.
     *
     * @param[in] input_vec A collection of number.
     * @return double
     */
    double get_min_value(const std::vector<double> &input_vec)
    {
        double curr_min = input_vec[0];
        for (const auto &element : input_vec)
        {
            curr_min = curr_min < element ? curr_min : element;
        }
        return curr_min;
    }

    /**
     * @brief Finds the maximum value in the given vector.
     *
     * @param[in] input_vec A collection of number.
     * @return double
     */
    double get_max_value(const std::vector<double> &input_vec)
    {
        double curr_max = input_vec[0];
        for (const auto &element : input_vec)
        {
            curr_max = curr_max > element ? curr_max : element;
        }
        return curr_max;
    }

    /**
     * @brief Computes the length of the width/height
     * @details The result will be scaled internally to set the size of image.
     *
     * @param[in] dim_min Minimum value in X/Y-axis.
     * @param[in] dim_max Maximum value in X/Y-axis.
     * @return double
     */
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

    /**
     * @brief Computes the position of zero in X/Y-axis.
     * @details The result will be scaled internally to set the size of image.
     *
     * @param[in] dim_min Minimum value in X/Y-axis.
     * @param[in] dim_max Maximum value in X/Y-axis.
     * @return double
     */
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

    /**
     * @brief
     * Compute values requires for image size initialization.
     * @details
     * The process requires a value rounding-up process for converting double value into an integer value.
     * The process may cause a rounding error in the result.
     *
     * @param[in] x_observed A collection of observed data's X-Axis.
     * @param[in] y_observed A collection of observed data's Y-Axis.
     */
    void set_dimension(const std::vector<double> &x_observed, const std::vector<double> &y_observed)
    {
        validate_vector_length_match(x_observed, y_observed);

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
            m_graph_height = static_cast<uint32_t>(std::round(m_actual_height / m_actual_width * static_cast<double>(max_dimension)));
        }
        else if (m_actual_width < m_actual_height)
        {
            m_graph_width = static_cast<uint32_t>(std::round(m_actual_width / m_actual_height * static_cast<double>(max_dimension)));
            m_graph_height = max_dimension;
        }
        else
        {
            m_graph_width = max_dimension;
            m_graph_height = max_dimension;
        }
    }

    /**
     * @brief
     * The function scales the input value in double type to an integer type to
     * match the relative coordinate position in the image in pixel.
     *
     * @param[in] act_x X-coordinate in double type
     * @param[in] act_y Y-coordinate in double type
     * @param[out] graph_x Relative x-coordinate in pixel unit (integer type)
     * @param[out] graph_y Relative y-coordinate in pixel unit (integer type)
     */
    void compute_coordinates(const double act_x, const double act_y, uint32_t &graph_x, uint32_t &graph_y)
    {
        graph_x = compute_coordinate(act_x, m_zero_pos_x, m_actual_width, m_graph_width);
        graph_y = compute_coordinate(act_y, m_zero_pos_y, m_actual_height, m_graph_height);
    }

    /**
     * @brief
     * The function scales the input value in double type to an integer type to
     * match the relative coordinate position in the image in pixel.
     * @details
     * The process requires a value rounding-up process for converting double value into an integer value.
     * The process may cause a rounding error in the result.
     *
     * @param[in] actual_pos non-scaled coordinate data
     * @param[in] zero_pos non-scaled zero coordinate data
     * @param[in] actual_len non-scaled length of input data
     * @param[in] graph_len length of graph in pixel unit.
     * @return uint32_t
     */
    uint32_t compute_coordinate(const double actual_pos, const double zero_pos, const double actual_len, const uint32_t graph_len)
    {
        double graph_position = 0;
        graph_position = ((actual_pos + zero_pos) * static_cast<double>(graph_len)) / actual_len;
        return static_cast<uint32_t>(std::round(graph_position));
    }

    /**
     * @brief
     * The function draws marker at the targeted coordinate with the given size and colour.
     *
     * @param[in] x_coordi Targeted x-coordinate in pixel unit.
     * @param[in] y_coordi Targeted y-coordinate in pixel unit.
     * @param[in] marker_radius Radius of mark to be drawn in pixel unit. If the value is zero, the size would be 1 pixel.
     * @param[in] marker_colour RGB colour data of marker.
     */
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

    /**
     * @brief Initializes size of output image based on computed dimension data.
     *
     */
    void init_image()
    {
        set_dimension(m_x_observed, m_y_observed);
        plot_result.set_size(m_graph_width, m_graph_height);
    }

    /**
     * @brief
     * The function validates the number of given data collections matches each other and
     * throws runtime error if there is a mismatch.
     *
     * @param vec_one collection of independent variables
     * @param vec_two collection of independent variables
     */
    void validate_vector_length_match(const std::vector<double> &vec_one, const std::vector<double> &vec_two)
    {
        if (vec_one.size() != vec_two.size())
        {
            std::string error_message =
                "OUTLIER PLOT ERROR - VECTOR LENGTH MISMATCH\n"
                "Number of elements in given vector must be matched, but\n"
                "VECTOR ONE: " + std::to_string(vec_one.size()) + "\n"
                "VECTOR TWO: " + std::to_string(vec_two.size()) + "\n";
            throw std::runtime_error(error_message);
        }
    }
};