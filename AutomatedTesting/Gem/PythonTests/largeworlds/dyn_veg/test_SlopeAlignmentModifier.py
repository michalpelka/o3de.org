"""
All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
its licensors.

For complete copyright and license terms please see the LICENSE at the root of this
distribution (the "License"). All use of this software is governed by the License,
or, if provided, by the license below or the license accompanying this file. Do not
remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
"""

"""
C4896941 - Surface Alignment functions as expected
C4814459 - Surface Alignment overrides function as expected
"""

import os
import pytest

# Bail on the test if ly_test_tools doesn't exist.
pytest.importorskip("ly_test_tools")
import editor_python_test_tools.hydra_test_utils as hydra
import ly_test_tools.environment.file_system as file_system

test_directory = os.path.join(os.path.dirname(__file__), "EditorScripts")


@pytest.mark.parametrize("project", ["AutomatedTesting"])
@pytest.mark.parametrize("level", ["tmp_level"])
@pytest.mark.usefixtures("automatic_process_killer")
@pytest.mark.parametrize("launcher_platform", ['windows_editor'])
class TestSlopeAlignmentModifier(object):

    @pytest.fixture(autouse=True)
    def setup_teardown(self, request, workspace, project, level):
        def teardown():
            file_system.delete([os.path.join(workspace.paths.engine_root(), project, "Levels", level)], True, True)
        request.addfinalizer(teardown)

        file_system.delete([os.path.join(workspace.paths.engine_root(), project, "Levels", level)], True, True)

    @pytest.mark.test_case_id("C4896941")
    @pytest.mark.SUITE_periodic
    @pytest.mark.skip   # ATOM-14299
    def test_SlopeAlignmentModifier_InstanceSurfaceAlignment(self, request, editor, level, launcher_platform):

        expected_lines = [
            "Vegetation Slope Alignment Modifier component was added to entity",
            "Instance Spawner Configuration|Alignment Coefficient Min: SUCCESS",
            "Constant Gradient component was added to entity",
            "Instance Spawner Configuration|Gradient|Gradient Entity Id: SUCCESS",
            "SlopeAlignmentModifier:  result=SUCCESS"
        ]

        hydra.launch_and_validate_results(
            request,
            test_directory,
            editor,
            "SlopeAlignmentModifier_InstanceSurfaceAlignment.py",
            expected_lines,
            cfg_args=[level]
        )

    @pytest.mark.test_case_id("C4814459")
    @pytest.mark.SUITE_periodic
    @pytest.mark.skip  # ATOM-14299
    def test_SlopeAlignmentModifierOverrides_InstanceSurfaceAlignment(self, request, editor, level, launcher_platform):

        expected_lines = [
            "Instance Spawner Configuration|Allow Per-Item Overrides: SUCCESS",
            "Instance Spawner Configuration|Embedded Assets|[0]|Surface Slope Alignment|Override Enabled: SUCCESS",
            "Instance Spawner Configuration|Embedded Assets|[0]|Surface Slope Alignment|Max: SUCCESS",
            "Instance Spawner Configuration|Embedded Assets|[0]|Surface Slope Alignment|Min: SUCCESS",
            "SlopeAlignmentModifierOverrides:  result=SUCCESS"
        ]

        hydra.launch_and_validate_results(
            request,
            test_directory,
            editor,
            "SlopeAlignmentModifierOverrides_InstanceSurfaceAlignment.py",
            expected_lines,
            cfg_args=[level]
        )
