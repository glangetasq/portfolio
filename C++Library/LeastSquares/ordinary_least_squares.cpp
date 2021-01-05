//
// Created by Quentin Glangetas [pro] on 1/5/21.
//

#include "ordinary_least_squares.h"

using namespace std;

OLS::OLS() : AbstractLeastSquares() {

}

void OLS::fit(Matrix &X, Matrix &Y, bool verbose) {

    Matrix X_ = X;
    //if (intercept) X_ = add_ones(X);

    auto R = QR(X_).second;
    auto R_inv = smooth(inv(R));

    beta_hat = R_inv * R_inv.transpose() * X_.transpose() * Y;
    auto Y_hat = X_ * beta_hat;

    double sigma2_hat = sum(square(Y_hat-Y));

    Matrix covMatrix = R_inv * R_inv.transpose() * sigma2_hat;

    if (verbose) cout << Statistics(beta_hat, Y_hat, Y, covMatrix) << endl;

}


Matrix OLS::predict(Matrix &X) {
    return X * beta_hat;
}

