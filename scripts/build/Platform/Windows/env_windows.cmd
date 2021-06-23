@ECHO OFF
REM
REM Copyright (c) Contributors to the Open 3D Engine Project
REM 
REM SPDX-License-Identifier: Apache-2.0 OR MIT
REM
REM

where /Q cmake
IF NOT %ERRORLEVEL%==0 (
    ECHO [ci_build] CMake not found
    GOTO :error
)

EXIT /b 0

:error
EXIT /b 1