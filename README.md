# DeepFolio

An attention-driven portfolio optimization library leveraging deep learning and modern machine learning techniques for advanced asset allocation and risk management.

---

## Features

- Flexible data pipeline (resampling, feature engineering)
- Portfolio Transformer model for allocation
- Multiple loss functions: Sharpe ratio, CVaR, and more
- Cost models: Linear, Almgren-Chriss transaction cost
- Portfolio constraints: Gross exposure, leverage cap, etc.
- Scenario augmentation and Monte Carlo simulation
- Integrated backtesting and performance monitoring
- Auto re-training and hyperparameter tuning

---

## Installation

```bash
pip install deepfolio
```

## Quickstart

```python
from deepfolio import Pipeline, PortfolioTransformer, MultiLossTrainer, Backtester

pipe = Pipeline(hooks=[Pipeline.pct_return])
prices = pipe.load('prices.csv')
returns = prices.values

model = PortfolioTransformer(n_assets=returns.shape[1])
# ... etc
```

## License

MIT
