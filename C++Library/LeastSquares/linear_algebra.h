//
// Created by Quentin Glangetas [pro] on 1/4/21.
//

#ifndef LEASTSQUARES_LINEAR_ALGEBRA_H
#define LEASTSQUARES_LINEAR_ALGEBRA_H

#include "matrix.h"
#include <vector>
#include <utility>
#include <cmath>

struct LinAlg {
    typedef MatrixFactory Matrix;
    typedef VectorFactory Vector;
};

std::pair<Matrix, Matrix> QR(const Matrix&);
Matrix backsubstitution(const Matrix&, const Matrix&);
Matrix inv(const Matrix&);

Matrix smooth(const Matrix&, double = 1e-10);
Matrix square(const Matrix&);
double sum(const Matrix&);
double mean(const Matrix&);


#endif //LEASTSQUARES_LINEAR_ALGEBRA_H
