# OpenLPA

**OpenLPA** (Open-source Liquidity Provision Analytics) is a Python library for analyzing the behavior and quality of liquidity providers (LPs) in electronic trading. Inspired by institutional platforms such as BidFX LPA, this project empowers traders, quants, and researchers with tools to evaluate LP behavior, optimize routing decisions, and support transaction cost analysis (TCA).

---

## 🔍 Features

- ⏱️ **Latency & Quote Behavior Analysis**  
  Measure RFQ/ESP response times, quote cancellation patterns, and quote duration.

- 📈 **Fill Probability and Slippage Attribution**  
  Quantify true liquidity based on actual trade outcomes.

- 🧠 **LP Scoring System**  
  Generate LP quality scores by aggregating multiple behavioral indicators.

- 📊 **Interactive Dashboard (Streamlit)**  
  Upload quotes/trades and visualize LP performance dynamically.

- 🧬 **Behavioral Modeling**  
  Extract time-series LP features for clustering and anomaly detection.

- ⚖️ **Causal Inference (DoWhy)**  
  Estimate causal impact of LP selection on execution outcomes.

- 🤖 **Adaptive LP Routing (MAB)**  
  Use multi-armed bandit algorithms to learn and optimize LP selection.

---

## 🆚 OpenLPA vs Traditional TCA

While traditional Transaction Cost Analysis (TCA) primarily focuses on post-trade outcomes such as slippage, OpenLPA goes one step further by incorporating the behavioral dynamics of liquidity providers into the analysis pipeline.

| Feature | Traditional TCA | OpenLPA |
|--------|------------------|---------|
| Focus | Execution result | Execution process + behavior |
| Metrics | Slippage, cost | Latency, fill ratio, quote stability |
| Counterparty Modeling | None | LP-level behavioral scoring |
| Causal Analysis | Rare | Integrated (DoWhy) |
| Optimization | Static benchmarks | Adaptive LP selection (MAB) |
| Real-Time Application | Limited | Supported via dashboard + routing logic |

By integrating microstructure behavior modeling, causal inference, and adaptive learning, OpenLPA enables smarter routing, better transparency, and a more complete picture of liquidity quality.

---

## 📦 Installation

```bash
pip install openlpa
```

---

## 🚀 Quick Start

### 1. LP Behavior Scoring

```python
from core.lp_evaluator import LPEvaluator
from io.data_loader import load_quotes, load_trades

quotes = load_quotes("data/quotes.csv")
trades = load_trades("data/trades.csv")

evaluator = LPEvaluator(quotes, trades)
scores = evaluator.score_liquidity_providers()
print(scores.head())
```

---

### 2. Slippage Analysis

```python
from core.tca import calculate_slippage, aggregate_slippage_by_lp

trades_slippage = calculate_slippage(trades, benchmark_col="arrival_price")
lp_slip = aggregate_slippage_by_lp(trades_slippage)
print(lp_slip)
```

---

### 3. LP Behavior Modeling (Time-Series)

```python
from core.behavior_model import extract_behavior_features

behavior_features = extract_behavior_features(quotes, trades, window="1h")
print(behavior_features.head())
```

---

### 4. Causal Inference with DoWhy

```python
from core.causal_analysis import estimate_treatment_effect

# Merge LP usage and slippage data with controls
effect = estimate_treatment_effect(lp_usage_df, slippage_df)
print("Estimated Causal Effect:", effect)
```

---

### 5. LP Routing via Multi-Armed Bandit

```python
from core.lp_router import LPRouter

router = LPRouter(arms=["LP1", "LP2", "LP3"])
router.fit(["LP1", "LP2", "LP1"], [0.8, 0.5, 0.9])
print("Recommended LP:", router.select_lp())
```

---

### 6. Interactive Dashboard

```bash
streamlit run streamlit_app/app.py
# or the advanced version:
streamlit run streamlit_app/intelligence.py
```

---

## 📘 Use Cases

| Market | Applications |
|--------|--------------|
| FX     | RFQ/ESP latency tracking, LP ranking, quote-to-fill gap |
| Equities | Venue performance analysis, ATS/SDP routing |
| Crypto | CEX/DEX LP clustering, anomaly detection |
| Fixed Income | RFQ stability, best execution validation |

---

## 🔮 Roadmap

- [x] LP behavioral time-series modeling
- [x] Causal inference via DoWhy
- [x] Online learning with multi-armed bandits
- [ ] Reinforcement learning agent for dynamic LP selection
- [ ] Graph-based LP modeling (GNN)
- [ ] Market simulator integration (e.g., MARS, DeepMarket)

---

## 🧑‍💻 Contributing

We welcome feedback, pull requests, and discussions! Please open issues or submit improvements via PR.

---

## 📄 License

Licensed under the Apache License, Version 2.0.
