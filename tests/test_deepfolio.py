import pytest
import deepfolio

def test_version():
    assert hasattr(deepfolio, '__version__')
