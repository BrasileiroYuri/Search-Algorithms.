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
 *
 * while (first != last) {
 *  if (*first == value) {
 *    return first;
 *  }
 *      first++;
 * }
 * return last;
 * }
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
 * Uma versão que trabalha com deslocamentos:
 *
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
  if (first != last) {
    value_type *aux, *mid = first + (last - first) / 2;
    if (*mid == value) {
      return mid;
    } else if (*mid < value) {
      aux = bsearch_rec(mid + 1, last, value);
    } else {
      aux = bsearch_rec(first, mid, value);
    }

    // Quando buscamos um elemento maior que o último elemento válido, aux ==
    // last. Nesse caso, desreferenciar aux pode gerar comportamento indefinido.
    // Então, para garantir, verifico se aux != last antes de desreferenciar.
    if (aux != last and *aux == value) {
      return aux;
    }
  }

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
  while (first != last) {
    value_type *mid = first + (last - first) / 2;
    if (*mid >= value) {
      last = mid;
    } else {
      first = mid + 1;
    }
  }
  return first;
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
  while (first != last) {
    value_type *mid = first + (last - first) / 2;
    if (*mid > value) {
      last = mid;
    } else {
      first = mid + 1;
    }
  }
  return first;
}

value_type *tsearch(value_type *first, value_type *last, value_type value) {
  value_type *backup_last{last}, *mid_l, *mid_r;
  while (first != last) {
    mid_l = first + (last - first) / 3;
    mid_r = mid_l + (last - first) / 3;

    if (*mid_l < value) {
      if (*mid_r < value) {
        first = mid_r + 1;
      } else if (value < *mid_r) {
        first = mid_l + 1;
        last = mid_r;
      } else {
        return mid_r;
      }
    } else if (value < *mid_l) {
      last = mid_l;
    } else {
      return mid_l;
    }
  }
  return backup_last;
}
/**
 * @brief Interpolation search.
 *
 * @details Esse algoritmo é interessante pois a busca por interpolação em
 * arrays ordenados uniformemente (em progressão aritmética) tem complexidade
 * O(log(logN)).
 *
 * @param first Ponteiro para o início do array.
 * @param last Ponteiro para uma posição após o último elemento do array.
 * @param value Valor procurado.
 *
 * @return Indice do local onde 'value' está, ou last caso 'value' não seja
 * encontrado.
 */
value_type *isearch(value_type *first, value_type *last, value_type value) {
  value_type *backup_last{last};

  while (first != last) {

    value_type diff1 = value - *first;
    value_type diff2 = *std::prev(last) - *first;

    if (diff2 == 0) {
      return backup_last;
    }

    value_type proportion = diff1 / diff2;
    value_type off_set = proportion * (last - first - 1);
    value_type *position = first + off_set;

    if (*position == value) {
      return position;
    } else if (*position < value) {
      first = position + 1;
    } else {
      last = position;
    }
  }

  return backup_last;
}

/**
 * @brief Exponential search.
 *
 * @details A busca exponencial é um bom algoritmo para grandes volumes de
 * dados. Tem complexidade semelhante a busca binária, do qual ele faz uso.
 *
 * @param first Ponteiro para o início do array.
 * @param last Ponteiro para uma posição após o último elemento do array.
 * @param value Valor procurado.
 *
 * @return Indice do local onde 'value' está, ou last caso 'value' não seja
 * encontrado.
 */
value_type *esearch(value_type *first, value_type *last, value_type value) {
  return last;
}
} // namespace sa
