# ----------------------------------------------------------------------------
# SymForce - Copyright 2022, Skydio, Inc.
# This source code is under the Apache 2.0 license found in the LICENSE file.
# ----------------------------------------------------------------------------

import unittest
import numpy as np

from symforce import typing as T
from symforce import geo
from symforce import ops
from symforce.test_util import TestCase
from symforce.test_util.lie_group_ops_test_mixin import LieGroupOpsTestMixin


class LieGroupNdarrayTest(LieGroupOpsTestMixin, TestCase):
    """
    Test that ndarrays function as a LieGroup
    Note the mixin that tests all storage, group, and lie group ops.
    """

    @classmethod
    def element(cls) -> np.ndarray:
        return np.array([[1, 2, 3], [4, 5, 6]], dtype=T.Scalar)

    def test_storage_order_matches_geo_matrix(self) -> None:
        """
        Test that the storage order of ndarrays matches that of geo.Matrix
        """
        m = geo.M33()
        a = np.zeros((3, 3))

        i = 0.0
        for row in range(3):
            for col in range(3):
                m[row, col] = i
                a[row, col] = i
                i += 1

        self.assertEqual(ops.StorageOps.to_storage(a), m.to_storage())


if __name__ == "__main__":
    TestCase.main()
