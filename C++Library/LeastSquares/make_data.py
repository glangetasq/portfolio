import argparse
import numpy as np
import csv

def make_data(n, p, vol):

    beta_0 = np.random.randint(-100, 101, p) / 10

    X = []

    for j in range(p):

        X.append(
                10 * np.random.normal(0, 1, n) 
        )

    X = np.array(X).T

    Y = X.dot(beta_0) + np.random.normal(0, vol, n)

    return beta_0, Y, X



if __name__ == "__main__":

    parser = argparse.ArgumentParser()

    parser.add_argument("path")
    parser.add_argument("n_data")
    parser.add_argument("n_dim")
    parser.add_argument("vol")

    args = parser.parse_args()

    path = args.path
    n_data, n_dim = int(args.n_data), int(args.n_dim)
    vol = float(args.vol)

    beta_0, Y, X = make_data(n_data, n_dim, vol)

    with open(path, 'w') as file:

        writer = csv.writer(file)

        # First row: n, p and vol
        writer.writerow([n_data, n_dim, vol])

        # Second row: true parameters
        writer.writerow(beta_0)

        # Then, data points Y | X1 | X2 | ... | Xp
        for i in range(n_data):
            row = [Y[i]] + [ X[i, j] for j in range(n_dim) ]
            writer.writerow(row)
    


