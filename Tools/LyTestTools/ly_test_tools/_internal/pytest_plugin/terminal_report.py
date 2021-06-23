"""
Copyright (c) Contributors to the Open 3D Engine Project

SPDX-License-Identifier: Apache-2.0 OR MIT
"""
import os

import ly_test_tools._internal.pytest_plugin.failed_test_rerun_command as rerun


def _add_commands(terminalreporter, header, test_path, nodeids, build_dir=None):
    """
    Add test re-run commands to the TerminalReporter object
    :param terminalreporter: Pytest's TerminalReporter object that contains test result information.
    :param header: Message to write to TerminalReporter before list is added
    :param test_path: File or directory that contains the test(s) that to run
    :param nodeids: List of test node ids, with parametrized values
    :param build_dir: the --build-directory arg that is passed to determine which build dir to use. Can also be None
    """

    terminalreporter.write_line(header)

    if nodeids:
        commands = rerun.build_rerun_commands(test_path, nodeids, build_dir)
        for command in commands:
            terminalreporter.write_line(command)
    else:
        terminalreporter.write_line("Error, Test node id list is empty!")


def pytest_terminal_summary(terminalreporter, exitstatus, config):
    """
    Pytest's hook for terminal reporting. This hook is invoked at the end of the test session.

    :param terminalreporter: Pytest's TerminalReporter object that contains test result information.
    :param exitstatus: Exit that will be returned to the system
    """
    # Check to see if the build directory was passed
    build_dir = None
    try:
        build_dir = config.known_args_namespace.build_directory
    except AttributeError:
        pass

    # Add to the TerminalReport a section for failed test re-running
    failures = terminalreporter.stats.get('failed', [])
    errors = terminalreporter.stats.get('error', [])
    failure_count = len(failures)
    error_count = len(errors)

    if failure_count or error_count:
        file_or_dir_option = terminalreporter.config.getoption('file_or_dir', default=[])
        if file_or_dir_option:
            test_path = file_or_dir_option[0]
        else:
            test_path = ''

        terminalreporter.section("Test failure and error troubleshooting")

        if failure_count:
            nodeids = [os.path.basename(report.nodeid) for report in failures]

            _add_commands(
                terminalreporter,
                "Use the following commands to re-run each test that failed locally\n"
                "(NOTE: The 'PYTHON' or 'PYTHONPATH' environment variables need values for accurate commands): ",
                test_path, nodeids, build_dir)

        if error_count:
            nodeids = [os.path.basename(report.nodeid) for report in errors]

            _add_commands(
                terminalreporter,
                "Use the following commands to re-run each test that had errors locally\n"
                "(NOTE: The 'PYTHON' or 'PYTHONPATH' environment variables need values for accurate commands): ",
                test_path, nodeids, build_dir)
