"""Expected returns module."""

from deepfolio.moments.expected_returns._base import (
    BaseMu,
)
from deepfolio.moments.expected_returns._expected_returns import (
    EWMu,
    EmpiricalMu,
    EquilibriumMu,
    ShrunkMu,
    ShrunkMuMethods,
)

__all__ = [
    "BaseMu",
    "EmpiricalMu",
    "EWMu",
    "ShrunkMu",
    "EquilibriumMu",
    "ShrunkMuMethods",
]
