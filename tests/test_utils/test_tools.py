from collections.abc import Iterator

import numpy as np
from deepfolio.utils.tools import (
    args_names,
    bisection,
    deduplicate_names,
    default_asset_names,
    format_measure,
    input_to_array,
    safe_indexing,
    safe_split,
)


# Generated by CodiumAI
class TestArgsNames:
    #  Returns a list of argument names for a given function.
    def test_returns_argument_names(self):
        # Define a function with arguments
        def my_function(arg1, arg2, arg3):
            pass

        # Call the args_names function
        result = args_names(my_function)

        # Check if the result is a list
        assert isinstance(result, list)

        # Check if the result contains the correct argument names
        assert result == ["arg1", "arg2", "arg3"]


# Generated by CodiumAI

import pytest


class TestInputToArray:
    #  Convert a dictionary with asset names and values to a numpy array of shape (n_assets) when dim=1.
    def test_convert_dict_to_array_dim_1(self):
        items = {"asset1": 1, "asset2": 2, "asset3": 3}
        n_assets = 3
        fill_value = 0
        dim = 1
        assets_names = np.array(["asset1", "asset2", "asset3"])
        name = "items"

        expected_result = np.array([1, 2, 3])

        result = input_to_array(items, n_assets, fill_value, dim, assets_names, name)

        assert np.array_equal(result, expected_result)

    #  Raise a ValueError if items is a dictionary and assets_names is not provided.
    def test_raise_value_error_no_assets_names(self):
        items = {"asset1": 1, "asset2": 2, "asset3": 3}
        n_assets = 3
        fill_value = 0
        dim = 1
        assets_names = None
        name = "items"

        with pytest.raises(ValueError):
            input_to_array(items, n_assets, fill_value, dim, assets_names, name)


# Generated by CodiumAI
class TestFormatMeasure:
    #  Formats a positive float number without decimal places correctly.
    def test_positive_float_no_decimal(self):
        result = format_measure(10.0)
        assert result == "10.00"

    #  Formats a float number with the maximum number of decimal places correctly.
    def test_float_maximum_decimal(self):
        result = format_measure(3.141592653589793)
        assert result == "3.14"

    #  Formats a float number with the minimum number of decimal places correctly.
    def test_float_minimum_decimal(self):
        result = format_measure(0.123456)
        assert result == "0.12"


# Generated by CodiumAI
class TestBisection:
    #  The function receives a list of numpy arrays and returns an iterator.
    def test_returns_iterator(self):
        arr = [np.array([1, 2, 3]), np.array([4, 5, 6]), np.array([7, 8, 9])]
        result = bisection(arr)
        assert isinstance(result, Iterator)

    #  The function works correctly for empty arrays.
    def test_empty_arrays(self):
        arr = []
        result = list(bisection(arr))
        assert result == []

    #  The function works correctly for arrays with only one element.
    def test_single_element_array(self):
        arr = [np.array([1])]
        result = list(bisection(arr))
        assert result == []


# Generated by CodiumAI
class TestSafeIndexing:
    #  Returns the entire data if indices is None.
    def test_returns_entire_data_if_indices_is_none(self):
        X = np.array([1, 2, 3, 4, 5])
        indices = None
        result = safe_indexing(X, indices)
        assert np.array_equal(result, X)


# Generated by CodiumAI
class TestSafeSplit:
    #  Returns X_subset and y_subset when given valid inputs.
    def test_valid_inputs(self):
        # Arrange
        X = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
        y = np.array([1, 2, 3])
        indices = np.array([0, 2])
        axis = 0

        # Act
        X_subset, y_subset = safe_split(X, y, indices=indices, axis=axis)

        # Assert
        np.testing.assert_array_equal(X_subset, np.array([[1, 2, 3], [7, 8, 9]]))
        np.testing.assert_array_equal(y_subset, np.array([1, 3]))


# Generated by CodiumAI

import pytest


class TestDefaultAssetNames:
    #  Returns an ndarray of str with length equal to n_assets.
    def test_returns_ndarray_with_length_equal_to_n_assets(self):
        n_assets = 5
        result = default_asset_names(n_assets)
        assert isinstance(result, np.ndarray)
        assert len(result) == n_assets

    #  Raises TypeError when n_assets is not an integer.
    def test_raises_type_error_when_n_assets_is_not_an_integer(self):
        n_assets = "5"
        with pytest.raises(TypeError):
            default_asset_names(n_assets)


def test_deduplicate_names():
    names = ["blah", "blah2", "blah3", "blah", "blah"]
    names = deduplicate_names(names)
    assert names == ["blah", "blah2", "blah3", "blah_1", "blah_2"]
