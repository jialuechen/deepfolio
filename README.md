# DeepFolio

DeepFolio is an attention-driven portfolio optimization library that leverages deep learning and modern machine learning techniques for advanced asset allocation and risk management.

---

## Features

- **Flexible data pipeline**: Resampling, feature engineering, and custom hooks
- **Portfolio Transformer model**: Attention-based allocation for multiple assets
- **Multiple loss functions**: Sharpe ratio, CVaR, and more
- **Cost models**: Linear, Almgren-Chriss transaction cost modeling
- **Portfolio constraints**: Gross exposure, leverage cap, and more
- **Scenario augmentation**: Monte Carlo simulation and scenario generation
- **Integrated backtesting**: Performance monitoring and evaluation
- **Auto re-training & hyperparameter tuning**

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
