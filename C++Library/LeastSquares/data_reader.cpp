//
// Created by Quentin Glangetas [pro] on 1/5/21.
//

#include "data_reader.h"

using namespace std;

DataReader::DataReader(string& fileName) {

    ifstream file(fileName);

    // Make sure the file is open
    if (!file.is_open()) {
        throw runtime_error("Could not open file.");
    }

    string line, col;
    if (file.good()) {

        // First Line: n_data, n_dim, vol
        getline(file, line);

        // String stream from line
        stringstream ss1(line);

        if (getline(ss1, col, ',')) { stringstream(col) >> n_data; }
        if (getline(ss1, col, ',')) { stringstream(col) >> n_dim; }
        if (getline(ss1, col, ',')) { stringstream(col) >> vol; }

        // Second Line: true coefficients
        getline(file, line);
        stringstream ss2(line);
        double beta;

        while (getline(ss2, col, ',')) {
            stringstream(col) >> beta;
            beta_0.push_back(beta);
        }

    }

    Y = vector<double>(n_data, 0);
    X = vector<vector<double>>(n_data, vector<double>(n_dim, 0));

    // Read the data points Y, X_1, X_2, ..., X_p
    for (int i = 0; i < n_data; i++) {

        // Get line
        getline(file, line);

        // String stream from current line
        stringstream ss(line);

        // First is Y_i
        ss >> Y[i];

        // Then X_i1, ..., X_ip
        for (int j = 0; j < n_dim; j++) {
            if (ss.peek() == ',') ss.ignore();
            ss >> X[i][j];
        }

    }

}
