
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
    < DCCsi >:: Tools//DCC//Substance//constants.py

This module contains default values for commony used constants & strings.
We can make an update here easily that is propogated elsewhere.

Notice: this module should not actually set ENVARs in the os.environ
That would be the responsibility of a module like config.py
"""
# -------------------------------------------------------------------------
# standard imports
import sys
import os
import site
import timeit
import inspect
from pathlib import Path
import logging as _logging
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# global scope
_MODULENAME = 'Tools.DCC.Substance.constants'
_LOGGER = _logging.getLogger(_MODULENAME)
_LOGGER.debug(f'Initializing: {_MODULENAME}')

_MODULE_PATH = Path(__file__)  # To Do: what if frozen?
_LOGGER.debug(f'_MODULE_PATH: {_MODULE_PATH.as_posix()}')

# we need to set up basic access to the DCCsi
_PATH_DCCSIG = Path(_MODULE_PATH, '../../../..').resolve()
site.addsitedir(_PATH_DCCSIG.as_posix())
_LOGGER.debug(f'site.addsitedir({_PATH_DCCSIG})')
# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# Substance Designer default paths
# our ENVARS that mimic the dccsi windows .bat file env and can be overriden

# ENVAR_ == env key
# PATH_ == retreived path, as pathlib.Path object

# our dccsi location for substance designer <DCCsi>\Tools\DCC\Substance
# to do: This ENVAR Key should be refacted across files to 'DCCSI_TOOLS_SUBSTANCE'
ENVAR_DCCSI_TOOLS_SUBSTANCE_PATH = "DCCSI_TOOLS_SUBSTANCE_PATH"
PATH_DCCSI_TOOLS_SUBSTANCE_PATH = Path(_MODULE_PATH.parent)
PATH_DCCSI_TOOLS_SUBSTANCE_PATH = Path(os.getenv(ENVAR_DCCSI_TOOLS_SUBSTANCE_PATH,
                                                  PATH_DCCSI_TOOLS_SUBSTANCE_PATH.as_posix()))

# DCCsi tools dir
# to do: This ENVAR Key should be refacted across files to 'DCCSI_TOOLS'
ENVAR_PATH_DCCSI_TOOLS = "PATH_DCCSI_TOOLS"  # <DCCsi>\Tools
PATH_PATH_DCCSI_TOOLS = Path(PATH_DCCSI_TOOLS_SUBSTANCE_PATH.parent.parent)
PATH_PATH_DCCSI_TOOLS = Path(os.getenv(ENVAR_PATH_DCCSI_TOOLS,
                                       PATH_PATH_DCCSI_TOOLS.as_posix()))

ENVAR_DCCSI_SUBSTANCE_RESOURCES = "DCCSI_SUBSTANCE_RESOURCES"  # <DCCsi>\Tools\DCC\Substance\Resources
PATH_DCCSI_SUBSTANCE_RESOURCES = Path(PATH_PATH_DCCSI_TOOLS, 'Resources')
PATH_DCCSI_SUBSTANCE_RESOURCES = Path(os.getenv(ENVAR_DCCSI_SUBSTANCE_RESOURCES,
                                                 PATH_DCCSI_SUBSTANCE_RESOURCES.as_posix()))

ENVAR_DCCSI_SUBSTANCE_LOCATION = "DCCSI_SUBSTANCE_LOCATION"
PATH_DCCSI_SUBSTANCE_LOCATION = Path(os.environ['PROGRAMFILES'],
                                      'Adobe',
                                      'Adobe Substance 3D Designer')
PATH_DCCSI_SUBSTANCE_LOCATION = Path(os.getenv(ENVAR_DCCSI_SUBSTANCE_LOCATION,
                                                 PATH_DCCSI_SUBSTANCE_LOCATION.as_posix()))

ENVAR_DCCSI_SUBSTANCE_EXE = "DCCSI_SUBSTANCE_EXE"
PATH_DCCSI_SUBSTANCE_EXE = Path(PATH_DCCSI_SUBSTANCE_LOCATION, 'Adobe Substance 3D Designer.exe')
PATH_DCCSI_SUBSTANCE_EXE = Path(os.getenv(ENVAR_DCCSI_SUBSTANCE_EXE,
                                          PATH_DCCSI_SUBSTANCE_EXE.as_posix()))

ENVAR_DCCSI_SUBSTANCE_PYTHON = "DCCSI_SUBSTANCE_PYTHON"
PATH_DCCSI_SUBSTANCE_PYTHON = Path(PATH_DCCSI_SUBSTANCE_LOCATION, 'plugins', 'pythonsdk')
PATH_DCCSI_SUBSTANCE_PYTHON = Path(os.getenv(ENVAR_DCCSI_SUBSTANCE_PYTHON,
                                             PATH_DCCSI_SUBSTANCE_PYTHON.as_posix()))

ENVAR_DCCSI_SUBSTANCE_PY_EXE = "DCCSI_SUBSTANCE_PY_EXE"
PATH_DCCSI_SUBSTANCE_PY_EXE = Path(PATH_DCCSI_SUBSTANCE_PYTHON, 'python.exe')
PATH_DCCSI_SUBSTANCE_PY_EXE = Path(os.getenv(ENVAR_DCCSI_SUBSTANCE_PY_EXE,
                                             PATH_DCCSI_SUBSTANCE_PY_EXE.as_posix()))

ENVAR_DCCSI_PY_SUBSTANCE = "DCCSI_PY_SUBSTANCE"
PATH_DCCSI_PY_SUBSTANCE = PATH_DCCSI_SUBSTANCE_PY_EXE
PATH_DCCSI_PY_SUBSTANCE = Path(os.getenv(ENVAR_DCCSI_PY_SUBSTANCE,
                                         PATH_DCCSI_PY_SUBSTANCE.as_posix()))

ENVAR_DCCSI_SUBSTANCE_SET_CALLBACKS = "DCCSI_SUBSTANCE_SET_CALLBACKS"
DCCSI_SUBSTANCE_SET_CALLBACKS = os.getenv(ENVAR_DCCSI_SUBSTANCE_SET_CALLBACKS, False)
# ^ really should use env_bool, but we are restricting other dccsi module imports here

# our dccsi python scripts
ENVAR_DCCSI_SUBSTANCE_SCRIPTS = "DCCSI_SUBSTANCE_SCRIPTS"
PATH_DCCSI_SUBSTANCE_SCRIPTS = Path(PATH_DCCSI_SUBSTANCE_RESOURCES, 'python')
PATH_DCCSI_SUBSTANCE_SCRIPTS = Path(os.getenv(ENVAR_DCCSI_SUBSTANCE_SCRIPTS,
                                              PATH_DCCSI_SUBSTANCE_SCRIPTS.as_posix()))

ENVAR_DCCSI_SUBSTANCE_CFG = "DCCSI_SUBSTANCE_CFG"
TAG_DCCSI_SUBSTANCE_CFG = "o3de_dccsi.sbscfg"
DCCSI_SUBSTANCE_CFG = os.getenv(ENVAR_DCCSI_SUBSTANCE_CFG, TAG_DCCSI_SUBSTANCE_CFG)

ENVAR_DCCSI_SUBSTANCE_CFG_PATH = "DCCSI_SUBSTANCE_CFG_PATH"
PATH_DCCSI_SUBSTANCE_CFG_PATH = Path(PATH_DCCSI_TOOLS_SUBSTANCE_PATH, DCCSI_SUBSTANCE_CFG)
PATH_DCCSI_SUBSTANCE_CFG_PATH = Path(os.getenv(ENVAR_DCCSI_SUBSTANCE_CFG_PATH,
                                               PATH_DCCSI_SUBSTANCE_CFG_PATH.as_posix()))

# -------------------------------------------------------------------------


# -------------------------------------------------------------------------
# Substance Designer Registry paths, to retreive registered install paths
# To Do: the use of these and searching the registry is not implemented in DCCsi yet
# Substance docs: https://substance3d.adobe.com/documentation/sddoc/retrieving-the-installation-path-172823228.html
# Windwows (registry)
# Creative Cloud Desktop (CCD), Adobe Version 11.2 (or newer)
WIN_REG_APP_PATHS_HKEY = "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\"
WIN_CCD_SUBD_APP_EXE_SUBKEY = "Adobe Substance 3D Designer.exe"
WIN_CCD_SUBD_APP_HKEY = WIN_REG_APP_PATHS_HKEY + WIN_CCD_SUBD_APP_EXE_SUBKEY

# This registry key is only available since version 11.2.
# For older versions, the installation path can be retrieved from the file associations in
WIN_ALT_CCD_REG_APP_PATHS_HKEY = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\"
# to do: figure out what this means, I assume it's something like inspect ".sbs" file extension?

# Substance 3D Standalone (SA)
WIN_SA_REG_APP_PATHS_HKEY = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall6"
WIN_SA_VER_5_x_SUBKEY = "{25E7D16D-1FBA-49EA-BF36-E2D6B20A9206}"   # Version 5.x
WIN_SA_VER_6_x_SUBKEY = "{09a302b1-8da8-4f62-b0cb-a208faa210f9}"   # Version 6.x
WIN_SA_VER_7_x_SUBKEY = "{e9e3d6d9-3023-41c7-b223-11d8fdd691b9}"   # Version 7.x (2017.x) to 11.1
WIN_SA_VER_11_2_SUBKEY = "{662bb79f-5616-44e6-a84d-b3d6abebe002}"  # Version 11.2 (or newer)

# Steam
# The application is installed in the steamapps/common/ sub-folder of the Steam installation folder.
# You'll want to override the appplication path in the <dccsi>/Tools/DCC/Substance/settings.local.json file
# to do: If someone ever sets this up put an example here

# Mac (library)
# To Do: Mac isn't implemented
# On Mac the application is installed in the following:
MAC_REG_SUB_APP = "/Applications/Adobe Substance 3D Designer.app"  # 11.2 or newer
MAC_LEGACY_REG_SUB_APP = "/Applications/Substance Designer.app"  # Legacy

# Linux
LINUX_REG_SUB_APP = "/opt/Adobe/Adobe_Substance_3D_Designer"  # 11.2 or newer
LINUX_LEGACY_REG_SUB_APP = "/opt/Allegorithmic/Substance_Designer"  # Legacy

# Substance Painter doc link with examples for registry parsing:
# https: // substance3d.adobe.com / documentation / spdoc / editing - the - shelf - preferences - with-python - 172824763.html
# -------------------------------------------------------------------------


###########################################################################
# Main Code Block, runs this script as main (testing)
# -------------------------------------------------------------------------
if __name__ == '__main__':
    """Run this file as a standalone script for local tests"""

    _MODULENAME = 'Tools.DCC.Substance.constants.cli'

    from azpy.env_bool import env_bool
    from azpy.constants import ENVAR_DCCSI_GDEBUG
    from azpy.constants import ENVAR_DCCSI_LOGLEVEL
    from azpy.constants import FRMT_LOG_LONG

    _DCCSI_GDEBUG = env_bool(ENVAR_DCCSI_GDEBUG, False)
    _DCCSI_LOGLEVEL = env_bool(ENVAR_DCCSI_LOGLEVEL, _logging.INFO)

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

    # happy print
    _LOGGER.info("# {0} #".format('-' * 72))
    _LOGGER.info(f'~ {_MODULENAME} ... Running module as __main__')
    _LOGGER.info("# {0} #".format('-' * 72))

    _LOGGER.debug('_DCCSI_GDEBUG: {}'.format(_DCCSI_GDEBUG))
    _LOGGER.debug('_DCCSI_LOGLEVEL: {}'.format(_DCCSI_LOGLEVEL))

    # run a local test
    _stash_dict = {}
    _stash_dict['_MODULENAME'] = Path(_MODULE_PATH)
    _stash_dict['PATH_DCCSIG'] = Path(_PATH_DCCSIG)

    _stash_dict[ENVAR_DCCSI_TOOLS_SUBSTANCE_PATH] = PATH_DCCSI_TOOLS_SUBSTANCE_PATH
    _stash_dict[ENVAR_PATH_DCCSI_TOOLS] = PATH_PATH_DCCSI_TOOLS
    _stash_dict[ENVAR_DCCSI_SUBSTANCE_RESOURCES] = PATH_DCCSI_SUBSTANCE_RESOURCES
    _stash_dict[ENVAR_DCCSI_SUBSTANCE_LOCATION] = PATH_DCCSI_SUBSTANCE_LOCATION
    _stash_dict[ENVAR_DCCSI_SUBSTANCE_EXE] = PATH_DCCSI_SUBSTANCE_EXE
    _stash_dict[ENVAR_DCCSI_SUBSTANCE_PYTHON] = PATH_DCCSI_SUBSTANCE_PYTHON
    _stash_dict[ENVAR_DCCSI_SUBSTANCE_PY_EXE] = PATH_DCCSI_SUBSTANCE_PY_EXE
    _stash_dict[ENVAR_DCCSI_PY_SUBSTANCE] = _PATH_DCCSIG
    _stash_dict[ENVAR_DCCSI_SUBSTANCE_SCRIPTS] = PATH_DCCSI_SUBSTANCE_SCRIPTS
    _stash_dict[ENVAR_DCCSI_SUBSTANCE_CFG_PATH] = PATH_DCCSI_SUBSTANCE_CFG_PATH

    # ---------------------------------------------------------------------
    # py 2 and 3 compatible iter
    def get_items(dict_object):
        for key in dict_object:
            yield key, dict_object[key]

    for key, value in get_items(_stash_dict):
        # check if path exists
        try:
            value.exists()
            _LOGGER.info(F'Path.()exists():: {key}: {value}')
        except Exception as e:
            _LOGGER.warning(f'FAILED PATH: {e}')
    # ---------------------------------------------------------------------

    # custom prompt
    sys.ps1 = f"[{_MODULENAME}]>>"

# --- END -----------------------------------------------------------------










