//
// Created by Quentin Glangetas [pro] on 1/5/21.
//

#include "abstract_least_squares.h"

using namespace std;


Matrix AbstractLeastSquares::add_ones(Matrix &X) {

    int n_rows = X.get_n_rows(), n_cols = X.get_n_cols();
    auto content = X.get_content();
    auto new_content = vector<vector<double>>(n_rows, vector<double>(n_cols+1, 1));

    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            new_content[i][j+1] = X.get_element(i, j);
        }
    }

    return MatrixFactory::Custom(new_content);

}