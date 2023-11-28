import os, errno

import unittest
from subprocess import Popen, PIPE

from contextlib import contextmanager

TEST_PROGRAM = './classTask1 '

@contextmanager
def clear_db_fixture(message):
    rmDatabase(message)
    try:
        yield
    finally:
        rmDatabase(message)

def rmDatabase(filename):
    try:
        os.remove(filename)
    except OSError as e:
        if e.errno != errno.ENOENT: # errno.ENOENT = no such file or directory
            raise

class TestClassTask(unittest.TestCase):

    def callPopen(self, message):
        with Popen(TEST_PROGRAM + message, stdout=PIPE, stderr=PIPE, shell=True) as process:
            process.wait()
            assert process.returncode == 0
            return process.stdout.read()

    def setUp(self):
        rmDatabase("db.txt")

    def tearDown(self):
        rmDatabase("db.txt")


    @clear_db_fixture("db.txt")
    def test_simple_insert(self):
        TEST_ARGS = 'INSERT 1=2? INSERT 3=4? INSERT 5=6? INSERT 7=8?'
        _ = self.callPopen(TEST_ARGS)

        TEST_ARGS = 'FIND 1?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b'FOUND: 2\n'
        self.assertEqual(process_out, expected_out)


    @clear_db_fixture("db.txt")
    def test_simple_delete(self):
        TEST_ARGS = 'INSERT 1=2? INSERT 3=4?'
        _ = self.callPopen(TEST_ARGS)

        TEST_ARGS = 'DELETE 3?'
        _ = self.callPopen(TEST_ARGS)


        TEST_ARGS = 'FIND 3?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b'NOT FOUND\n'
        self.assertEqual(process_out, expected_out)


    @clear_db_fixture("db.txt")
    def test_simple_reassign(self):
        TEST_ARGS = 'INSERT hello=world?'
        _ = self.callPopen(TEST_ARGS)

        TEST_ARGS = 'FIND hello?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b'FOUND: world\n'
        self.assertEqual(process_out, expected_out)


        TEST_ARGS = 'INSERT hello=mir?'
        _ = self.callPopen(TEST_ARGS)


        TEST_ARGS = 'FIND hello?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b'FOUND: mir\n'
        self.assertEqual(process_out, expected_out)


    @clear_db_fixture("db.txt")
    def test_reassign_deleted(self):
        TEST_ARGS = 'INSERT hello=world?'
        _ = self.callPopen(TEST_ARGS)

        TEST_ARGS = 'FIND hello?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b'FOUND: world\n'
        self.assertEqual(process_out, expected_out)

        TEST_ARGS = 'DELETE hello?'
        _ = self.callPopen(TEST_ARGS)

        TEST_ARGS = 'FIND hello?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b'NOT FOUND\n'
        self.assertEqual(process_out, expected_out)


        TEST_ARGS = 'INSERT hello=mir?'
        _ = self.callPopen(TEST_ARGS)

        TEST_ARGS = 'FIND hello?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b'FOUND: mir\n'
        self.assertEqual(process_out, expected_out)


    @clear_db_fixture("db.txt")
    def test_delete_return_empty(self):
        TEST_ARGS = 'INSERT 1=2? INSERT 3=4?'
        _ = self.callPopen(TEST_ARGS)

        TEST_ARGS = 'DELETE 1?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b''
        self.assertEqual(process_out, expected_out)

        TEST_ARGS = 'DELETE hello?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b''
        self.assertEqual(process_out, expected_out)


    @clear_db_fixture("db.txt")
    def test_simple_print(self):
        TEST_ARGS = 'INSERT 1=2? INSERT 3=4? INSERT 5=6? INSERT hello=world?'
        _ = self.callPopen(TEST_ARGS)


        TEST_ARGS = 'PRINT VALUES?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b'2\n4\n6\nworld\n'
        ok = False
        if (process_out == expected_out):
            ok = True
        elif (all([
                expected in process_out for expected in [b'2', b'4', b'6', b'world']
                    ])):
            ok = True
        self.assertTrue(ok)


        TEST_ARGS = 'PRINT KEYS?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b'1\n3\n5\nhello\n'
        ok = False
        if (process_out == expected_out):
            ok = True
        elif (all([
                expected in process_out for expected in [b'1', b'3', b'5', b'hello']
                    ])):
            ok = True
        self.assertTrue(ok)


    @clear_db_fixture("db.txt")
    def test_simple_print_deleted(self):
        TEST_ARGS = 'INSERT 1=2? INSERT 3=4? INSERT hello=world?'
        _ = self.callPopen(TEST_ARGS)


        TEST_ARGS = 'PRINT VALUES?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b'2\n4\nworld\n'
        ok = False
        if (process_out == expected_out):
            ok = True
        elif (all([
                expected in process_out for expected in [b'2', b'4', b'world']
                    ])):
            ok = True
        self.assertTrue(ok)

        TEST_ARGS = 'DELETE hello?'
        _ = self.callPopen(TEST_ARGS)


        TEST_ARGS = 'PRINT VALUES?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b'2\n4\n'
        ok = False
        if (process_out == expected_out):
            ok = True
        elif (all([
                expected in process_out for expected in [b'2', b'4']
                    ])):
            ok = True
        self.assertTrue(ok)


        TEST_ARGS = 'DROPALL?'
        _ = self.callPopen(TEST_ARGS)

        TEST_ARGS = 'PRINT VALUES?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b''
        self.assertTrue(process_out == expected_out)


    @clear_db_fixture("db.txt")
    def test_print_reassigned(self):
        TEST_ARGS = 'INSERT 1=2? INSERT 3=4? INSERT hello=world?'
        _ = self.callPopen(TEST_ARGS)

        TEST_ARGS = 'PRINT VALUES?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b'2\n4\nworld\n'
        ok = False
        if (process_out == expected_out):
            ok = True
        elif (all([
                expected in process_out for expected in [b'2', b'4', b'world']
                    ])):
            ok = True
        self.assertTrue(ok)

        TEST_ARGS = 'INSERT 1=reassigned?'
        _ = self.callPopen(TEST_ARGS)

        TEST_ARGS = 'PRINT VALUES?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b'reassigned\n4\nworld\n'
        ok = False
        if (process_out == expected_out):
            ok = True
        elif (all([
                expected in process_out for expected in [b'reassigned', b'4', b'world']
                    ])):
            ok = True
        self.assertTrue(ok)


    @clear_db_fixture("db.txt")
    def test_empty_command(self):
        TEST_ARGS = 'INSERT hello=world?'
        _ = self.callPopen(TEST_ARGS)

        TEST_ARGS = 'DROPALL?'
        _ = self.callPopen(TEST_ARGS)

        TEST_ARGS = ''
        process_out = self.callPopen(TEST_ARGS)
        expected_out = b''
        self.assertEqual(process_out, expected_out)


    @clear_db_fixture("db.txt")
    def test_find_after_drop(self):
        TEST_ARGS = 'INSERT hello=world?'
        _ = self.callPopen(TEST_ARGS)

        TEST_ARGS = 'FIND hello?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b'FOUND: world\n'
        self.assertEqual(process_out, expected_out)

        TEST_ARGS = 'DROPALL?'
        process_out = self.callPopen(TEST_ARGS)

        expected_out = b''
        self.assertEqual(process_out, expected_out)

        TEST_ARGS = 'FIND hello?'
        process_out = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_out = b'NOT FOUND\n'
        self.assertEqual(process_out, expected_out)

if __name__ == '__main__':
    unittest.main()