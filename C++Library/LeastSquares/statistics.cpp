//
// Created by Quentin Glangetas [pro] on 1/5/21.
//

#include "statistics.h"

using namespace std;

std::ostream &operator<<(std::ostream &os, const Statistics &S) {

    unsigned int n = S.Y.get_n_rows(), p = S.beta_hat.get_n_rows() - 1;

    double RSS = sum(square(S.Y_pred-S.Y));
    Matrix Y_mean = LinAlg::Vector::Column::Ones(n) * mean(S.Y);
    double TSS = sum(square(S.Y-Y_mean));
    double sigma_hat = sqrt(RSS / (n-p-1));

    double Z095 = 1.96;

    cout << "******************************" << endl;
    cout << "**********OLS Result**********" << endl;
    cout << "******************************" << endl;

    cout << "N = " << S.Y.get_n_rows() << endl << "p = " << S.beta_hat.get_n_rows() << endl;

    cout << endl << "Sigma Hat = " << sqrt(sigma_hat) << endl;
    cout << "R2 = " << 1 - RSS / TSS << endl;
    cout << "Adj. R2 = " << 1 - (RSS/(n-p-1)) / (TSS/(n-1)) << endl;

    cout << endl << "Coefficients:" << endl << endl;
    cout << "Dimension, Estimate, Z-Score, Lower Bound, Higher Bound" << endl;

    double std_error;
    for (int j = 0; j < p+1; j++) {

        double b = S.beta_hat.get_element(j, 0);
        std_error = S.Cov.get_element(j, j) * sigma_hat;

        cout << "BetaHat_" << j << ", ";
        cout << b << ", ";
        cout << b / std_error << ", ";
        cout << "[" << b - Z095 * std_error << ", " << b + Z095 * std_error << "]";
        cout << endl;

    }

    return os;
}
