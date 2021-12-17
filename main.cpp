#include "include/facade_regression.hpp"
#include "include/facade_detection.hpp"
#include "include/facade_plot.hpp"
#include "include/data_io.hpp"

int main(int argc, char *argv[])
{
    if (argc < 5 || argc > 5)
    {
        std::cout << "The program is designed to perform linear regression and detect outlier.\n\n"
                     "First Input\n"
                     "\tWeight function for robust regression\n"
                     "\tPlease, select one from the list from the link\n"
                     "\thttps://www.mathworks.com/help/stats/robustfit.html#mw_48d239e7-b4dc-4a5e-8e97-ba7c34ce85b9\n\n"

                     "Second Input\n"
                     "\tType of outlier detection method\n"
                     "\tPlease choose one between 'weight' and 'standardized_resdual'\n\n"

                     "Third Input\n"
                     "\tPath to the first file - observed x data.\n\n"

                     "Forth Input\n"
                     "\tPath to the second file - observed y data.\n\n"
                  << std::endl;

        std::cout << "Example Input\n"
                     "\tproj_r.out bisquare standardized_residual observed_x.dvec observed_y.dvec\n"
                  << std::endl;
        return 0;
    }

    DATA_IO data_io(IO_MODE::UNSAFE);
    std::vector<double> x_observed;
    std::vector<double> y_observed;
    REGRESSION_METHOD reg_method = validate_reg_method(argv[1]);
    DETECTION_METHOD det_method = validate_det_method(argv[2]);
    data_io.load_vec(argv[3], x_observed);
    data_io.load_vec(argv[4], y_observed);

    FACADE_REGRESSION regression(x_observed, y_observed, reg_method);
    regression.proceed_regression();

    double m_slope = 0;
    double b_intercept = 0;
    std::vector<double> w_weight;
    regression.get_estimates(m_slope, b_intercept);
    regression.get_w_weight(w_weight);
    FACADE_DETECTION outlier_detect(x_observed, y_observed, w_weight, m_slope, b_intercept);
    outlier_detect.proceed_detection(det_method);

    uint32_t num_detected_outlier = 0;
    std::vector<double> x_outlier;
    std::vector<double> y_outlier;
    std::vector<double> x_inlier;
    std::vector<double> y_inlier;
    num_detected_outlier = outlier_detect.get_num_outlier();
    outlier_detect.get_outliers(x_outlier, y_outlier);
    outlier_detect.get_inliers(x_inlier, y_inlier);

    data_io.write_vec("x_outlier.dvec", x_outlier);
    data_io.write_vec("y_outlier.dvec", y_outlier);
    data_io.write_vec("x_inlier.dvec", x_inlier);
    data_io.write_vec("y_inlier.dvec", y_inlier);

    std::cout << "Computed slope: " << std::scientific << m_slope << "\n"
                                                                     "Computed intercept: "
              << std::scientific << b_intercept << "\n"
                                                   "Detected outliers: "
              << num_detected_outlier << " out of " << x_observed.size() << "\n"
              << std::endl;

    FACADE_PLOT plot_result(x_observed, y_observed, x_outlier, y_outlier, x_inlier, y_inlier, m_slope, b_intercept);
    plot_result.draw_all();
    plot_result.generate_plot("result_plot.bmp");

    return 0;
}