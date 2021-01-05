//
// Created by Quentin Glangetas [pro] on 1/5/21.
//

#ifndef LEASTSQUARES_DATA_READER_H
#define LEASTSQUARES_DATA_READER_H

#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>


class DataReader {
public:

    explicit DataReader(std::string&);

    // getters
    int get_n_data() const { return n_data; }
    int get_n_dim() const { return n_dim; }
    double get_vol() const { return vol; }
    std::vector<double> get_coefficients() { return beta_0; }
    std::pair<std::vector<double>, std::vector<std::vector<double>>> get_data() { return make_pair(Y, X); };

private:

    // DATA
    int n_data, n_dim;
    double vol;
    std::vector<double> beta_0;
    std::vector<double> Y;
    std::vector<std::vector<double>> X;
};

#endif //LEASTSQUARES_DATA_READER_H
