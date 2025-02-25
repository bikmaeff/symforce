# -----------------------------------------------------------------------------
# This file was autogenerated by symforce from template:
#     python_templates/ops/CLASS/lie_group_ops.py.jinja
# Do NOT modify by hand.
# -----------------------------------------------------------------------------

import math
import numpy
import typing as T

import sym  # pylint: disable=unused-import


class LieGroupOps(object):
    """
    Python LieGroupOps implementation for <class 'symforce.geo.pose3.Pose3'>.
    """

    @staticmethod
    def from_tangent(vec, epsilon):
        # type: (T.Sequence[float], float) -> sym.Pose3

        # Total ops: 15

        # Input arrays

        # Intermediate terms (3)
        _tmp0 = math.sqrt(epsilon ** 2 + vec[0] ** 2 + vec[1] ** 2 + vec[2] ** 2)
        _tmp1 = (1.0 / 2.0) * _tmp0
        _tmp2 = math.sin(_tmp1) / _tmp0

        # Output terms
        _res = [0.0] * 7
        _res[0] = _tmp2 * vec[0]
        _res[1] = _tmp2 * vec[1]
        _res[2] = _tmp2 * vec[2]
        _res[3] = math.cos(_tmp1)
        _res[4] = vec[3]
        _res[5] = vec[4]
        _res[6] = vec[5]
        return sym.Pose3.from_storage(_res)

    @staticmethod
    def to_tangent(a, epsilon):
        # type: (sym.Pose3, float) -> T.List[float]

        # Total ops: 17

        # Input arrays
        _a = a.data

        # Intermediate terms (2)
        _tmp0 = min(abs(_a[3]), 1 - epsilon)
        _tmp1 = (
            2
            * (2 * min(0, (0.0 if _a[3] == 0 else math.copysign(1, _a[3]))) + 1)
            * math.acos(_tmp0)
            / math.sqrt(1 - _tmp0 ** 2)
        )

        # Output terms
        _res = [0.0] * 6
        _res[0] = _a[0] * _tmp1
        _res[1] = _a[1] * _tmp1
        _res[2] = _a[2] * _tmp1
        _res[3] = _a[4]
        _res[4] = _a[5]
        _res[5] = _a[6]
        return _res

    @staticmethod
    def retract(a, vec, epsilon):
        # type: (sym.Pose3, T.Sequence[float], float) -> sym.Pose3

        # Total ops: 47

        # Input arrays
        _a = a.data

        # Intermediate terms (8)
        _tmp0 = math.sqrt(epsilon ** 2 + vec[0] ** 2 + vec[1] ** 2 + vec[2] ** 2)
        _tmp1 = (1.0 / 2.0) * _tmp0
        _tmp2 = math.sin(_tmp1) / _tmp0
        _tmp3 = _tmp2 * vec[1]
        _tmp4 = _tmp2 * vec[2]
        _tmp5 = _tmp2 * vec[0]
        _tmp6 = math.cos(_tmp1)
        _tmp7 = _a[0] * _tmp2

        # Output terms
        _res = [0.0] * 7
        _res[0] = _a[0] * _tmp6 + _a[1] * _tmp4 - _a[2] * _tmp3 + _a[3] * _tmp5
        _res[1] = _a[1] * _tmp6 + _a[2] * _tmp5 + _a[3] * _tmp3 - _tmp7 * vec[2]
        _res[2] = -_a[1] * _tmp5 + _a[2] * _tmp6 + _a[3] * _tmp4 + _tmp7 * vec[1]
        _res[3] = -_a[1] * _tmp3 - _a[2] * _tmp4 + _a[3] * _tmp6 - _tmp7 * vec[0]
        _res[4] = _a[4] + vec[3]
        _res[5] = _a[5] + vec[4]
        _res[6] = _a[6] + vec[5]
        return sym.Pose3.from_storage(_res)

    @staticmethod
    def local_coordinates(a, b, epsilon):
        # type: (sym.Pose3, sym.Pose3, float) -> T.List[float]

        # Total ops: 50

        # Input arrays
        _a = a.data
        _b = b.data

        # Intermediate terms (4)
        _tmp0 = -_a[0] * _b[0] - _a[1] * _b[1] - _a[2] * _b[2]
        _tmp1 = _a[3] * _b[3]
        _tmp2 = min(1 - epsilon, abs(_tmp0 - _tmp1))
        _tmp3 = (
            2
            * (2 * min(0, (0.0 if -_tmp0 + _tmp1 == 0 else math.copysign(1, -_tmp0 + _tmp1))) + 1)
            * math.acos(_tmp2)
            / math.sqrt(1 - _tmp2 ** 2)
        )

        # Output terms
        _res = [0.0] * 6
        _res[0] = _tmp3 * (-_a[0] * _b[3] - _a[1] * _b[2] + _a[2] * _b[1] + _a[3] * _b[0])
        _res[1] = _tmp3 * (_a[0] * _b[2] - _a[1] * _b[3] - _a[2] * _b[0] + _a[3] * _b[1])
        _res[2] = _tmp3 * (-_a[0] * _b[1] + _a[1] * _b[0] - _a[2] * _b[3] + _a[3] * _b[2])
        _res[3] = -_a[4] + _b[4]
        _res[4] = -_a[5] + _b[5]
        _res[5] = -_a[6] + _b[6]
        return _res
