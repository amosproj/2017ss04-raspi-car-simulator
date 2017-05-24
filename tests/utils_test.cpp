/**
 * @file UtilsTest.cpp
 * @author Florian Bauer
 *
 * Unit test for the utility functions.
 */

#include "utils_test.h"
#include "utilities.h"

CPPUNIT_TEST_SUITE_REGISTRATION(UtilsTest);

UtilsTest::UtilsTest() { }

UtilsTest::~UtilsTest() { }

void UtilsTest::setUp() { }

void UtilsTest::tearDown() { }

void UtilsTest::testExistsFile()
{
    const std::string file_path = "tests/testscript01.lua";
    bool result = utils::existsFile(file_path);
    CPPUNIT_ASSERT_MESSAGE("File does not exist!", result);
    
    // these checks are supposed to fail
    result = utils::existsFile("tests/");
    CPPUNIT_ASSERT_EQUAL(false, result);

    result = utils::existsFile("tests/hutzlpfrt.lua");
    CPPUNIT_ASSERT_EQUAL(false, result);
}

void UtilsTest::testExistsDirectory()
{
    const std::string dir_path = "tests";
    bool result = utils::existsDirectory(dir_path);
    CPPUNIT_ASSERT_MESSAGE("Directory does not exist!", result);

    result = utils::existsDirectory("tests/"); // check also case with trailing slash
    CPPUNIT_ASSERT_MESSAGE("Failure on path with trailing '/'", result);
    
    result = utils::existsDirectory("./");
    CPPUNIT_ASSERT_EQUAL(true, result);
    
    result = utils::existsDirectory("..");
    CPPUNIT_ASSERT_EQUAL(true, result);
    
    // this check is supposed to fail
    result = utils::existsDirectory("tests/testscript01.lua");
    CPPUNIT_ASSERT_EQUAL(false, result);
}
