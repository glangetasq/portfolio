import numpy as np


def pca_weights(cov, risk_dist = None, risk_target=1.):

    # Follwing the riskAlloc distribution, match risk_target

    eVal, eVec = np.linalg.eigh(cov) # must be Hermitian
    indices = eVal.argsort()[::-1] # arguments for sorting eVal in descending order
    eVal, eVec = eVal[indices], eVec[:, indices]

    if risk_dist is None:
        risk_dist = np.zeros(cov.shape[0])
        risk_dist[-1] = 1.

    loads = risk_target * (risk_dist/eVal)**.5
    weights = np.dot(eVec, np.reshape(loads, (-1, 1)))

    # Verify risk_dist
    # ctr = (loads/risk_target)**2 * eVal

    return weights
