#include <iostream>
#include <stdexcept>

#include "linear_algebra.h"
#include "data_reader.h"
#include "ordinary_least_squares.h"


using namespace std;


int main() {

    string fileName = "../bigdata.csv";
    auto reader = DataReader(fileName);

    int n = reader.get_n_data(), p = reader.get_n_dim();
    auto beta_0 = reader.get_coefficients();
    auto YX = reader.get_data();

    auto Y = LinAlg::Vector::Column::Custom(YX.first);
    auto X = LinAlg::Matrix::Custom(YX.second);

    auto model = OLS();

    cout << "Beta_0 = 0.0" << endl;
    for (int j = 0; j < p+1; j++) {

        cout << "Beta_" << j+1 << " = ";
        cout << beta_0[j];
        cout << endl;

    }

    cout << endl << endl;

    model.fit(X, Y, true);


    return 0;
}