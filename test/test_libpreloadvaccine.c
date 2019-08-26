#define _GNU_SOURCE
#include "vendor/unity.h"
#include "../src/libpreloadvaccine.h"

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

int main(void)
{
   UnityBegin("test/test_libpreloadvaccine.c");

   RUN_TEST(test_la_version_zero);
   RUN_TEST(test_la_version_valid);

   return UnityEnd();
}