"""
Copyright (c) Contributors to the Open 3D Engine Project

SPDX-License-Identifier: Apache-2.0 OR MIT
"""

import os
import pytest

# Bail on the test if ly_test_tools doesn't exist.
pytest.importorskip('ly_test_tools')

import editor_python_test_tools.hydra_test_utils as hydra
import ly_test_tools.environment.file_system as file_system

test_directory = os.path.join(os.path.dirname(__file__), 'EditorScripts')


@pytest.mark.parametrize('project', ['AutomatedTesting'])
@pytest.mark.parametrize('level', ['tmp_level'])
@pytest.mark.usefixtures("automatic_process_killer")
@pytest.mark.parametrize("launcher_platform", ['windows_editor'])
class Test_DynVeg_Regressions(object):
    @pytest.fixture(autouse=True)
    def setup_teardown(self, request, workspace, project, level):
        def teardown():
            # delete temp level
            file_system.delete([os.path.join(workspace.paths.engine_root(), project, "Levels", level)], True, True)

        # Setup - add the teardown finalizer
        request.addfinalizer(teardown)

        # Make sure the temp level doesn't already exist
        file_system.delete([os.path.join(workspace.paths.engine_root(), project, "Levels", level)], True, True)

    @pytest.mark.test_case_id("C29470845")
    @pytest.mark.SUITE_periodic
    @pytest.mark.dynveg_regression
    def test_SurfaceDataRefreshes_RemainsStable(self, request, editor, level, launcher_platform):

        expected_lines = [
             "SurfaceDataRefreshes_RemainsStable:  test started",
             "SurfaceDataRefreshes_RemainsStable:  test finished", 
             "SurfaceDataRefreshes_RemainsStable:  result=SUCCESS"
        ]

        unexpected_lines = [
            "Sector update mode is 'RebuildSurfaceCache' but sector doesn't exist"
        ]

        hydra.launch_and_validate_results(
            request,
            test_directory,
            editor,
            'SurfaceDataRefreshes_RemainsStable.py',
            expected_lines=expected_lines,
            unexpected_lines=unexpected_lines,
            cfg_args=[level]
        )

    @pytest.mark.SUITE_periodic
    def test_VegetationInstances_DespawnWhenOutOfRange(self, request, editor, level, launcher_platform):
        
        expected_lines = [
            "VegetationInstances_DespawnWhenOutOfRange:  test started",
            "VegetationInstances_DespawnWhenOutOfRange:  test finished",
            "VegetationInstances_DespawnWhenOutOfRange:  result=SUCCESS"
        ]

        hydra.launch_and_validate_results(
            request, 
            test_directory, 
            editor, 
            'VegetationInstances_DespawnWhenOutOfRange.py',
            expected_lines=expected_lines,
            cfg_args=[level]
        )
