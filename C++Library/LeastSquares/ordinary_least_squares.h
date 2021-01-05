//
// Created by Quentin Glangetas [pro] on 1/5/21.
//

#ifndef LEASTSQUARES_ORDINARY_LEAST_SQUARES_H
#define LEASTSQUARES_ORDINARY_LEAST_SQUARES_H

#include <iostream>

#include "abstract_least_squares.h"
#include "linear_algebra.h"
#include "statistics.h"


class OLS : public AbstractLeastSquares {

public:

    explicit OLS();

    void fit(Matrix &X, Matrix &Y, bool) override;
    Matrix predict(Matrix &X) override;

};


#endif //LEASTSQUARES_ORDINARY_LEAST_SQUARES_H
