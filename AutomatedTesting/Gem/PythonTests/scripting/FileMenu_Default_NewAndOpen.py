"""
Copyright (c) Contributors to the Open 3D Engine Project.
For complete copyright and license terms please see the LICENSE at the root of this distribution.

SPDX-License-Identifier: Apache-2.0 OR MIT
"""

from PySide2 import QtWidgets
from editor_python_test_tools.utils import TestHelper as helper
from editor_python_test_tools.utils import Report
import azlmbr.legacy.general as general
import editor_python_test_tools.pyside_utils as pyside_utils


# fmt: off
class Tests():

    initialTabTestResults = "Verified no tabs open"
    newTabTestResults = "New tab opened successfully"
    fileMenuTestResults = "Open file window triggered successfully"

# fmt: on
TIME_TO_WAIT = 3

class TestFileMenuDefaultNewOpen:

    """
    Summary:
     When clicked on File->New, new script opens
     File->Open should open the FileBrowser

    Expected Behavior:
     New and Open actions should work as expected.

    Test Steps:
     1) Open Script Canvas window (Tools > Script Canvas)
     2) Get the SC window object
     3) Trigger File->New action
     4) Verify if New tab is opened
     5) Trigger File->Open action
     6) Close Script Canvas window


    Note:
     - This test file must be called from the Open 3D Engine Editor command terminal
     - Any passed and failed tests are written to the Editor.log file.
        Parsing the file or running a log_monitor are required to observe the test results.

    :return: None
    """

    @pyside_utils.wrap_async
    async def run_test(self):

        # Preconditions
        general.idle_enable(True)

        # 1) Open Script Canvas window and wait for it to render(Tools > Script Canvas)
        general.open_pane("Script Canvas")
        helper.wait_for_condition(lambda: general.is_pane_visible("Script Canvas"), TIME_TO_WAIT)

        # 2) Get the SC window object
        editor_window = pyside_utils.get_editor_main_window()
        sc = editor_window.findChild(QtWidgets.QDockWidget, "Script Canvas")
        sc_main = sc.findChild(QtWidgets.QMainWindow)
        sc_tabs = sc_main.findChild(QtWidgets.QTabWidget, "ScriptCanvasTabs")

        # 3) Get the initial tab count and verify it's zero. Save the tab count for verification in step 5
        result = helper.wait_for_condition(lambda: sc_tabs.count() == 0, TIME_TO_WAIT)
        Report.info(f"{Tests.initialTabTestResults}: {result}")
        initial_tabs_count = sc_tabs.count()

        # 4) Trigger open new graph file action
        action = pyside_utils.find_child_by_pattern(
            sc_main, {"objectName": "action_New_Script", "type": QtWidgets.QAction})
        action.trigger()

        # 5) Check tab count again to verify a new tab has been opened
        result = helper.wait_for_condition(lambda: sc_tabs.count() == initial_tabs_count + 1, TIME_TO_WAIT)
        Report.info(f"{Tests.newTabTestResults}: {result}")

        # 6) Trigger open file popup action then close the popup.
        action = pyside_utils.find_child_by_pattern(sc_main, {"objectName": "action_Open", "type": QtWidgets.QAction})
        pyside_utils.trigger_action_async(action)
        popup = await pyside_utils.wait_for_modal_widget()
        result = popup and 'Open' in popup.windowTitle()
        Report.info(f"{Tests.fileMenuTestResults}: {result}")
        popup.close()

        # 7) Close Script Canvas window
        general.close_pane("Script Canvas")


test = TestFileMenuDefaultNewOpen()
test.run_test()
