/**
 * @file driver_dictionary.cpp
 * @brief Test suit for the linear search
 */

#include <algorithm>
#include <array>
#include <cassert>  // assert()
#include <iostream> // cout, endl
#include <iterator> // std::begin(), std::end()
#include <random>   // random_device, mt19937

#include "include/tm/test_manager.h"

#include "../src/searching.h"
using namespace sa;

int main() {
  // Creates a test manager for the DAL class.
  TestManager tm{"Linear Search Test Suite"};

  {
    //=== Test #1
    BEGIN_TEST(tm, "BasicSearch",
               "Search for all n elements present in the array.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};
    std::random_device rd;
    std::shuffle(arr.begin(), arr.end(), rd);
    // std::copy( arr.begin(), arr.end(),
    // std::ostream_iterator<int>(std::cout, " ") );

    // Looking for each element from arr in arr.
    for (const auto &e : arr) {
      auto result = lsearch(arr.begin(), arr.end(), e);
      EXPECT_EQ(*result, e);
    }
  }

  {
    //=== Test #2
    BEGIN_TEST(tm, "FailedSearchLeft",
               "Search for an element not present, which is smaller than the "
               "lowest value element.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};
    std::random_device rd;
    std::shuffle(arr.begin(), arr.end(), rd);

    auto target{-4};
    auto result = lsearch(arr.begin(), arr.end(), target);
    EXPECT_EQ(result, arr.end());
  }

  {
    //=== Test #3
    BEGIN_TEST(tm, "FailedSearchRight",
               "Search for an element not present, which is greater than the "
               "highest value element.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};
    std::random_device rd;
    std::shuffle(arr.begin(), arr.end(), rd);

    auto target{10};
    auto result = lsearch(arr.begin(), arr.end(), target);
    EXPECT_EQ(result, arr.end());
  }

  {
    //=== Test #4
    BEGIN_TEST(tm, "FailedSearchInBetween",
               "Search for an element not present, which has a value in the "
               "range of elements.");
    // DISABLE();
    std::array<value_type, 6> arr{1, 3, 5, 7, 9, 11};
    std::random_device rd;
    std::shuffle(arr.begin(), arr.end(), rd);

    for (auto i{2}; i < 11; i += 2) {
      auto result = lsearch(arr.begin(), arr.end(), i);
      EXPECT_EQ(result, arr.end());
    }
  }

  {
    //=== Test #4
    BEGIN_TEST(tm, "EmptyArray", "Search for an element in an empty array.");
    // DISABLE();
    std::array<value_type, 6> arr{1, 3, 5, 7, 9, 11};

    // Let us simulate an empty range here.
    auto first = arr.begin();
    auto last = arr.begin();
    auto result = lsearch(first, last, 10);
    EXPECT_EQ(result, last);
  }

  tm.summary();
  std::cout << std::endl;

  // Creates a test manager for the DAL class.
  TestManager tm2{"Binary Search Test Suite"};

  {
    //=== Test #1
    BEGIN_TEST(tm2, "BasicSearch",
               "Search for all n elements present in the array.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};

    // Looking for each element from arr in arr.
    for (const auto &e : arr) {
      auto result = bsearch(arr.begin(), arr.end(), e);
      EXPECT_EQ(*result, e);
      EXPECT_EQ(e - 1, std::distance(arr.begin(), result));
    }
  }
  {
    //=== Test #2
    BEGIN_TEST(tm2, "NotPresentToLeft",
               "Search for an element that is not present, whose value is "
               "smaller than the first element of the array.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};

    auto target{-4};
    auto result = bsearch(arr.begin(), arr.end(), target);
    EXPECT_EQ(result, arr.end());
  }

  {
    //=== Test #3
    BEGIN_TEST(tm2, "NotPresentToRight",
               "Search for an element that is not present, whose value is "
               "greater than the last element of the array.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};

    auto target{10};
    auto result = bsearch(arr.begin(), arr.end(), target);
    EXPECT_EQ(result, arr.end());
  }

  {
    //=== Test #4
    BEGIN_TEST(tm2, "NotPresentInBetween",
               "Search for an element that is not present, whose value is "
               "between the first and the last elements of the array.");
    // DISABLE();
    std::array<value_type, 6> arr{1, 3, 5, 7, 9, 11};

    for (auto i{2}; i < 11; i += 2) {
      auto result = bsearch(arr.begin(), arr.end(), i);
      EXPECT_EQ(result, arr.end());
    }
  }

  {
    //=== Test #5
    BEGIN_TEST(tm2, "EmptyRange", "Search for an element on an empty range.");
    // DISABLE();
    std::array<value_type, 6> arr{1, 3, 5, 7, 9, 11};

    // Let us simulate an empty range here.
    auto first = arr.begin();
    auto last = arr.begin();
    auto result = bsearch(first, last, 10);
    EXPECT_EQ(result, last);
  }

  tm2.summary();
  std::cout << std::endl;

  // Creates a test manager for the DAL class.
  TestManager tm3{"Lower Bound Test Suite"};

  {
    //=== Test #1
    BEGIN_TEST(tm3, "EmptyRange", "Lower bound applied to an empty range.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{3};
    auto lb_it = lbound(arr.begin(), arr.begin(), value);
    auto expected_lb_it = std::lower_bound(arr.begin(), arr.begin(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(lb_it, expected_lb_it);
  }
  {
    //=== Test #2
    BEGIN_TEST(tm3, "RangeHasSingleValue",
               "Range has a repeated single value, same as target.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    auto value{1};
    auto lb_it = lbound(arr.begin(), arr.end(), value);
    auto expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(*lb_it, value);
    EXPECT_EQ(lb_it, expected_lb_it);
  }

  {
    //=== Test #3
    BEGIN_TEST(tm3, "RegularCallOddLength", "Regular call, range size is odd.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{3};
    auto lb_it = lbound(arr.begin(), arr.end(), value);
    auto expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(*lb_it, value);
    EXPECT_EQ(lb_it, expected_lb_it);
  }

  {
    //=== Test #4
    BEGIN_TEST(tm3, "LBToTheLeftOddLength",
               "Target element located to the left end of range");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{2};
    auto lb_it = lbound(arr.begin(), arr.end(), value);
    auto expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(*lb_it, value);
    EXPECT_EQ(lb_it, expected_lb_it);
  }

  {
    //=== Test #5
    BEGIN_TEST(tm3, "LBToTheRightOddLength",
               "Target element located to the right end of range.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{4};
    auto lb_it = lbound(arr.begin(), arr.end(), value);
    auto expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(*lb_it, value);
    EXPECT_EQ(lb_it, expected_lb_it);
  }

  {
    //=== Test #6
    BEGIN_TEST(tm3, "LBAtBeginningOddLength", "Target is the first element.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{1};
    auto lb_it = lbound(arr.begin(), arr.end(), value);
    auto expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(*lb_it, value);
    EXPECT_EQ(lb_it, expected_lb_it);
  }

  {
    //=== Test #7
    BEGIN_TEST(tm3, "LBAtEndOddLength", "Target is the first element.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{5};
    auto lb_it = lbound(arr.begin(), arr.end(), value);
    auto expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(*lb_it, value);
    EXPECT_EQ(lb_it, expected_lb_it);
  }

  {
    //=== Test #8
    BEGIN_TEST(tm3, "RangeHasSingleValueLBNotPresent",
               "Range has a repeated single value, target not present.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    auto value{2};
    auto lb_it = lbound(arr.begin(), arr.end(), value);
    auto expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(lb_it, expected_lb_it);
  }

  {
    //=== Test #9
    BEGIN_TEST(tm3, "TargetOutsideLeft",
               "Target is not present and is lower than the first element.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{-2};
    auto lb_it = lbound(arr.begin(), arr.end(), value);
    auto expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(lb_it, arr.begin());
    EXPECT_EQ(lb_it, expected_lb_it);
  }

  {
    //=== Test #10
    BEGIN_TEST(tm3, "TargetOutsideRight",
               "Target is not present and is greater than the last element.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{8};
    auto lb_it = lbound(arr.begin(), arr.end(), value);
    auto expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(lb_it, arr.end());
    EXPECT_EQ(lb_it, expected_lb_it);
  }

  {
    //=== Test #11
    BEGIN_TEST(tm3, "TargetOutsideInBetween",
               "Target is not present and is a value between the first and the "
               "last element.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 3, 3, 5, 5, 5, 7, 7, 7, 9, 9};

    auto value{2};
    auto lb_it = lbound(arr.begin(), arr.end(), value);
    auto expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(lb_it, arr.begin() + 3);
    EXPECT_EQ(lb_it, expected_lb_it);

    value = 4;
    lb_it = lbound(arr.begin(), arr.end(), value);
    expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(lb_it, arr.begin() + 5);
    EXPECT_EQ(lb_it, expected_lb_it);

    value = 6;
    lb_it = lbound(arr.begin(), arr.end(), value);
    expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(lb_it, arr.begin() + 8);
    EXPECT_EQ(lb_it, expected_lb_it);

    value = 8;
    lb_it = lbound(arr.begin(), arr.end(), value);
    expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(lb_it, arr.begin() + 11);
    EXPECT_EQ(lb_it, expected_lb_it);
  }
  {
    //=== Test #12
    BEGIN_TEST(tm3, "RegularCallEvenLength",
               "Regular call, range size is odd.");
    // DISABLE();
    std::array<value_type, 14> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{3};
    auto lb_it = lbound(arr.begin(), arr.end(), value);
    auto expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(*lb_it, value);
    EXPECT_EQ(lb_it, expected_lb_it);
  }

  {
    //=== Test #13
    BEGIN_TEST(tm3, "LBToTheLeftEvenLength",
               "Target element located to the left end of range");
    // DISABLE();
    std::array<value_type, 14> arr{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{2};
    auto lb_it = lbound(arr.begin(), arr.end(), value);
    auto expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(*lb_it, value);
    EXPECT_EQ(lb_it, expected_lb_it);
  }

  {
    //=== Test #14
    BEGIN_TEST(tm3, "LBToTheRightEvenLength",
               "Target element located to the right end of range.");
    // DISABLE();
    std::array<value_type, 14> arr{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{4};
    auto lb_it = lbound(arr.begin(), arr.end(), value);
    auto expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(*lb_it, value);
    EXPECT_EQ(lb_it, expected_lb_it);
  }

  {
    //=== Test #15
    BEGIN_TEST(tm3, "LBAtBeginningEvenLength", "Target is the first element.");
    // DISABLE();
    std::array<value_type, 14> arr{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{1};
    auto lb_it = lbound(arr.begin(), arr.end(), value);
    auto expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(*lb_it, value);
    EXPECT_EQ(lb_it, expected_lb_it);
  }

  {
    //=== Test #16
    BEGIN_TEST(tm3, "LBAtEndEvenLength", "Target is the first element.");
    // DISABLE();
    std::array<value_type, 14> arr{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{5};
    auto lb_it = lbound(arr.begin(), arr.end(), value);
    auto expected_lb_it = std::lower_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(lb_it, nullptr);
    EXPECT_EQ(*lb_it, value);
    EXPECT_EQ(lb_it, expected_lb_it);
  }

  tm3.summary();
  std::cout << std::endl;

  // Creates a test manager for the DAL class.
  TestManager tm4{"Uppert Bound Test Suite"};

  {
    //=== Test #1
    BEGIN_TEST(tm4, "EmptyRange", "Upper bound applied to an empty range.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{3};
    auto ub_it = ubound(arr.begin(), arr.begin(), value);
    auto expected_ub_it = std::upper_bound(arr.begin(), arr.begin(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, expected_ub_it);
  }
  {
    //=== Test #2
    BEGIN_TEST(tm4, "RangeHasSingleValue",
               "Range has a repeated single value, same as target.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    auto value{1};
    auto ub_it = ubound(arr.begin(), arr.end(), value);
    auto expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_EQ(ub_it, expected_ub_it);
  }

  {
    //=== Test #3
    BEGIN_TEST(tm4, "RegularCallOddLength", "Regular call, range size is odd.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{3};
    auto ub_it = ubound(arr.begin(), arr.end(), value);
    auto expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, expected_ub_it);
  }

  {
    //=== Test #4
    BEGIN_TEST(tm4, "UbToTheLeftOddLength",
               "Target element located to the left end of range");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{2};
    auto ub_it = ubound(arr.begin(), arr.end(), value);
    auto expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, expected_ub_it);
  }

  {
    //=== Test #5
    BEGIN_TEST(tm4, "UbToTheRightOddLength",
               "Target element located to the right end of range.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{4};
    auto ub_it = ubound(arr.begin(), arr.end(), value);
    auto expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, expected_ub_it);
  }

  {
    //=== Test #6
    BEGIN_TEST(tm4, "UbAtBeginningOddLength", "Target is the first element.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{1};
    auto ub_it = ubound(arr.begin(), arr.end(), value);
    auto expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, expected_ub_it);
  }

  {
    //=== Test #7
    BEGIN_TEST(tm4, "UbAtEndOddLength", "Target is the first element.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{5};
    auto ub_it = ubound(arr.begin(), arr.end(), value);
    auto expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, expected_ub_it);
  }

  {
    //=== Test #8
    BEGIN_TEST(tm4, "RangeHasSingleValueUbNotPresent",
               "Range has a repeated single value, target not present.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    auto value{2};
    auto ub_it = ubound(arr.begin(), arr.end(), value);
    auto expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, expected_ub_it);
  }

  {
    //=== Test #9
    BEGIN_TEST(tm4, "TargetOutsideLeft",
               "Target is not present and is lower than the first element.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{-2};
    auto ub_it = ubound(arr.begin(), arr.end(), value);
    auto expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, arr.begin());
    EXPECT_EQ(ub_it, expected_ub_it);
  }

  {
    //=== Test #10
    BEGIN_TEST(tm4, "TargetOutsideRight",
               "Target is not present and is greater than the last element.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{8};
    auto ub_it = ubound(arr.begin(), arr.end(), value);
    auto expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, arr.end());
    EXPECT_EQ(ub_it, expected_ub_it);
  }

  {
    //=== Test #11
    BEGIN_TEST(tm4, "TargetOutsideInBetween",
               "Target is not present and is a value between the first and the "
               "last element.");
    // DISABLE();
    std::array<value_type, 13> arr{1, 1, 1, 3, 3, 5, 5, 5, 7, 7, 7, 9, 9};

    auto value{2};
    auto ub_it = ubound(arr.begin(), arr.end(), value);
    auto expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, expected_ub_it);

    value = 4;
    ub_it = ubound(arr.begin(), arr.end(), value);
    expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, expected_ub_it);

    value = 6;
    ub_it = ubound(arr.begin(), arr.end(), value);
    expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, expected_ub_it);

    value = 8;
    ub_it = ubound(arr.begin(), arr.end(), value);
    expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, expected_ub_it);
  }
  {
    //=== Test #12
    BEGIN_TEST(tm4, "RegularCallEvenLength",
               "Regular call, range size is odd.");
    // DISABLE();
    std::array<value_type, 14> arr{1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{3};
    auto ub_it = ubound(arr.begin(), arr.end(), value);
    auto expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, expected_ub_it);
  }

  {
    //=== Test #13
    BEGIN_TEST(tm4, "UbToTheLeftEvenLength",
               "Target element located to the left end of range");
    // DISABLE();
    std::array<value_type, 14> arr{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{2};
    auto ub_it = ubound(arr.begin(), arr.end(), value);
    auto expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, expected_ub_it);
  }

  {
    //=== Test #14
    BEGIN_TEST(tm4, "UbToTheRightEvenLength",
               "Target element located to the right end of range.");
    // DISABLE();
    std::array<value_type, 14> arr{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{4};
    auto ub_it = ubound(arr.begin(), arr.end(), value);
    auto expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, expected_ub_it);
  }

  {
    //=== Test #15
    BEGIN_TEST(tm4, "UbAtBeginningEvenLength", "Target is the first element.");
    // DISABLE();
    std::array<value_type, 14> arr{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{1};
    auto ub_it = ubound(arr.begin(), arr.end(), value);
    auto expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, expected_ub_it);
  }

  {
    //=== Test #16
    BEGIN_TEST(tm4, "UbAtEndEvenLength", "Target is the first element.");
    // DISABLE();
    std::array<value_type, 14> arr{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5};

    auto value{5};
    auto ub_it = ubound(arr.begin(), arr.end(), value);
    auto expected_ub_it = std::upper_bound(arr.begin(), arr.end(), value);
    EXPECT_NE(ub_it, nullptr);
    EXPECT_EQ(ub_it, expected_ub_it);
  }

  tm4.summary();
  std::cout << std::endl;

  // Creates a test manager for the DAL class.
  TestManager tm5{"Recursive Binary Search Test Suite"};

  {
    //=== Test #1
    BEGIN_TEST(tm5, "BasicSearch",
               "Search for all n elements present in the array.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};

    // Looking for each element from arr in arr.
    for (const auto &e : arr) {
      auto *result = bsearch(arr.begin(), arr.end(), e);
      EXPECT_EQ(*result, e);
      EXPECT_EQ(e - 1, std::distance(arr.begin(), result));
    }
  }
  {
    //=== Test #2
    BEGIN_TEST(tm5, "NotPresentToLeft",
               "Search for an element that is not present, whose value is "
               "smaller than the first element of the array.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};

    auto target{-4};
    auto result = bsearch(arr.begin(), arr.end(), target);
    EXPECT_EQ(result, arr.end());
  }

  {
    //=== Test #3
    BEGIN_TEST(tm5, "NotPresentToRight",
               "Search for an element that is not present, whose value is "
               "greater than the last element of the array.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};

    auto target{10};
    auto result = bsearch(arr.begin(), arr.end(), target);
    EXPECT_EQ(result, arr.end());
  }

  {
    //=== Test #4
    BEGIN_TEST(tm5, "NotPresentInBetween",
               "Search for an element that is not present, whose value is "
               "between the first and the last elements of the array.");
    // DISABLE();
    std::array<value_type, 6> arr{1, 3, 5, 7, 9, 11};

    for (auto i{2}; i < 11; i += 2) {
      auto result = bsearch(arr.begin(), arr.end(), i);
      EXPECT_EQ(result, arr.end());
    }
  }

  {
    //=== Test #5
    BEGIN_TEST(tm5, "EmptyRange", "Search for an element on an empty range.");
    // DISABLE();
    std::array<value_type, 6> arr{1, 3, 5, 7, 9, 11};

    // Let us simulate an empty range here.
    auto first = arr.begin();
    auto last = arr.begin();
    auto result = bsearch(first, last, 10);
    EXPECT_EQ(result, last);
  }

  tm5.summary();
  std::cout << std::endl;

  // Creates a test manager for the DAL class.
  TestManager tm6{"Ternary Search Test Suite"};

  {
    //=== Test #1
    BEGIN_TEST(tm6, "BasicSearch",
               "Search for all n elements present in the array.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};

    // Looking for each element from arr in arr.
    for (const auto &e : arr) {
      auto *result = tsearch(arr.begin(), arr.end(), e);
      EXPECT_EQ(*result, e);
      EXPECT_EQ(e - 1, std::distance(arr.begin(), result));
    }
  }
  {
    //=== Test #2
    BEGIN_TEST(tm6, "NotPresentToLeft",
               "Search for an element that is not present, whose value is "
               "smaller than the first element of the array.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};

    auto target{-4};
    auto *result = tsearch(arr.begin(), arr.end(), target);
    EXPECT_EQ(result, arr.end());
  }

  {
    //=== Test #3
    BEGIN_TEST(tm6, "NotPresentToRight",
               "Search for an element that is not present, whose value is "
               "greater than the last element of the array.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};

    auto target{10};
    auto *result = tsearch(arr.begin(), arr.end(), target);
    EXPECT_EQ(result, arr.end());
  }

  {
    //=== Test #4
    BEGIN_TEST(tm6, "NotPresentInBetween",
               "Search for an element that is not present, whose value would "
               "place him inside the array.");
    // DISABLE();
    std::array<value_type, 9> arr{1, 3, 5, 7, 9, 11, 13, 15, 17};
    size_t sz{9};

    for (size_t i{0}; i < arr.size() / 2; i += 2) {
      auto *result = tsearch(arr.begin(), arr.end(), i);
      EXPECT_EQ(result, arr.end());
    }
  }

  {
    //=== Test #5
    BEGIN_TEST(tm6, "EmptyRange", "Search for an element on an empty range.");
    // DISABLE();
    std::array<value_type, 6> arr{1, 3, 5, 7, 9, 11};

    // Let us simulate an empty range here.
    auto *first = arr.begin();
    auto *last = arr.begin();
    auto *result = tsearch(first, last, 10);
    EXPECT_EQ(result, last);
  }

  tm6.summary();
  std::cout << std::endl;

  TestManager tm7{"Interpolation Search Test Suite"};

  {
    //=== Test #1
    BEGIN_TEST(tm7, "BasicSearch",
               "Search for all n elements present in the array.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};

    // Looking for each element from arr in arr.
    for (const auto &e : arr) {
      auto result = isearch(arr.begin(), arr.end(), e);
      EXPECT_EQ(*result, e);
      EXPECT_EQ(e - 1, std::distance(arr.begin(), result));
    }
  }
  {
    //=== Test #2
    BEGIN_TEST(tm7, "NotPresentToLeft",
               "Search for an element that is not present, whose value is "
               "smaller than the first element of the array.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};

    auto target{-4};
    auto result = isearch(arr.begin(), arr.end(), target);
    EXPECT_EQ(result, arr.end());
  }

  {
    //=== Test #3
    BEGIN_TEST(tm7, "NotPresentToRight",
               "Search for an element that is not present, whose value is "
               "greater than the last element of the array.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};

    auto target{10};
    auto result = isearch(arr.begin(), arr.end(), target);
    EXPECT_EQ(result, arr.end());
  }

  {
    //=== Test #4
    BEGIN_TEST(tm7, "NotPresentInBetween",
               "Search for an element that is not present, whose value is "
               "between the first and the last elements of the array.");
    // DISABLE();
    std::array<value_type, 6> arr{1, 3, 5, 7, 9, 11};

    for (auto i{2}; i < 11; i += 2) {
      auto result = isearch(arr.begin(), arr.end(), i);
      EXPECT_EQ(result, arr.end());
    }
  }

  {
    //=== Test #5
    BEGIN_TEST(tm7, "EmptyRange", "Search for an element on an empty range.");
    // DISABLE();
    std::array<value_type, 6> arr{1, 3, 5, 7, 9, 11};

    // Let us simulate an empty range here.
    auto first = arr.begin();
    auto last = arr.begin();
    auto result = isearch(first, last, 10);
    EXPECT_EQ(result, last);
  }

  {
    //=== Test #6
    BEGIN_TEST(tm7, "SingleElement",
               "Busca em um array com apenas um elemento.");
    std::array<value_type, 1> arr{42};
    // Como o array possui somente um elemento, espera-se que se busque esse
    // elemento.
    auto result = isearch(arr.begin(), arr.end(), 42);
    EXPECT_EQ(*result, 42);
  }

  {
    //=== Test #7
    BEGIN_TEST(tm7, "TwoElements", "Busca em um array com dois elementos.");
    std::array<value_type, 2> arr{10, 20};

    // Buscando o primeiro elemento:
    auto result1 = isearch(arr.begin(), arr.end(), 10);
    EXPECT_EQ(*result1, 10);

    // Buscando o segundo elemento:
    auto result2 = isearch(arr.begin(), arr.end(), 20);
    EXPECT_EQ(*result2, 20);

    // Buscando um valor que não existe (deve retornar arr.end()):
    auto result3 = isearch(arr.begin(), arr.end(), 15);
    EXPECT_EQ(result3, arr.end());
  }

  {
    //=== Test #8
    BEGIN_TEST(tm7, "NonUniformDistribution",
               "Busca em um array ordenado que não está em PA perfeita.");
    // Neste array os intervalos entre os elementos não são constantes:
    // Diferenças: 1, 2, 3, 4, 5.
    std::array<value_type, 6> arr{1, 2, 4, 7, 11, 16};

    // Apesar de não estar em PA exata, a função isearch pode localizar
    // os valores que coincidirem com os presentes no array.
    auto result_first = isearch(arr.begin(), arr.end(), 1);
    EXPECT_EQ(*result_first, 1);

    auto result_middle = isearch(arr.begin(), arr.end(), 7);
    EXPECT_EQ(*result_middle, 7);

    auto result_last = isearch(arr.begin(), arr.end(), 16);
    EXPECT_EQ(*result_last, 16);
  }

  {
    //=== Test #9
    BEGIN_TEST(
        tm7, "ValueOutsideNonUniform",
        "Busca por um valor ausente em um array ordenado não uniformemente.");
    std::array<value_type, 6> arr{1, 2, 4, 7, 11, 16};

    // Buscando um valor que não existe. Neste caso, espera-se que o retorno
    // seja arr.end()
    auto result = isearch(arr.begin(), arr.end(), 5);
    EXPECT_EQ(result, arr.end());
  }
  tm7.summary();
  std::cout << std::endl;

  TestManager tm8{"Exponential Search Test Suite"};

  {
    //=== Test #1
    BEGIN_TEST(tm8, "BasicSearch",
               "Search for all n elements present in the array.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};

    // Looking for each element from arr in arr.
    for (const auto &e : arr) {
      auto result = esearch(arr.begin(), arr.end(), e);
      EXPECT_EQ(*result, e);
      EXPECT_EQ(e - 1, std::distance(arr.begin(), result));
    }
  }
  {
    //=== Test #2
    BEGIN_TEST(tm8, "NotPresentToLeft",
               "Search for an element that is not present, whose value is "
               "smaller than the first element of the array.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};

    auto target{-4};
    auto result = esearch(arr.begin(), arr.end(), target);
    EXPECT_EQ(result, arr.end());
  }

  {
    //=== Test #3
    BEGIN_TEST(tm8, "NotPresentToRight",
               "Search for an element that is not present, whose value is "
               "greater than the last element of the array.");
    // DISABLE();
    std::array<value_type, 7> arr{1, 2, 3, 4, 5, 6, 7};

    auto target{10};
    auto result = esearch(arr.begin(), arr.end(), target);
    EXPECT_EQ(result, arr.end());
  }

  {
    //=== Test #4
    BEGIN_TEST(tm8, "NotPresentInBetween",
               "Search for an element that is not present, whose value is "
               "between the first and the last elements of the array.");
    // DISABLE();
    std::array<value_type, 6> arr{1, 3, 5, 7, 9, 11};

    for (auto i{2}; i < 11; i += 2) {
      auto result = esearch(arr.begin(), arr.end(), i);
      EXPECT_EQ(result, arr.end());
    }
  }

  {
    //=== Test #5
    BEGIN_TEST(tm8, "EmptyRange", "Search for an element on an empty range.");
    // DISABLE();
    std::array<value_type, 6> arr{1, 3, 5, 7, 9, 11};

    // Let us simulate an empty range here.
    auto first = arr.begin();
    auto last = arr.begin();
    auto result = esearch(first, last, 10);
    EXPECT_EQ(result, last);
  }

  tm8.summary();
  std::cout << std::endl;

  return EXIT_SUCCESS;
}
