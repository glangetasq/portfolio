//
// Created by Quentin Glangetas [pro] on 1/5/21.
//

#ifndef LEASTSQUARES_STATISTICS_H
#define LEASTSQUARES_STATISTICS_H

#include <iostream>
#include <vector>
#include <cmath>


#include "matrix.h"
#include "linear_algebra.h"


class Statistics {
public:
    Statistics(Matrix& beta_hat, Matrix& Y_pred, Matrix& Y, Matrix &Cov) :
        beta_hat(beta_hat), Y_pred(Y_pred), Y(Y), Cov(Cov) {}

    friend std::ostream& operator<<(std::ostream& os, const Statistics& S);

private:

    Matrix beta_hat, Y_pred, Y, Cov;

};

std::ostream& operator<<(std::ostream& os, const Statistics& S);

#endif //LEASTSQUARES_STATISTICS_H
