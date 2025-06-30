# DeepFolio

DeepFolio is a Quadratic Programming-based Python library for large-scale portfolio optimization.

It implements a unified QP framework with an efficient OSQP-ADMM solver (featuring sparse LDL caching and warm starts), and provides full support for real-world constraints such as long/short limits, turnover bounds, and factor neutrality. DeepFolio pioneers ℓ₁+ℓ₂² regularization on mapped factor weights and integrates cutting-edge covariance estimators (AP-Trees, IPCA, RP-PCA, etc.), enabling single-core, high-precision optimization for portfolios with hundreds of assets across multiple rolling-window backtests.

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

# 1. Data loading and preprocessing
pipe = Pipeline(hooks=[Pipeline.pct_return])
prices = pipe.load('prices.csv')  # Load your price data (CSV with datetime index and asset columns)
returns = prices.values           # Convert to numpy array

# 2. Build the model
model = PortfolioTransformer(n_assets=returns.shape[1])

# 3. Train the model with multiple objectives (e.g., maximize Sharpe, minimize CVaR)
trainer = MultiLossTrainer(model=model, losses=['sharpe', 'cvar'])
trainer.fit(returns, epochs=100, batch_size=32)

# 4. Generate portfolio weights for new data
weights = model.predict(returns[-20:])  # Predict weights for the last 20 periods

# 5. Backtest the strategy
backtester = Backtester(model)
results = backtester.run(returns)

# 6. Analyze results
```

## License

MIT
