# coding:utf-8
#!/usr/bin/python
#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#
# -------------------------------------------------------------------------
"""Treat IDE tool integrations as a package

    < DCCsi >/Tools/IDE/__init__.py

:Status: Prototype
:Version: 0.0.1
"""
# -------------------------------------------------------------------------
# standard imports
import os
import site
from pathlib import Path
import logging as _logging
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# global scope
_PACKAGENAME = 'DCCsi.Tools.IDE'

__all__ = ['WingIDE']
           # 'PyCharm',
           # 'VScode']  # to do: add others when they are set up

_LOGGER = _logging.getLogger(_PACKAGENAME)
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# set up access to this DCC folder as a pkg
_MODULE_PATH = Path(__file__)
_LOGGER.debug(f'_MODULE_PATH: {_MODULE_PATH}')

# last two package paths, follow the turtles all the way down
from DccScriptingInterface.Tools import PATH_DCCSIG
from DccScriptingInterface.Tools import PATH_DCCSI_TOOLS
from DccScriptingInterface.globals import *

from DccScriptingInterface.constants import ENVAR_PATH_DCCSI_TOOLS_IDE

# the path to this < dccsi >/Tools/IDE pkg
PATH_DCCSI_TOOLS_IDE = Path(_MODULE_PATH.parent)

PATH_DCCSI_TOOLS_IDE = Path(os.getenv(ENVAR_PATH_DCCSI_TOOLS_IDE,
                                       PATH_DCCSI_TOOLS_IDE.as_posix()))
site.addsitedir(PATH_DCCSI_TOOLS_IDE.as_posix())
_LOGGER.debug(f'{ENVAR_PATH_DCCSI_TOOLS_IDE}: {PATH_DCCSI_TOOLS_IDE}')
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
from azpy.config_utils import attach_debugger
from azpy import test_imports

# suggestion would be to turn this into a method to reduce boilerplate
# but where to put it that makes sense?
if DCCSI_DEV_MODE:
    # if dev mode, this will attemp to auto-attach the debugger
    # at the earliest possible point in this module
    attach_debugger(debugger_type=DCCSI_GDEBUGGER)

    _LOGGER.debug(f'Testing Imports from {_PACKAGENAME}')

    # If in dev mode and test is flagged this will force imports of __all__
    # although slower and verbose, this can help detect cyclical import
    # failure and other issues

    # the DCCSI_TESTS flag needs to be properly added in .bat env
    if DCCSI_TESTS:
        test_imports(_all=__all__,
                     _pkg=_PACKAGENAME,
                     _logger=_LOGGER)
# -------------------------------------------------------------------------
