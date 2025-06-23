import pandas as pd
from typing import List, Callable, Optional

class Pipeline:
    """Data pipeline: load, resample, feature hooks."""
    def __init__(self, freq: str = '1D', hooks: Optional[List[Callable]] = None):
        self.freq = freq
        self.hooks = hooks or []

    def load(self, path: str, date_col: str = 'Date') -> pd.DataFrame:
        df = pd.read_csv(path, parse_dates=[date_col]).set_index(date_col).sort_index()
        df = df.resample(self.freq).last()
        for h in self.hooks:
            df = h(df)
        return df

    @staticmethod
    def pct_return(df: pd.DataFrame) -> pd.DataFrame:
        return df.pct_change().dropna()
