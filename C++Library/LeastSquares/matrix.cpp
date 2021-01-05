//
// Created by Quentin Glangetas [pro] on 1/4/21.
//

#include "matrix.h"

using namespace std;


Matrix::Matrix(unsigned int m, unsigned int n, Matrix::fill fill_method) : n_rows(m), n_cols(n)
{
        double fill_value = (fill_method == fill::ones) ? 1 : 0;
        M = vector<vector<double>>(m, vector<double>(n, fill_value));

        if (fill_method == eye) {
            unsigned int min_size = (m < n) ? m : n;
            for (int i = 0; i < min_size; i++) {
                M[i][i] = 1;
            }
        }
};


Matrix::Matrix(vector<vector<double>>& M) : M(M)
{
        n_rows = M.size();
        n_cols = M[0].size();
};


// matrix operation operators
Matrix Matrix::operator+(const Matrix& other) const
{
    if (n_rows == other.n_rows && n_cols == other.n_cols) {
        auto C = vector<vector<double>>(n_rows, vector<double>(n_cols));
        for (int i = 0; i < n_rows; i++) {
            for (int j = 0; j < n_cols; j++) {
                C[i][j] = this->M[i][j] + other.M[i][j];
            }
        }
        return Matrix(C);
    } else {
        return Matrix(n_rows, n_cols);
    }
}


Matrix Matrix::operator-(const Matrix& other) const
{
    if (n_rows == other.n_rows && n_cols == other.n_cols) {
        auto C = vector<vector<double>>(n_rows, vector<double>(n_cols));
        for (int i = 0; i < n_rows; i++) {
            for (int j = 0; j < n_cols; j++) {
                C[i][j] = this->M[i][j] - other.M[i][j];
            }
        }
        return Matrix(C);
    } else {
        return Matrix(n_rows, n_cols);
    }
}


Matrix Matrix::operator*(const double& lambda) const
{
    auto C = vector<vector<double>>(n_rows, vector<double>(n_cols));
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            C[i][j] = lambda * M[i][j];
        }
    }
    return Matrix(C);
}


Matrix Matrix::operator/(const double& lambda) const
{
    if (lambda != 0) {
        auto C = vector<vector<double>>(n_rows, vector<double>(n_cols));
        for (int i = 0; i < n_rows; i++) {
            for (int j = 0; j < n_cols; j++) {
                C[i][j] = M[i][j] / lambda;
            }
        }
        return Matrix(C);
    } else {
        return Matrix(n_rows, n_cols);
    }
}


Matrix Matrix::operator*(const Matrix& other) const
{
    if (n_cols == other.n_rows) {
        auto C = vector<vector<double>>(n_rows, vector<double>(other.n_cols));
        for (int i = 0; i < n_rows; i++) {
            for (int j = 0; j < other.n_cols; j++) {
                double c_ij = 0;
                for (int k = 0; k < n_cols; k++) {
                    c_ij += this->M[i][k] * other.M[k][j];
                }
                C[i][j] = c_ij;
            }
        }
        return Matrix(C);
    } else {
        return Matrix(n_rows, n_cols);
    }
}


// matrix bool operators
bool Matrix::operator==(const Matrix& other)
{
    if (n_rows == other.n_rows && n_cols && other.n_cols) {
        bool all = true;
        for (int i = 0; i < n_rows; i++) {
            for (int j = 0; j < n_cols; j++) {
                all = all && (M[i][j] == other.M[i][j]);
            }
        }
        return all;
    } else {
        return false;
    }
}


bool Matrix::is_square() const
{
    return (n_rows == n_cols);
}


bool Matrix::is_symetric() const
{
    if (is_square()) {
        bool all = true;
        for (int i = 1; i < n_rows; i++) {
            for (int j = i; j < n_cols; j++) {
                all = all && (M[i][j] == M[j][i]);
            }
        }
        return all;
    } else {
        return false;
    }
}


bool Matrix::is_upper_triangular(const double& threshold) const
{
    if (is_square()) {
        bool all = true;
        for (int i = 1; i < n_rows; i++) {
            for (int j = 0; j < i; j++) {
                all = all && (M[i][j] < threshold) && (M[i][j] > -threshold);
            }
        }
        return all;
    } else {
        return false;
    }
}


bool Matrix::is_lower_triangular(const double& threshold) const
{
    if (is_square()) {
        bool all = true;
        for (int i = 0; i < n_rows; i++) {
            for (int j = i+1; j < n_cols; j++) {
                all = all && (M[i][j] < threshold) && (M[i][j] > -threshold);
            }
        }
        return all;
    } else {
        return false;
    }
}


// other operators
Matrix Matrix::transpose() const
{
    auto C = vector<vector<double>>(n_cols, vector<double>(n_rows));
    for (int j = 0; j < n_cols; j++) {
        for (int i = 0; i < n_rows; i++) {
            C[j][i] = M[i][j];
        }
    }
    return Matrix(C);
}


Matrix operator*(const double lambda, const Matrix& M) {
    unsigned int m = M.get_n_rows(), n = M.get_n_cols();
    auto C = vector<vector<double>>(m, vector<double>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = lambda * M.get_element(i, j);
        }
    }
    return Matrix(C);
}


// external operators
ostream& operator<<(ostream& os, const Matrix& M) {
    for (int i = 0; i < M.get_n_rows(); i++) {
        for (int j = 0; j < M.get_n_cols(); j++) {
            os << M.get_element(i, j) << " ";
        }
        os << endl;
    }
    return os;
}

// getters
Matrix Matrix::get_vector (unsigned int position, vec direction) const
{
    if (direction == vec::row) {
        auto result = vector<vector<double>>(1, M[position]);
        return Matrix(result);
    } else if (direction == vec::column ) {
        auto result = vector<vector<double>>(n_rows, vector<double>(1));
        for (int i = 0; i < n_rows; i++) {
            result[i][0] = M[i][position];
        }
        return Matrix(result);
    } else {
        return Matrix(n_rows, n_cols, fill::zeros);
    }
}



/***** MATRIX FACTORY *****/
Matrix MatrixFactory::Custom(vector<vector<double>>& matrix)
{
    return Matrix(matrix);
}


Matrix MatrixFactory::Zeros(const unsigned int m, const unsigned int n)
{
    int n_ = (n==0) ? m : n;
    return Matrix(m, n_, Matrix::fill::zeros);
}


Matrix MatrixFactory::Ones(const unsigned int m, const unsigned int n )
{
    int n_ = (n==0) ? m : n;
    return Matrix(m, n_, Matrix::fill::ones);
}


Matrix MatrixFactory::Eye(const unsigned int m, const unsigned int n)
{
    int n_ = (n==0) ? m : n;
    return Matrix(m, n_, Matrix::fill::eye);
}


Matrix MatrixFactory::Resize(const Matrix& M, unsigned int m, unsigned int n)
{
    auto C = vector<vector<double>>(m, vector<double>(n));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = M.get_element(i, j);
        }
    }
    return MatrixFactory::Custom(C);
}


Matrix MatrixFactory::FromVec(const vector<Matrix>& vecs) {
    unsigned int m = vecs[0].get_n_rows(), n = vecs[0].get_n_cols();
    if (m == 1) { // Row Vectors
        auto C = vector<vector<double>>(vecs.size(), vector<double>(n));
        for (int i = 0; i < vecs.size(); i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = vecs[i].get_element(0, j);
            }
        }
        return MatrixFactory::Custom(C);
    } else { // Column Vectors
        auto C = vector<vector<double>>(m, vector<double>(vecs.size()));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < vecs.size(); j++) {
                C[i][j] = vecs[j].get_element(i, 0);
            }
        }
        return MatrixFactory::Custom(C);
    }
}


Matrix MatrixFactory::Kronecker(const unsigned int m,
                                const unsigned int n,
                                const unsigned int i,
                                const unsigned int j)
{
    auto C = vector<vector<double>>(m, vector<double>(n, 0));
    C[i][j] = 1;
    return MatrixFactory::Custom(C);
}


// Matrix Random();



/***** VECTOR FACTORY *****/

// Column Vector Factory //
Matrix VectorFactory::Column::Custom(vector<double>& vec)
{
    int n = vec.size();
    auto C = vector<vector<double>>(n, vector<double>(1));
    for (int i = 0; i < n; i++) {
        C[i][0] = vec[i];
    }
    return MatrixFactory::Custom(C);
}


Matrix VectorFactory::Column::Zeros(const unsigned int n)
{
    return MatrixFactory::Zeros(n, 1);
}


Matrix VectorFactory::Column::Ones(const unsigned int n)
{
    return MatrixFactory::Ones(n, 1);
}


Matrix VectorFactory::Column::E(const unsigned int n, const unsigned int i)
{
    return MatrixFactory::Kronecker(n, 1, i, 0);
}


// ROW VECTOR FACTORY
Matrix VectorFactory::Row::Custom(vector<double>& vec)
{
    auto C = vector<vector<double>>(1, vec);
    return MatrixFactory::Custom(C);
}


Matrix VectorFactory::Row::Zeros(const unsigned int n)
{
    return MatrixFactory::Zeros(1, n);
}


Matrix VectorFactory::Row::Ones(const unsigned int n)
{
    return MatrixFactory::Ones(1, n);
}


Matrix VectorFactory::Row::E(const unsigned int n, const unsigned int j)
{
    return MatrixFactory::Kronecker(1, n, 1, j);
}
