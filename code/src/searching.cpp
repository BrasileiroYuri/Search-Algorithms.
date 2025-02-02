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
 * @brief Função auxiliar para isearch que calcula o índice esperado de 'value'
 *
 * @details Essa função se baseia em conceitos de funções lineares. Isso pois
 * quando temos um conjunto de dados uniformemente distruídos podemos
 * escrevê-los como uma função linear da forma 'T + i * R', onde 'T' é o termo
 * inicial, 'i' o índice - começando em 0 - e 'R' a razão.
 * O outro conceito, que define a variável r abaixo é o de razão de progressão
 * aritmética: (último elemento - primeiro elemento) / (quantidade de elementos
 * - 1). Assim teremos a razão exata ou aproximada, se os dados não estiverem em
 * PA.
 *
 * @param first Ponteiro para o início do array.
 * @param last Ponteiro para uma posição após o último elemento do array.
 * @param value Valor procurado.
 *
 * @return Indice do local onde é esperado que 'value' esteja.
 */
value_type index(value_type *first, value_type *last, value_type value) {

  value_type den = last - first - 1;
  value_type r = (*std::prev(last) - *first) / den;

  // Caso que temos apenas um elemento, ai prev(last) == first e o numerador
  // acima fica 0.
  if (r == 0) {
    return -1;
  }

  return (value - *first) / r;
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

    // Intervalo com apenas um elemento já verifico.
    if (std::distance(first, last) == 1) {
      return (*first == value) ? first : backup_last;
    }

    value_type off_set = index(first, last, value);
    if (off_set == -1)
      return backup_last;

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
 * Curiosamente, podemos implementar "avançando" first e parando quando value
 * for menor que *first, ou "voltando" last até value ser maior que *last. Isso
 * faz sentido quando supomos que o target esteja mais à direita ou à esquerda
 * do array.
 *
 * @param first Ponteiro para o início do array.
 * @param last Ponteiro para uma posição após o último elemento do array.
 * @param value Valor procurado.
 *
 * @return Indice do local onde 'value' está, ou last caso 'value' não seja
 * encontrado.
 */
value_type *esearch(value_type *first, value_type *last, value_type value) {

  value_type off_set{1};
  auto size{last - first};

  while (off_set < size and value > *(first + off_set)) {
    off_set *= 2;
  }

  value_type *new_last = first + off_set < last ? first + off_set : last;

  auto result = bsearch(first + off_set / 2, new_last, value);

  return *result == value ? result : last;
}

} // namespace sa
