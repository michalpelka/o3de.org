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
Module Documentation:
    < DCCsi >:: Tools//DCC//Substance//config.py

This module manages the dynamic config and settings for boostrapping
Adobe Substance Designer with o3de inter-op, scripts, etc.

This like the core <DCCsi>/config.py is the use of Dynaconf:
1. Layered config and settings
2. Dervie or alter via logic
3. etc. (to do: expand on the benefits)

"""
# -------------------------------------------------------------------------
import timeit
_MODULE_START = timeit.default_timer()  # start tracking

# standard imports
import sys
import os
import site
import re
import inspect
import importlib.util
from pathlib import Path
import logging as _logging
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# global scope
_MODULENAME = 'Tools.DCC.Substance.config'
_LOGGER = _logging.getLogger(_MODULENAME)
_LOGGER.debug(f'Initializing: {_MODULENAME}')

_MODULE_PATH = Path(__file__)  # To Do: what if frozen?
_LOGGER.debug(f'_MODULE_PATH: {_MODULE_PATH.as_posix()}')

# This sets up basic code access to the DCCsi
# <o3de>/Gems/AtomLyIntegration/TechnicalArt/<DCCsi>
_PATH_DCCSIG = Path(_MODULE_PATH, '../../../..').resolve()
site.addsitedir(_PATH_DCCSIG.as_posix())

# set envar so DCCsi synthetic env bootstraps with it (config.py)
from azpy.constants import ENVAR_PATH_DCCSIG
os.environ[ENVAR_PATH_DCCSIG] = str(_PATH_DCCSIG.as_posix())
_LOGGER.debug(f'PATH_DCCSIG: {_PATH_DCCSIG.as_posix()}')

# now we have dccsi azpy api access
import azpy.config_utils

# these must be imported explicitly, they are not defined in __all__
from azpy.config_utils import ENVAR_DCCSI_GDEBUG
from azpy.config_utils import ENVAR_DCCSI_DEV_MODE
from azpy.config_utils import ENVAR_DCCSI_LOGLEVEL
from azpy.config_utils import ENVAR_DCCSI_GDEBUGGER
from azpy.config_utils import FRMT_LOG_LONG
from azpy.config_utils import STR_CROSSBAR

# defaults, can be overriden/forced here for development
# method 1: .bat file, <dccsi>
from azpy.env_bool import env_bool
_DCCSI_GDEBUG = env_bool(ENVAR_DCCSI_GDEBUG, False)
_DCCSI_DEV_MODE = env_bool(ENVAR_DCCSI_DEV_MODE, False)
_DCCSI_LOGLEVEL = env_bool(ENVAR_DCCSI_LOGLEVEL, _logging.INFO)
_DCCSI_GDEBUGGER = env_bool(ENVAR_DCCSI_GDEBUGGER, 'WING')

# this will boostrap access to the dccsi managed package dependancies
# <DCCsi>\3rdParty\Python\Lib\3.x\3.x.x (based on python version)
_PATH_DCCSI_PYTHON_LIB = azpy.config_utils.bootstrap_dccsi_py_libs()
site.addsitedir(_PATH_DCCSI_PYTHON_LIB.as_posix())
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# early debugging
if _DCCSI_DEV_MODE:
    azpy.config_utils.attach_debugger(_DCCSI_GDEBUGGER)

# This will import and retreive the core <dccsi>/config.py and settings
_DCCSI_CORE_CONFIG = azpy.config_utils.get_dccsi_config(_PATH_DCCSIG)

# now standalone we can validate the config, env, settings.
_SETTINGS = _DCCSI_CORE_CONFIG.get_config_settings(enable_o3de_python=False,
                                                  enable_o3de_pyside2=True,
                                                  set_env=True)
# we don't init the O3DE python env settings!
# that will cause conflicts with the DCC tools python!!!
# we are enabling the O3DE PySide2 (aka QtForPython) access
# to do: get o3de Qt running on a thread in blender:
# https://github.com/friedererdmann/blender_pyside2_example
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# global scope
# start locally prepping known default values for dyanmic environment settings
# these global variables are passed as defaults into methods within the module

# special, a global home for stashing PATHs for managed settings
global _DCCSI_SYS_PATH
_DCCSI_SYS_PATH = list()

# special, a global home for stashing PYTHONPATHs for managed settings
global _DCCSI_PYTHONPATH
_DCCSI_PYTHONPATH = list()

# special, stash local PYTHONPATHs in a non-managed way (won't end up in settings.local.json)
global _DCCSI_PYTHONPATH_EXCLUDE
_DCCSI_PYTHONPATH_EXCLUDE = list()

# this is a dict bucket to store none-managed settings (fully local to module)
global _DCCSI_LOCAL_SETTINGS
_DCCSI_LOCAL_SETTINGS = {}
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# grab imports from Substance\constants.py that we will use
from Tools.DCC.Substance.constants import ENVAR_DCCSI_TOOLS_SUBSTANCE
from Tools.DCC.Substance.constants import PATH_DCCSI_TOOLS_SUBSTANCE

from Tools.DCC.Substance.constants import ENVAR_PATH_DCCSI_TOOLS
from Tools.DCC.Substance.constants import PATH_PATH_DCCSI_TOOLS

from Tools.DCC.Substance.constants import ENVAR_DCCSI_SUBSTANCE_RESOURCES
from Tools.DCC.Substance.constants import PATH_DCCSI_SUBSTANCE_RESOURCES

from Tools.DCC.Substance.constants import ENVAR_DCCSI_SUBSTANCE_LOCATION
from Tools.DCC.Substance.constants import PATH_DCCSI_SUBSTANCE_LOCATION

from Tools.DCC.Substance.constants import ENVAR_DCCSI_SUBSTANCE_EXE
from Tools.DCC.Substance.constants import PATH_DCCSI_SUBSTANCE_EXE

from Tools.DCC.Substance.constants import ENVAR_DCCSI_SUBSTANCE_PYTHON
from Tools.DCC.Substance.constants import PATH_DCCSI_SUBSTANCE_PYTHON

from Tools.DCC.Substance.constants import ENVAR_DCCSI_SUBSTANCE_PY_EXE
from Tools.DCC.Substance.constants import PATH_DCCSI_SUBSTANCE_PY_EXE

from Tools.DCC.Substance.constants import ENVAR_DCCSI_PY_SUBSTANCE
from Tools.DCC.Substance.constants import PATH_DCCSI_PY_SUBSTANCE

from Tools.DCC.Substance.constants import ENVAR_DCCSI_SUBSTANCE_SET_CALLBACKS
from Tools.DCC.Substance.constants import DCCSI_SUBSTANCE_SET_CALLBACKS

from Tools.DCC.Substance.constants import ENVAR_DCCSI_SUBSTANCE_SCRIPTS
from Tools.DCC.Substance.constants import PATH_DCCSI_SUBSTANCE_SCRIPTS

from Tools.DCC.Substance.constants import ENVAR_DCCSI_SUBSTANCE_CFG_PATH
from Tools.DCC.Substance.constants import PATH_DCCSI_SUBSTANCE_CFG
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
def init_dccsi_substance(settings=_SETTINGS, set_env=True):
    # now we can extend the environment specific to Blender
    # start by grabbing the constants we want to work with as envars
    # import others

    time_start = timeit.default_timer()  # start tracking for perf

    # we don't do this often but we want to stash to global dict
    # global _DCCSI_LOCAL_SETTINGS # non-dynaconf managed settings

    # This extends the settings and environment with Subtance3d stuff
    os.environ[f"DYNACONF_{ENVAR_DCCSI_TOOLS_SUBSTANCE}"] = PATH_DCCSI_TOOLS_SUBSTANCE.as_posix()
    os.environ[f"DYNACONF_{ENVAR_PATH_DCCSI_TOOLS}"] = PATH_PATH_DCCSI_TOOLS.as_posix()
    os.environ[f"DYNACONF_{ENVAR_DCCSI_SUBSTANCE_RESOURCES}"] = PATH_DCCSI_SUBSTANCE_RESOURCES.as_posix()
    os.environ[f"DYNACONF_{ENVAR_DCCSI_SUBSTANCE_LOCATION}"] = PATH_DCCSI_SUBSTANCE_LOCATION.as_posix()
    os.environ[f"DYNACONF_{ENVAR_DCCSI_SUBSTANCE_EXE}"] = PATH_DCCSI_SUBSTANCE_EXE.as_posix()
    os.environ[f"DYNACONF_{ENVAR_DCCSI_SUBSTANCE_PYTHON}"] = PATH_DCCSI_SUBSTANCE_PYTHON.as_posix()
    os.environ[f"DYNACONF_{ENVAR_DCCSI_SUBSTANCE_PY_EXE}"] = PATH_DCCSI_SUBSTANCE_PY_EXE.as_posix()
    os.environ[f"DYNACONF_{ENVAR_DCCSI_PY_SUBSTANCE}"] = PATH_DCCSI_PY_SUBSTANCE.as_posix()
    os.environ[f"DYNACONF_{ENVAR_DCCSI_SUBSTANCE_SET_CALLBACKS}"] = DCCSI_SUBSTANCE_SET_CALLBACKS
    os.environ[f"DYNACONF_{ENVAR_DCCSI_SUBSTANCE_SCRIPTS}"] = PATH_DCCSI_SUBSTANCE_SCRIPTS.as_posix()
    os.environ[f"DYNACONF_{ENVAR_DCCSI_SUBSTANCE_CFG_PATH}"] = PATH_DCCSI_SUBSTANCE_CFG.as_posix()

    # now standalone we can validate the config. env, settings.
    from dynaconf import settings

    if set_env:
        settings.setenv()

    time_complete = timeit.default_timer() - time_start
    _LOGGER.info('~   config.init_o3de_core() DONE: {} sec'.format(time_complete))

    return settings
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
def get_config_settings(settings=_SETTINGS, set_env=True):
    'This will return the settings as initialized via this module'

    settings = init_dccsi_substance()

    return settings
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
_MODULE_END = timeit.default_timer() - _MODULE_START
_LOGGER.debug(f'{_MODULENAME} took: {_MODULE_END} sec')
# -------------------------------------------------------------------------


###########################################################################
# Main Code Block, runs this script as main (testing)
# -------------------------------------------------------------------------
if __name__ == '__main__':
    """Run this file as a standalone cli script for testing/debugging"""

    main_start = timeit.default_timer()  # start tracking

    _MODULENAME = 'DCCsi.Tools.DCC.Substance.config'

    import pathlib

    from azpy.env_bool import env_bool
    # temp internal debug flag, toggle values for manual testing
    _DCCSI_GDEBUG = env_bool(ENVAR_DCCSI_GDEBUG, False)
    _DCCSI_DEV_MODE = env_bool(ENVAR_DCCSI_DEV_MODE, False)
    _DCCSI_LOGLEVEL = env_bool(ENVAR_DCCSI_LOGLEVEL, _logging.INFO)
    _DCCSI_GDEBUGGER = env_bool(ENVAR_DCCSI_GDEBUGGER, 'WING')

    # default loglevel to info unless set
    _DCCSI_LOGLEVEL = int(env_bool(ENVAR_DCCSI_LOGLEVEL, _logging.INFO))
    if _DCCSI_GDEBUG:
        # override loglevel if runnign debug
        _DCCSI_LOGLEVEL = _logging.DEBUG

    # set up module logging
    #for handler in _logging.root.handlers[:]:
        #_logging.root.removeHandler(handler)

    # configure basic logger
    # note: not using a common logger to reduce cyclical imports
    _logging.basicConfig(level=_DCCSI_LOGLEVEL,
                        format=FRMT_LOG_LONG,
                        datefmt='%m-%d %H:%M')

    _LOGGER = _logging.getLogger(_MODULENAME)

    from azpy.constants import STR_CROSSBAR

    # happy print
    _LOGGER.info(STR_CROSSBAR)
    _LOGGER.info('~ {}.py ... Running script as __main__'.format(_MODULENAME))
    _LOGGER.info(STR_CROSSBAR)

    # go ahead and run the rest of the configuration
    # parse the command line args
    import argparse
    parser = argparse.ArgumentParser(
        description='O3DE DCCsi Dynamic Config (dynaconf) for Blender',
        epilog="Attempts to determine O3DE project if -pp not set")

    parser.add_argument('-gd', '--global-debug',
                        type=bool,
                        required=False,
                        default=False,
                        help='(NOT IMPLEMENTED) Enables global debug flag.')

    parser.add_argument('-dm', '--developer-mode',
                        type=bool,
                        required=False,
                        default=False,
                        help='(NOT IMPLEMENTED) Enables dev mode for early auto attaching debugger.')

    parser.add_argument('-sd', '--set-debugger',
                        type=str,
                        required=False,
                        default='WING',
                        help='(NOT IMPLEMENTED) Default debugger: WING, thers: PYCHARM and VSCODE.')

    parser.add_argument('-pp', '--project-path',
                        type=pathlib.Path,
                        required=False,
                        default=Path('{ to do: implement }'),
                        help='(NOT IMPLEMENTED) The path to the project.')

    parser.add_argument('-qt', '--enable-qt',
                        type=bool,
                        required=False,
                        default=False,
                        help='(NOT IMPLEMENTED) Enables O3DE Qt & PySide2 access.')

    parser.add_argument('-tp', '--test-pyside2',
                        type=bool,
                        required=False,
                        default=False,
                        help='(NOT IMPLEMENTED) Runs Qt/PySide2 tests and reports.')

    parser.add_argument('-ex', '--exit',
                        type=bool,
                        required=False,
                        default=False,
                        help='(NOT IMPLEMENTED) Exits python. Do not exit if you want to be in interactive interpretter after config')

    args = parser.parse_args()

    # easy overrides
    if args.global_debug:
        _DCCSI_GDEBUG = True
        os.environ["DYNACONF_DCCSI_GDEBUG"] = str(_DCCSI_GDEBUG)

    if args.developer_mode:
        _DCCSI_DEV_MODE = True
        attach_debugger()  # attempts to start debugger

    if args.set_debugger:
        _LOGGER.info('Setting and switching debugger type not implemented (default=WING)')
        # To Do: implement debugger plugin pattern

    # now standalone we can validate the config. env, settings.
    # settings = get_config_settings(stub) # To Do: pipe in CLI
    settings = get_config_settings()

    # CORE
    _LOGGER.info(STR_CROSSBAR)
    # not using fstrings in this module because it might run in py2.7 (maya)
    _LOGGER.info('DCCSI_GDEBUG: {}'.format(settings.DCCSI_GDEBUG))
    _LOGGER.info('DCCSI_DEV_MODE: {}'.format(settings.DCCSI_DEV_MODE))
    _LOGGER.info('DCCSI_LOGLEVEL: {}'.format(settings.DCCSI_LOGLEVEL))
    _LOGGER.info('DCCSI_OS_FOLDER: {}'.format(settings.DCCSI_OS_FOLDER))

    _LOGGER.info('O3DE_DEV: {}'.format(settings.O3DE_DEV))
    _LOGGER.info('O3DE_O3DE_BUILD_FOLDER: {}'.format(settings.PATH_O3DE_BUILD))
    _LOGGER.info('PATH_O3DE_BUILD: {}'.format(settings.PATH_O3DE_BUILD))
    _LOGGER.info('PATH_O3DE_BIN: {}'.format(settings.PATH_O3DE_BIN))

    _LOGGER.info('PATH_DCCSIG: {}'.format(settings.PATH_DCCSIG))
    _LOGGER.info('DCCSI_LOG_PATH: {}'.format(settings.DCCSI_LOG_PATH))
    _LOGGER.info('PATH_DCCSI_CONFIG: {}'.format(settings.PATH_DCCSI_CONFIG))

    # to do: log substance settings for cli
    _LOGGER.info(f'{ENVAR_DCCSI_TOOLS_SUBSTANCE}: {settings.DCCSI_TOOLS_SUBSTANCE}')

    # custom prompt
    sys.ps1 = f"[{_MODULENAME}]>>"

    _MODULE_END = timeit.default_timer() - _MODULE_START
    _LOGGER.info(f'{_MODULENAME} took: {_MODULE_END} sec')

    if args.exit:
        # return
        sys.exit()
# --- END -----------------------------------------------------------------
