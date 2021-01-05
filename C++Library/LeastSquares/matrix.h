//
// Created by Quentin Glangetas [pro] on 1/4/21.
//

#ifndef LEASTSQUARES_MATRIX_H
#define LEASTSQUARES_MATRIX_H

#include <iostream>
#include <vector>

class Matrix {
public:
    enum fill { zeros, ones, eye };
    enum vec { column, row };

    // constructors
    Matrix() {};
    Matrix(unsigned int, unsigned int, fill = fill::zeros);
    explicit Matrix(std::vector<std::vector<double>>& M);

    // matrix operation operators
    Matrix operator+(const Matrix&) const;
    Matrix operator-(const Matrix&) const;
    Matrix operator*(const double&) const;
    Matrix operator/(const double&) const;
    Matrix operator*(const Matrix&) const;

    // matrix bool operators
    bool operator==(const Matrix&);
    bool is_square() const;
    bool is_symetric() const;
    bool is_upper_triangular(const double& = 1e-10) const;
    bool is_lower_triangular(const double& = 1e-10) const;

    // other matrix operators
    Matrix transpose() const;

    // external operators
    friend std::ostream& operator<<(std::ostream& os, const Matrix& M);

    // getters
    unsigned int get_n_rows() const { return n_rows; }
    unsigned int get_n_cols() const { return n_cols; }
    std::vector<std::vector<double>> get_content() { return M; }
    double get_element(unsigned int i, unsigned int j) const { return M[i][j]; }
    Matrix get_vector (unsigned int, vec = vec::column) const;

protected:
    unsigned int n_rows, n_cols;
    std::vector<std::vector<double>> M;
};

Matrix operator*(double lambda, const Matrix& M);
std::ostream& operator<<(std::ostream& os, const Matrix& M);


/***** MATRIX FACTORY *****/
struct MatrixFactory {
    static Matrix Custom(std::vector<std::vector<double>>&);
    static Matrix Zeros(unsigned int, unsigned int = 0);
    static Matrix Ones(unsigned int, unsigned int = 0);
    static Matrix Eye(unsigned int, unsigned int = 0);
    static Matrix Resize(const Matrix&, unsigned int, unsigned int);
    static Matrix FromVec(const std::vector<Matrix>& vecs);
    static Matrix Kronecker(unsigned int, unsigned int, unsigned int, unsigned int);
    // Matrix Random();
};


/***** VECTOR FACTORY *****/
struct VectorFactory {
    static struct Column {
        static Matrix Custom(std::vector<double>&);
        static Matrix Zeros(unsigned int);
        static Matrix Ones(unsigned int n);
        static Matrix E(unsigned int, unsigned int);
    } Column;
    static struct Row {
        static Matrix Custom(std::vector<double>&);
        static Matrix Zeros(unsigned int);
        static Matrix Ones(unsigned int);
        static Matrix E(unsigned int, unsigned int);
    } Row;
};

#endif //LEASTSQUARES_MATRIX_H
