"""
Copyright (c) Contributors to the Open 3D Engine Project.
For complete copyright and license terms please see the LICENSE at the root of this distribution.

SPDX-License-Identifier: Apache-2.0 OR MIT

Unit tests for metrics_xml_to_csv.py
"""
import unittest
import unittest.mock as mock

import pytest_metrics_xml_to_csv


class TestMetricsXMLtoCSV(unittest.TestCase):

    @mock.patch("pytest_metrics_xml_to_csv.datetime.datetime")
    def test_GetDefaultCSVFilename_SingleDigit_HasZeroes(self, mock_datetime):
        mock_date = mock.MagicMock()
        mock_date.month = 1
        mock_date.day = 2
        mock_date.year = "xxxx"
        mock_date.hour = 3
        mock_date.minute = 4
        mock_datetime.now.return_value = mock_date

        under_test = pytest_metrics_xml_to_csv._get_default_csv_filename()

        assert under_test == "xxxx_01_02_03_04_pytest.csv"

    @mock.patch("pytest_metrics_xml_to_csv.datetime.datetime")
    def test_GetDefaultCSVFilename_DoubleDigit_NoZeroes(self, mock_datetime):
        mock_date = mock.MagicMock()
        mock_date.month = 11
        mock_date.day = 12
        mock_date.year = "xxxx"
        mock_date.hour = 13
        mock_date.minute = 14
        mock_datetime.now.return_value = mock_date

        under_test = pytest_metrics_xml_to_csv._get_default_csv_filename()

        assert under_test == "xxxx_11_12_13_14_pytest.csv"

    def test_DetermineTestResult_FailedResult_ReturnsCorrectly(self):
        mock_node = mock.MagicMock()
        mock_node.find.return_value = True

        under_test = pytest_metrics_xml_to_csv._determine_test_result(mock_node)

        assert under_test == 'failed'

    def test_DetermineTestResult_PassedResult_ReturnsCorrectly(self):
        mock_node = mock.MagicMock()
        mock_node.find.return_value = None

        under_test = pytest_metrics_xml_to_csv._determine_test_result(mock_node)

        assert under_test == 'passed'

    
