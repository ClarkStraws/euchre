#! /usr/bin/env python

import os
import subprocess
import argparse

import fnmatch

TEST_EXE_PATTERNS = ['Card_test*.exe', 'Pack_test*.exe', 'Player_test*.exe']


def main():
    args = parse_args()

    num_tests_run = 0
    failures = []

    test_exes = []
    for pattern in args.patterns_to_run:
        test_exes += fnmatch.filter(os.listdir('.'), pattern)

    for test in test_exes:
        return_code = subprocess.call(['./' + test])
        num_tests_run += 1
        if return_code != 0:
            failures.append(test)

    print('''Out of {} tests run:
    {} tests passed,
    {} tests failed.
    '''.format(
        num_tests_run,
        num_tests_run - len(failures),
        len(failures)))

    if failures:
        print("Tests that failed:")
        print(','.join(failures))


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("patterns_to_run",
                        nargs='*',
                        default=TEST_EXE_PATTERNS)

    return parser.parse_args()

test_exe_pattern = 'List_test_*.exe'


if __name__ == '__main__':
    main()

