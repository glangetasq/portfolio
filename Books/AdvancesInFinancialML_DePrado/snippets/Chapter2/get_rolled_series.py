
import pandas as pd

# Local Imports
from .roll_gaps import roll_gaps


def get_rolled_series(path_in, key):

    series = pd.read_hdf(path_in, key = '/bars/ES_10k')
    series['Time'] = pd.to_datetime(series['Time'], format="%Y%m%d%H%M%S%f")
    series = series.set_index('Time')

    gaps = roll_gaps(series)

    for fld in ['Close', 'VWAP']:
        series[fld] -= gaps

    return series
