#define _GNU_SOURCE
#include "vendor/unity.h"
#include "../src/libpreloadvaccine.h"
#include <stdlib.h>
#include <string.h>
#include <link.h>

void setUp(void)
{
}

void tearDown(void)
{
}

static void test_la_version_zero(void)
{
    TEST_ASSERT_EQUAL_UINT(la_version(0),0);
}

static void test_la_version_valid(void)
{
    TEST_ASSERT_EQUAL_UINT(la_version(LAV_CURRENT), LAV_CURRENT);
}

static void test_file_contains_object(void)
{
    char *working_dir = getenv("PWD");
    char *test_path = strcat(working_dir,"/test/test_data/ld.so.preload");
    TEST_ASSERT_TRUE(file_contains_object("/tmp/libpreload.so", test_path));
}

static void test_file_contains_object_bad_file(void)
{
    char *working_dir = getenv("PWD");
    char *test_path = strcat(working_dir,"/test/test_data/ld.so.preload");
    TEST_ASSERT_FALSE(file_contains_object("/tmp/libpreload.so", test_path));
}

static void test_env_variable_contains_object_valid(void)
{
    setenv("LD_PRELOAD","/thing1.so",1);
    TEST_ASSERT_TRUE(env_variable_contains_object("thing1.so","LD_PRELOAD"));
}

static void test_env_variable_contains_object_null(void)
{
    unsetenv("LD_PRELOAD");
    TEST_ASSERT_FALSE(env_variable_contains_object("thing1.so","LD_PRELOAD"));
}


int main(void)
{
   UnityBegin("test/test_libpreloadvaccine.c");

   RUN_TEST(test_la_version_zero);
   RUN_TEST(test_la_version_valid);
   RUN_TEST(test_file_contains_object);
   RUN_TEST(test_env_variable_contains_object_null);
   RUN_TEST(test_env_variable_contains_object_valid);
   RUN_TEST(test_file_contains_object_bad_file);

   return UnityEnd();
}
