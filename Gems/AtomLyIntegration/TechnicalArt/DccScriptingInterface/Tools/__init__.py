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
"""! @brief
<DCCsi>/Tools/__init__.py

This init allows us to treat the Tools folder as a package.
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
_PACKAGENAME = 'Tools'
_LOGGER = _logging.getLogger(_PACKAGENAME)

__all__ = ['DCC',
           'Python']  # to do: add others when they are set up
          #'Foo',
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# we need to set up basic access to the DCCsi
_MODULE_PATH = Path(__file__)  # To Do: what if frozen?

# a suggestion it to make the DccScriptingInterface a package
# <DccScriptingInterface>/__init__.py and then
# from DccScriptingInterface import _PATH_DCCSIG

# then access azpy.constants to pull ENVAR key strings
# so they are not redefined in __init__ boilerplate

# for now, lifting those strings so they can be more easily moved later
ENVAR_PATH_DCCSI_TOOLS = 'PATH_DCCSI_TOOLS'

# another suggestion is that _PATH_DCCSI_TOOLS
# becomes PATH_DCCSI_TOOLS (remove the leading _)
# as these variables can propogate and do not need to be private

_PATH_DCCSI_TOOLS = Path(_MODULE_PATH.parent)
_PATH_DCCSI_TOOLS = Path(os.getenv(ENVAR_PATH_DCCSI_TOOLS,
                                   _PATH_DCCSI_TOOLS.as_posix()))
site.addsitedir(_PATH_DCCSI_TOOLS.as_posix())

ENVAR_PATH_DCCSIG = 'PATH_DCCSIG'

_PATH_DCCSIG = Path(_PATH_DCCSI_TOOLS.parent)
_PATH_DCCSIG = Path(os.getenv(ENVAR_PATH_DCCSIG,
                              _PATH_DCCSIG.as_posix()))
site.addsitedir(_PATH_DCCSIG.as_posix())
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# now we have access to the DCCsi code and azpy
from azpy.env_bool import env_bool
from azpy.constants import ENVAR_DCCSI_GDEBUG
from azpy.constants import ENVAR_DCCSI_DEV_MODE
from azpy.constants import ENVAR_DCCSI_LOGLEVEL
from azpy.constants import ENVAR_DCCSI_GDEBUGGER
from azpy.constants import FRMT_LOG_LONG
from azpy.config_utils import attach_debugger

#  global space
_DCCSI_GDEBUG = env_bool(ENVAR_DCCSI_GDEBUG, False)
_DCCSI_DEV_MODE = env_bool(ENVAR_DCCSI_DEV_MODE, False)
_DCCSI_GDEBUGGER = env_bool(ENVAR_DCCSI_GDEBUGGER, 'WING')

# suggestion make constants for known debugger type settings like
# STR_IDE_WING_TAG = 'WING'
# move this into <DccScriptingInterface>/__init__.py and propogate

# default loglevel to info unless set
_DCCSI_LOGLEVEL = int(env_bool(ENVAR_DCCSI_LOGLEVEL, _logging.INFO))
if _DCCSI_GDEBUG:
    # override loglevel if runnign debug
    _DCCSI_LOGLEVEL = _logging.DEBUG
    _logging.basicConfig(level=_DCCSI_LOGLEVEL,
                        format=FRMT_LOG_LONG,
                        datefmt='%m-%d %H:%M')
    _LOGGER = _logging.getLogger(_PACKAGENAME)
# -------------------------------------------------------------------------



# -------------------------------------------------------------------------
# message collection
_LOGGER.debug(f'Initializing: {_PACKAGENAME}')
_LOGGER.debug(f'_MODULE_PATH: {_MODULE_PATH}')
_LOGGER.debug(f'PATH_DCCSIG: {_PATH_DCCSIG}')
_LOGGER.debug(f'PATH_DCCSI_TOOLS: {_PATH_DCCSI_TOOLS}')
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
if _DCCSI_DEV_MODE:
    attach_debugger(debugger_type=_DCCSI_GDEBUGGER)

    from azpy.shared.utils.init import test_imports
    # If in dev mode this will test imports of __all__
    _LOGGER.debug(f'Testing Imports from {_PACKAGENAME}')
    test_imports(_all=__all__,_pkg=_PACKAGENAME,_logger=_LOGGER)
# -------------------------------------------------------------------------


###########################################################################
# Main Code Block, runs this script as main (testing)
# -------------------------------------------------------------------------
if __name__ == '__main__':
    """Run as main, perform debug and tests"""
    pass
