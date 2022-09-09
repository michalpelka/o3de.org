#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#
# -------------------------------------------------------------------------
"""! TThis init allows us to treat Blender setup as a DCCsi tools python package

:file: DccScriptingInterface\\Tools\\DCC\\Blender\\__init__.py
:Status: Prototype
:Version: 0.0.1
:Future: is unknown
:Notice:
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
from DccScriptingInterface.Tools.DCC import _PACKAGENAME
_PACKAGENAME = f'{_PACKAGENAME}.Blender'

__all__ = ['bootstrap',
           'config',
           'constants',
           'start']

_LOGGER = _logging.getLogger(_PACKAGENAME)
_LOGGER.debug('Initializing: {0}.'.format({_PACKAGENAME}))
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# set up access to this Blender folder as a pkg
_MODULE_PATH = Path(__file__)
_LOGGER.debug(f'_MODULE_PATH: {_MODULE_PATH}')

# last two parents
from DccScriptingInterface.Tools.DCC import PATH_DCCSI_TOOLS
from DccScriptingInterface.Tools.DCC import PATH_DCCSI_TOOLS_DCC
from DccScriptingInterface.globals import *
from DccScriptingInterface import add_site_dir

_DCCSI_TOOLS_BLENDER_PATH = Path(_MODULE_PATH.parent)
add_site_dir(_DCCSI_TOOLS_BLENDER_PATH.as_posix())

ENVAR_PATH_DCCSI_TOOLS_DCC_BLENDER = "PATH_DCCSI_TOOLS_DCC_BLENDER"

# the path to this < dccsi >/Tools/IDE pkg
PATH_DCCSI_TOOLS_DCC_BLENDER = Path(_MODULE_PATH.parent)
PATH_DCCSI_TOOLS_DCC_BLENDER = Path(os.getenv(ENVAR_PATH_DCCSI_TOOLS_DCC_BLENDER,
                                              PATH_DCCSI_TOOLS_DCC_BLENDER.as_posix()))
add_site_dir(PATH_DCCSI_TOOLS_DCC_BLENDER.as_posix())
_LOGGER.debug(f'{ENVAR_PATH_DCCSI_TOOLS_DCC_BLENDER}: {PATH_DCCSI_TOOLS_DCC_BLENDER}')
_LOGGER.debug(STR_CROSSBAR)
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# suggestion would be to turn this into a method to reduce boilerplate
# but where to put it that makes sense?
if DCCSI_DEV_MODE:
    _LOGGER.debug(f'Testing Imports from {_PACKAGENAME}')

    # If in dev mode and test is flagged this will force imports of __all__
    # although slower and verbose, this can help detect cyclical import
    # failure and other issues

    # the DCCSI_TESTS flag needs to be properly added in .bat env
    if DCCSI_TESTS:
        from DccScriptingInterface.azpy import test_imports
        test_imports(_all=__all__,
                     _pkg=_PACKAGENAME,
                     _logger=_LOGGER)
# -------------------------------------------------------------------------
