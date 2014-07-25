/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * Licensed under the MIT license (see LICENSE).
 */
#ifndef _FNORDMETRIC_UTIL_UNITTEST_H
#define _FNORDMETRIC_UTIL_UNITTEST_H
#include "runtimeexception.h"
#include <functional>

namespace fnordmetric {
namespace util {

#define UNIT_TEST(T) \
  static fnordmetric::util::UnitTest T(#T); \
  int main() { \
    auto& t = T; \
    return t.run(); \
  }

#define TEST_CASE(T, N, L) \
  static fnordmetric::util::UnitTest::TestCase __##T##__case__##N(&T, #N, L);

class UnitTest {
public:

  class TestCase {
  public:
    TestCase(
        UnitTest* test,
        const char* name,
        std::function<void ()> lambda) :
        name_(name),
        lambda_(lambda) {
      test->addTestCase(this);
    }

    const char* name_;
    std::function<void ()> lambda_;
  };

  UnitTest(const char* name) : name_(name) {}

  void addTestCase(const TestCase* test_case) {
    cases_.push_back(test_case);
  }

  int run() {
    setbuf(stdout, NULL);
    printf("%s\n", name_);

    const TestCase* current_test_case = nullptr;
    int num_tests_passed = 0;
    for (auto test_case : cases_) {
      printf("    %s::%s", name_, test_case->name_);
      current_test_case = test_case;

      try {
        test_case->lambda_();
      } catch (fnordmetric::util::RuntimeException e) {
        printf(" [FAIL]\n\n");
        e.debugPrint();
        continue;
      }

      num_tests_passed++;
      printf(" [PASS]\n");
    }

    if (num_tests_passed == cases_.size()) {
      printf("\n[SUCCESS] All tests passed :)\n");
      return 0;
    } else {
      printf(
          "\n[FAIL] %i/%i tests failed :(\n",
          cases_.size() - num_tests_passed,
          cases_.size());
      return 1;
    }
  }

protected:
  const char* name_;
  std::vector<const TestCase*> cases_;
};

}
}
#endif