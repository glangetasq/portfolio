
def roll_gaps(series,
    dict_ = {'Instrument' : 'FUT_CUR_GEN_TICKER',
             'Open' : 'PX_OPEN'
            },
    math_end = True):

    # Compute gaps at each roll between previous close and next open
    roll_dates = series[dict_['Instrument']].drop_duplicates(keep='first').index

    gaps = series[dict_['Close']] * 0
    iloc = list(series.index)
    iloc = [iloc.index(i) - 1 for i in roll_dates] # index of days prior to roll

    gaps.loc[roll_dates[1:]] = series[dict_['Open']].loc[roll_dates[1:]]
    gaps -= series[dict_['Close']].iloc[iloc[1:]].values
    gaps = gaps.cumsum()

    if match_end:
        gaps -= gaps.iloc[-1] # roll backward

    return gaps
