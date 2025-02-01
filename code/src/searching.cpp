/*!
 * \file searching.cpp
 * Binary search, Linear search, Upper bound, lower bound implementation for an
 * array of integers.
 * \author Selan R. dos Santos
 * \date June 17th, 2021.
 */

#include "searching.h"
#include <iterator>

namespace sa {

/*!
 * Performs a **linear search** for `value` in `[first;last)` and returns a
 * pointer to the location of `value` in the range `[first,last]`, or `last` if
 * no such element is found.
 * \param first Pointer to the begining of the data range.
 * \param last Pointer just past the last element of the data range.
 * \param value The value we are looking for.
 */
value_type *lsearch(value_type *first, value_type *last, value_type value) {

  while (first != last) {
    if (*first++ == value) {
      return std::prev(first);
    }
  }
  return last;
}

/*
 * Outra versão, sem std::prev:
 *
 * value_type *lsearch(value_type *first, value_type *last, value_type value) {

  while (first != last) {
    if (*first == value) {
      return first;
    }
        first++;
  }
  return last;
}
*/

/*!
 * Performs a **binary search** for `value` in `[first;last)` and returns a
 * pointer to the location of `value` in the range `[first,last]`, or `last` if
 * no such element is found.
 * \note The range **must** be sorted.
 * \param first Pointer to the begining of the data range.
 * \param last Pointer just past the last element of the data range.
 * \param value The value we are looking for.
 */

/*
 *value_type *bsearch(value_type *first, value_type *last, value_type value) {
  size_t total = last - first;

  size_t low_offset = 0;
  size_t high_offset = total;

  while (low_offset < high_offset) {
    size_t mid_offset = low_offset + (high_offset - low_offset) / 2;
    value_type *mid = first + mid_offset;

    if (*mid == value) {
      return mid; // Elemento encontrado
    } else if (*mid < value) {
      low_offset = mid_offset + 1;
    } else {
      high_offset = mid_offset;
    }
  }
  return last;
}*/

value_type *bsearch(value_type *first, value_type *last, value_type value) {

  value_type *backup_last{last}, *mid;

  while (first != last) {
    mid = first + (last - first) / 2;
    if (*mid == value) {
      return mid;
    } else if (value > *mid) {
      first = mid + 1;
    } else {
      last = mid;
    }
  }
  return backup_last;
}

/*!
 * Performs a **binary search** for `value` in `[first;last)` and returns a
 * pointer to the location of `value` in the range `[first,last]`, or `last` if
 * no such element is found.
 * \note The range **must** be sorted.
 * \param first Pointer to the begining of the data range.
 * \param last Pointer just past the last element of the data range.
 * \param value The value we are looking for.
 */
value_type *bsearch_rec(value_type *first, value_type *last, value_type value) {
  // TODO
  return last; // STUB
}

/*!
 * Returns a pointer to the first element in the range `[first, last)` that is
 * _not less_  than (i.e. greater or equal to) `value`, or `last` if no such
 * element is found.
 * \note The range **must** be sorted.
 * \param first Pointer to the begining of the data range.
 * \param last Pointer just past the last element of the data range.
 * \param value The value we are looking for.
 */
value_type *lbound(value_type *first, value_type *last, value_type value) {
  // TODO
  return first; // STUB
}

/*!
 * Returns a pointer to the first element in the range `[first, last)` that is
 * _greater_  than `value`, or `last` if no such element is found.
 * \note The range **must** be sorted.
 * \param first Pointer to the begining of the data range.
 * \param last Pointer just past the last element of the data range.
 * \param value The value we are looking for.
 */
value_type *ubound(value_type *first, value_type *last, value_type value) {
  // TODO
  return first; // STUB
}

value_type *tsearch(value_type *first, value_type *last, value_type value) {
  // TODO
  return last; // STUB
}
} // namespace sa
