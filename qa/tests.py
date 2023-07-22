import csv
import glob
import os
import pytest
import random
import shutil
import sys
import subprocess
import time
import itertools
from concurrent.futures import ThreadPoolExecutor


@pytest.fixture(scope="module")
def csv_test_data():
    reports = {}

    os.makedirs('test_data', exist_ok=True)

    filename = 'test_data/data_simple.csv'
    with open(filename, 'w') as f:
        data = csv.writer(f)
        data.writerow(['06.02.2023 00:00:00', 1.1, 1.1])
        data.writerow(['07.02.2023 18:45:01', 2.2, 2.2])
        data.writerow(['06.02.2023 07:30:02', 3.3, 3.3])
    reports[filename] = [f'{filename},quotient,1.0',
                         f'{filename},rows,3']

    filename = 'test_data/data_huge.csv'
    with open(filename, 'w') as f:
        data = csv.writer(f)
        for row in range(1, 100000):
            data.writerow(
                [f'{str(random.randint(1, 12)).zfill(2)}'
                 f'.{str(random.randint(1, 28)).zfill(2)}'
                 f'.{str(random.randint(1922, 1991))} 00:00::00', 1.1, f'1.{row}'])
            if row == 42:
                data.writerow(['07.02.2023 18:45:01', 2.2, 2.2])
                reports[filename] = [f'{filename},quotient,1.0',
                                     f'{filename},rows,1000']

    for i in range(1, 101):
        filename = f'test_data/data_many_{i}.csv'
        with open(filename, 'w') as f:
            data = csv.writer(f)
            for row in range(0, random.randint(100, 1000)):
                data.writerow(
                    [f'{str(random.randint(1, 12)).zfill(2)}'
                     f'.{str(random.randint(1, 28)).zfill(2)}'
                     f'.{str(random.randint(1922, 1991))} 00:00::00', 1.1, f'1.{i}'])
                if row == 42:
                    data.writerow(['07.02.2023 18:45:01', 2.2, 2.2])
                    reports[filename] = [
                        f'{filename},quotient,1.0', f'{filename},rows,1000']

    yield reports


@pytest.fixture
def server_process():
    server_process = subprocess.Popen(
        ['./server'], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    yield server_process
    server_process.terminate()
    server_process.wait()


def test_simple(server_process, csv_test_data):
    filename = 'test_data/data_simple.csv'
    # subprocess.run(f'./client {filename}')
    for row in open('report.log'):
        assert row.rstrip() in csv_test_data[filename]


def test_huge(server_process, csv_test_data):
    filename = 'test_data/data_huge.csv'
    # subprocess.run(f'./client {filename}')
    for row in open('report.log'):
        assert row.rstrip() in csv_test_data[filename]


def test_many(server_process, csv_test_data):
    with ThreadPoolExecutor(max_workers=5) as executor:
        def worker(filename):
            assert False
            pass  # subprocess.run(f'./client {filename}')
        filename_pattern = 'test_data/data_many_*.csv'
        filenames = glob.glob(filename_pattern)
        executor.map(worker, filenames)
        report_rows = (row.rstrip() for row in open('report.log'))
        reference_rows = itertools.chain(
            (csv_test_data[filename] for filename in filenames))
        assert all(item in reference_rows for item in report_rows)
