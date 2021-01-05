//
// Created by Quentin Glangetas [pro] on 1/5/21.
//

#ifndef LEASTSQUARES_ABSTRACT_LEAST_SQUARES_H
#define LEASTSQUARES_ABSTRACT_LEAST_SQUARES_H

#include <vector>

#include "matrix.h"


class AbstractLeastSquares {
protected:
    explicit AbstractLeastSquares(bool intercept = true) : intercept(intercept) {};

    Matrix add_ones(Matrix &X);
    virtual void fit(Matrix &X, Matrix &Y, bool) = 0;
    virtual Matrix predict(Matrix &X) = 0;

    bool intercept;
    Matrix beta_hat;
};


#endif //LEASTSQUARES_ABSTRACT_LEAST_SQUARES_H
