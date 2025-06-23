from enum import Enum

class SolverBackend(Enum):
    SOFTMAX = "softmax"
    TORCHOPT_QP = "torchopt_qp"

def solve_qp(*args, **kwargs):
    # TODO: implement
    pass
