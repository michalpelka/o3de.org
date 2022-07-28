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
"""! DccScriptingInterface:: constants.py

Commonly used global constants and default values.
"""
import os
import sys
from pathlib import Path
from os.path import expanduser
import logging as _logging
# -------------------------------------------------------------------------
_MODULENAME = 'DCCsi.constants'
_LOGGER = _logging.getLogger(_MODULENAME)
_LOGGER.debug(f'Initializing: {_MODULENAME}')
_MODULE_PATH = Path(__file__) # thos module should not be used as an entry
_PATH_DCCSIG = _MODULE_PATH.parents[0].resolve()
sys.path.append(_PATH_DCCSIG)
# -------------------------------------------------------------------------

# global constants here
# all the constants moved here, need to be removed from azpy.constants
# and then modules should be refactored to all pull from here

# ENVAR_ denotes a common key string

# resolves the windows progam install directory
ENVAR_PROGRAMFILES_X86 = 'PROGRAMFILES(X86)'
PATH_PROGRAMFILES_X86 = os.environ[ENVAR_PROGRAMFILES_X86]
# resolves the windows progam install directory
ENVAR_PROGRAMFILES_X64 = 'PROGRAMFILES'
PATH_PROGRAMFILES_X64 = os.environ[ENVAR_PROGRAMFILES_X64]

# resolves the os user directory
PATH_USER_HOME = expanduser("~")
_LOGGER.debug(f'user home: {PATH_USER_HOME}')
# special case, make sure didn't return <user>\documents
_user_home_parts = os.path.split(PATH_USER_HOME)

if str(_user_home_parts[1].lower()) == 'documents':
    PATH_USER_HOME = _user_home_parts[0]
    _LOGGER.debug(f'user home CORRECTED: {PATH_USER_HOME}')

# construct the o3de user home location
SLUG_O3DE_FOLDER = '.o3de'
# path string constructor
PATH_USER_O3DE = f'{PATH_USER_HOME}\\{SLUG_O3DE_FOLDER}'
# user home o3se registry
SLUG_DIR_REGISTRY = 'Registry'
# path string constructor
PATH_USER_O3DE_REGISTRY = f'{PATH_USER_O3DE}\\{SLUG_DIR_REGISTRY}'

# logging into the user home o3de cache (temporarily)
SLUG_DCCSI_SHORT = 'DCCsi'
PATH_DCCSI_LOG_PATH = (f'{PATH_USER_O3DE}\\Cache\\log' +
                       f'\\{SLUG_DCCSI_SHORT}' +
                       f'\\{SLUG_DCCSI_SHORT}.log')

# bootstrap site-packages by version
# it is suggested that in a future iteration, these are moved from
# a dccsi nested location, to a location in user home o3de

PATH_DCCSI_PYTHON_LIB = (f'{_PATH_DCCSIG.as_posix()}' +
                         f'\\3rdParty\\Python\\Lib' +
                         f'\\{sys.version_info[0]}.x' +
                         f'\\{sys.version_info[0]}.{sys.version_info[1]}.x' +
                         f'\\site-packages')

# Note: some constants may simply define and implicit part of a default
# all of the logic, such as dynamic configuration and settings (config.py)
# is actually soft-coded, which constant is the envar Key may be hard,
# however the setting derived from that envar is soft,
# and the defaults can be overridden

# envar to get/set the path for the DccScriptingInterface Gem (DCCSI)
ENVAR_PATH_DCCSIG = 'PATH_DCCSIG'

# enavar to get/set the < dccsi>/tools folder
ENVAR_PATH_DCCSI_TOOLS = 'PATH_DCCSI_TOOLS'

# enavar to get/set the < dccsi>/tools/IDE folder
ENVAR_PATH_DCCSI_TOOLS_IDE = 'PATH_DCCSI_TOOLS_IDE'

# envar to get/set bool for global DCCSI_GDEBUG behaviour
ENVAR_DCCSI_GDEBUG = 'DCCSI_GDEBUG'
# envar to get/set bool for developer mode (debugging)
ENVAR_DCCSI_DEV_MODE = 'DCCSI_DEV_MODE'
# envar to get/set the ide debugger str/slug (only 'WING' implemented)
ENVAR_DCCSI_GDEBUGGER = 'DCCSI_GDEBUGGER'
# envar to get/set int for global logging level
ENVAR_DCCSI_LOGLEVEL = 'DCCSI_LOGLEVEL'
# envar to get/set bool for running extra local tests
ENVAR_DCCSI_TESTS = 'DCCSI_TESTS'

# a str prefix for dynamic settings
DCCSI_DYNAMIC_PREFIX = 'DYNACONF'
# the common filename.ext for local/override settings file
DCCSI_SETTINGS_LOCAL_FILENAME = 'setting.local.json'

