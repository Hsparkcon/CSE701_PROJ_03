/**
 * The following code validates correctness of the robust regression.
 * Due to the type of the computation process, exact answer cannot be given
 * Therefore, the validation is done by comparing result from Matlab and C++ implementation manually.
*/
#include "test_case.hpp"
#include "../include/l_regression.hpp"
#include "../include/m_estimator_andrews.hpp"
#include "../include/m_estimator_bisquare.hpp"
#include "../include/m_estimator_cauchy.hpp"
#include "../include/m_estimator_fair.hpp"
#include "../include/m_estimator_huber.hpp"
#include "../include/m_estimator_logistic.hpp"
#include "../include/m_estimator_talwar.hpp"
#include "../include/m_estimator_welsch.hpp"

using namespace std;

int main()
{
    double m_ols = 0;
    double b_ols = 0;
    L_REGRESSION ols_regression;
    ols_regression.ols_regression(x_observed, y_observed, m_ols, b_ols);

    // cout << scientific << m_ols << "\n";
    // cout << scientific << b_ols << endl;

    REGRESSION_ROBUST *robust_regression = nullptr;

    robust_regression = new M_ESTIMATOR_ANDREWS(x_observed, y_observed);
    robust_regression->perform_regression_v2();
    cout << "ANDREW\n";
    cout << robust_regression->get_num_iteration() << "\n";
    cout << scientific << robust_regression->get_slope() << "\n";
    cout << scientific << robust_regression->get_intercept() << "\n"
         << endl;
    delete robust_regression;
    robust_regression = nullptr;

    robust_regression = new M_ESTIMATOR_BISQUARE(x_observed, y_observed);
    robust_regression->perform_regression_v2();
    cout << "BISQUARE\n";
    cout << robust_regression->get_num_iteration() << "\n";
    cout << scientific << robust_regression->get_slope() << "\n";
    cout << scientific << robust_regression->get_intercept() << "\n"
         << endl;
    delete robust_regression;
    robust_regression = nullptr;

    robust_regression = new M_ESTIMATOR_CAUCHY(x_observed, y_observed);
    robust_regression->perform_regression_v2();
    cout << "CAUCHY\n";
    cout << robust_regression->get_num_iteration() << "\n";
    cout << scientific << robust_regression->get_slope() << "\n";
    cout << scientific << robust_regression->get_intercept() << "\n"
         << endl;
    delete robust_regression;
    robust_regression = nullptr;

    robust_regression = new M_ESTIMATOR_FAIR(x_observed, y_observed);
    robust_regression->perform_regression_v2();
    cout << "FAIR\n";
    cout << robust_regression->get_num_iteration() << "\n";
    cout << scientific << robust_regression->get_slope() << "\n";
    cout << scientific << robust_regression->get_intercept() << "\n"
         << endl;
    delete robust_regression;
    robust_regression = nullptr;

    robust_regression = new M_ESTIMATOR_HUBER(x_observed, y_observed);
    robust_regression->perform_regression_v2();
    cout << "HUBER\n";
    cout << robust_regression->get_num_iteration() << "\n";
    cout << scientific << robust_regression->get_slope() << "\n";
    cout << scientific << robust_regression->get_intercept() << "\n"
         << endl;
    delete robust_regression;
    robust_regression = nullptr;

    robust_regression = new M_ESTIMATOR_LOGISTIC(x_observed, y_observed);
    robust_regression->perform_regression_v2();
    cout << "LOGISTIC\n";
    cout << robust_regression->get_num_iteration() << "\n";
    cout << scientific << robust_regression->get_slope() << "\n";
    cout << scientific << robust_regression->get_intercept() << "\n"
         << endl;
    delete robust_regression;
    robust_regression = nullptr;

    robust_regression = new M_ESTIMATOR_TALWAR(x_observed, y_observed);
    robust_regression->perform_regression_v2();
    cout << "TALWAR\n";
    cout << robust_regression->get_num_iteration() << "\n";
    cout << scientific << robust_regression->get_slope() << "\n";
    cout << scientific << robust_regression->get_intercept() << "\n"
         << endl;
    delete robust_regression;
    robust_regression = nullptr;

    robust_regression = new M_ESTIMATOR_WELSCH(x_observed, y_observed);
    robust_regression->perform_regression_v2();
    cout << "WELSCH\n";
    cout << robust_regression->get_num_iteration() << "\n";
    cout << scientific << robust_regression->get_slope() << "\n";
    cout << scientific << robust_regression->get_intercept() << "\n"
         << endl;
    delete robust_regression;
    robust_regression = nullptr;

    return 0;
}