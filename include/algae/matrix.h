#pragma once

#include <array>
#include <cstddef>
#include <iterator>

#include <algae/iterator.h>

namespace algae {

/*
  NOTE(ubsan): technically a ContiguousIterator,
  but I can't figure out how to write that.
*/

template <typename T>
class matrix_row_iterator;
template <typename T>
class matrix_row_const_iterator;

template <typename T, std::size_t Width>
class matrix_row {
  T underlying_[Width];

public:
  template <typename, std::size_t, std::size_t>
  friend class matrix;

  using iterator = matrix_row_iterator<T>;
  using const_iterator = matrix_row_const_iterator<T>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  constexpr iterator begin() { return iterator(&underlying_[0]); }
  constexpr iterator end() { return iterator(&underlying_[Width]); }
  constexpr const_iterator cbegin() const {
    return const_iterator(&underlying_[0]);
  }
  constexpr const_iterator cend() const {
    return const_iterator(&underlying_[Width]);
  }
  constexpr const_iterator begin() const { return cbegin(); }
  constexpr const_iterator end() const { return cend(); }

  constexpr reverse_iterator rbegin() { return std::reverse_iterator(end()); }
  constexpr reverse_iterator rend() { return std::reverse_iterator(begin()); }
  constexpr const_reverse_iterator crbegin() const {
    return std::reverse_iterator(cend());
  }
  constexpr const_reverse_iterator crend() const {
    return std::reverse_iterator(cbegin());
  }
  constexpr const_reverse_iterator rbegin() const { return crbegin(); }
  constexpr const_reverse_iterator rend() const { return crend(); }
};

template <typename T, std::size_t Width>
class matrix_iterator_row;

template <typename T, std::size_t Width>
class matrix_const_iterator_row;

template <typename T, std::size_t Height, std::size_t Width>
class matrix {
  std::array<matrix_row<T, Width>, Height> underlying_;

public:
  using row_iterator = matrix_iterator_row<T, Width>;
  using const_row_iterator = matrix_const_iterator_row<T, Width>;
  using reverse_row_iterator = std::reverse_iterator<row_iterator>;
  using const_reverse_row_iterator = std::reverse_iterator<const_row_iterator>;

  using iterator = row_iterator;
  using const_iterator = const_row_iterator;
  using reverse_iterator = reverse_row_iterator;
  using const_reverse_iterator = const_reverse_row_iterator;

  // note: this will be done in a better way eventually
  // too lazy to TMP right now
  matrix(std::array<std::array<T, Width>, Height> init) {
    using std::begin;
    using std::end;
    for (auto [dst, src] : range::zip(init, underlying_)) {
      std::move(begin(dst), end(dst), begin(src));
    }
  }

  // TODO(ubsan): actually implement *begin/*end
  // TODO(ubsan): column iterators
};

}

#include <algae/implementation/matrix_iterators.h>