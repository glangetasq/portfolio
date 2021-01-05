//
// Created by Quentin Glangetas [pro] on 1/4/21.
//

#include "linear_algebra.h"

using namespace std;


/***** OTHER FUNCTIONS *****/
double dot(Matrix& vec1, Matrix& vec2)
{
    unsigned int m1 = vec1.get_n_rows(), n1 = vec1.get_n_cols();
    unsigned int m2 = vec2.get_n_rows(), n2 = vec2.get_n_cols();

    double dot_product;

    if (m1 == 1 and m2 == 1)
    {
        dot_product = (vec2 * vec1.transpose()).get_element(0, 0);
    }
    else if (m1 == 1 and n2 == 1) {
        dot_product = (vec1 * vec2).get_element(0, 0);
    }
    else if (n1 == 1 and m2 == 1) {
        dot_product = (vec2 * vec1).get_element(0, 0);
    }
    else if (n1 == 1 and n2 == 1) {
        dot_product = (vec1.transpose() * vec2).get_element(0, 0);
    }
    else {
        dot_product = 0;
    }

    return dot_product;
}


double norm(Matrix &u)
{
    return sqrt(dot(u, u));
}


Matrix projection(Matrix& u, Matrix& a)
{
    return dot(u, a) * u / dot(u, u);
}


pair<Matrix, Matrix> QR(const Matrix& M)
{

    unsigned int m = M.get_n_rows(), n = M.get_n_cols();

    if (m >= n) {
        vector<Matrix> Q;

        for (int k = 0; k < n; k++) {
            Matrix ak = M.get_vector(k, Matrix::vec::column);
            Matrix uk = M.get_vector(k, Matrix::vec::column);
            for (int j = 0; j < k; j++) {
                uk = uk - projection(Q[j], ak);
            }
            Q.push_back( uk / norm(uk) );
        }

        auto Qmat = LinAlg::Matrix::FromVec(Q);
        auto R = Qmat.transpose() * M;

        return make_pair(Qmat, R);
    } else {
        return make_pair(Matrix(m, m), Matrix(m, n));
    }
}


Matrix backsubstitution(const Matrix& R, const Matrix& b)
{
    // Assume that T and vec are compatible

    int n = R.get_n_rows();

    if (R.is_upper_triangular()) {
        auto X = vector<double>(n);
        double S;

        for (int i = n-1; i > -1; i--) {
            S = b.get_element(i, 0);
            for (int j = i + 1; j < n; j++) {
                S -= R.get_element(i, j) * X[j];
            }

            X[i] = S / R.get_element(i, i);
        }
        return LinAlg::Vector::Column::Custom(X);

    } else {
        return MatrixFactory::Zeros(n, n);
    }
}


Matrix inv(const Matrix& R)
{
    // Only inverse of an upper triangular matrix is implemented
    if (R.is_upper_triangular()) {
        unsigned int n = R.get_n_rows();
        vector<Matrix> R_inverse;

        for (int i = 0; i < n; i++) {
            auto b = LinAlg::Vector::Column::E(n, i);
            auto tmp = backsubstitution(R, b);
            R_inverse.push_back( tmp );
        }

        return LinAlg::Matrix::FromVec(R_inverse);

    } else {
        return Matrix(R.get_n_rows(), R.get_n_cols());
    }
}


Matrix smooth(const Matrix& M, const double threshold) {
    unsigned int m = M.get_n_rows(), n = M.get_n_cols();
    auto C = vector<vector<double>>(m, vector<double>(n));

    double x;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            x = M.get_element(i, j);
            x = (abs(x) < threshold) ? 0 : x;
            C[i][j] = x;
        }
    }

    return LinAlg::Matrix::Custom(C);
}


Matrix square(const Matrix& M) {

    unsigned int m = M.get_n_rows(), n = M.get_n_cols();

    auto M2 = vector<vector<double>>(m, vector<double>(n));

    double x;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            x = M.get_element(i, j);
            M2[i][j] = x * x;
        }
    }

    return LinAlg::Matrix::Custom(M2);

}


double sum(const Matrix &M) {

    unsigned int m = M.get_n_rows(), n = M.get_n_cols();
    double S;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            S += M.get_element(i, j);
        }
    }

    return S;
}


double mean(const Matrix &M) {
    return sum(M) / M.get_n_rows() / M.get_n_cols();
}