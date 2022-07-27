#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

from test_impact import BaseTestImpact
from tiaf_logger import get_logger

logger = get_logger(__file__)


class PythonTestImpact(BaseTestImpact):

    _runtime_type = "python"
    _default_sequence_type = "regular"

    @property
    def default_sequence_type(self):
        return self._default_sequence_type
