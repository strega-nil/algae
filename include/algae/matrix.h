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
template <typename T, std::size_t Width>
class matrix_row {
  T underlying_[Width];

public:
  template <typename, std::size_t, std::size_t>
  friend class matrix;

  class iterator {
    T* current_;
    constexpr iterator(T* ptr) : current_(ptr) {}

  public:
    template <typename T, std::size_t Width>
    friend class matrix_row;

    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    constexpr bool operator==(iterator other) {
      return current_ == other.current_;
    }
    constexpr bool operator!=(iterator other) {
      return current_ != other.current_;
    }
    constexpr bool operator<(iterator other) {
      return current_ < other.current_;
    }
    constexpr bool operator>(iterator other) {
      return current_ > other.current_;
    }
    constexpr bool operator<=(iterator other) {
      return current_ <= other.current_;
    }
    constexpr bool operator>=(iterator other) {
      return current_ >= other.current_;
    }

    constexpr reference operator*() { return *current_; }
    constexpr pointer operator->() { return current_; }

    constexpr iterator& operator++() {
      ++current_;
      return *this;
    }
    constexpr iterator operator++(int) { return iterator(current_++); }
    constexpr iterator& operator--() {
      --current_;
      return *this;
    }
    constexpr iterator operator--(int) { return iterator(current_--); }

    constexpr iterator& operator+=(difference_type dif) {
      current_ += dif;
      return *this;
    }
    constexpr iterator operator+(difference_type dif) const {
      return iterator(current_ + dif);
    }
    constexpr friend iterator operator+(difference_type dif, iterator self) {
      return iterator(self.current_ + dif);
    }
    constexpr iterator& operator-=(difference_type dif) {
      current_ -= dif;
      return *this;
    }
    constexpr iterator operator-(difference_type dif) const {
      return iterator(current_ - dif);
    }
    constexpr difference_type operator-(iterator other) const {
      return current_ - other.current_;
    }

    constexpr reference operator[](difference_type dif) {
      return current_[dif];
    }
  };
  class const_iterator {
    T const* current_;
    constexpr const_iterator(T* ptr) : current_(ptr) {}

  public:
    template <typename T, std::size_t Width>
    friend class matrix_row;

    using value_type = T;
    using reference = T const&;
    using pointer = T const*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    constexpr bool operator==(iterator other) {
      return current_ == other.current_;
    }
    constexpr bool operator!=(iterator other) {
      return current_ != other.current_;
    }
    constexpr bool operator<(iterator other) {
      return current_ < other.current_;
    }
    constexpr bool operator>(iterator other) {
      return current_ > other.current_;
    }
    constexpr bool operator<=(iterator other) {
      return current_ <= other.current_;
    }
    constexpr bool operator>=(iterator other) {
      return current_ >= other.current_;
    }

    constexpr reference operator*() { return *current_; }
    constexpr pointer operator->() { return current_; }

    constexpr iterator& operator++() {
      ++current_;
      return *this;
    }
    constexpr iterator operator++(int) { return iterator(current_++); }
    constexpr iterator& operator--() {
      --current_;
      return *this;
    }
    constexpr iterator operator--(int) { return iterator(current_--); }

    constexpr iterator& operator+=(difference_type dif) {
      current_ += dif;
      return *this;
    }
    constexpr iterator operator+(difference_type dif) const {
      return iterator(current_ + dif);
    }
    constexpr friend iterator operator+(difference_type dif, iterator self) {
      return iterator(self.current_ + dif);
    }
    constexpr iterator& operator-=(difference_type dif) {
      current_ -= dif;
      return *this;
    }
    constexpr iterator operator-(difference_type dif) const {
      return iterator(current_ - dif);
    }
    constexpr difference_type operator-(iterator other) const {
      return current_ - other.current_;
    }

    constexpr reference operator[](difference_type dif) {
      return current_[dif];
    }
  };
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
class matrix_row_iterator {
  matrix_row<T, Width>* current_;

  constexpr matrix_row_iterator(matrix_row<T, Width>* underlying_)
      : current_(underlying_) {}

public:
  template <typename T, std::size_t Height, std::size_t Width>
  friend class matrix;

  using value_type = matrix_row;
  using reference = matrix_row&;
  using pointer = matrix_row*;
  using difference_type = std::ptrdiff_t;
  using matrix_row_iterator_category = std::random_access_iterator_tag;

  constexpr bool operator==(matrix_row_iterator other) {
    return current_ == other.current_;
  }
  constexpr bool operator!=(matrix_row_iterator other) {
    return current_ != other.current_;
  }
  constexpr bool operator<(matrix_row_iterator other) {
    return current_ < other.current_;
  }
  constexpr bool operator>(matrix_row_iterator other) {
    return current_ > other.current_;
  }
  constexpr bool operator<=(matrix_row_iterator other) {
    return current_ <= other.current_;
  }
  constexpr bool operator>=(matrix_row_iterator other) {
    return current_ >= other.current_;
  }

  constexpr reference operator*() { return *current_; }
  constexpr pointer operator->() { return current_; }

  constexpr matrix_row_iterator& operator++() {
    ++current_;
    return *this;
  }
  constexpr matrix_row_iterator operator++(int) {
    return matrix_row_iterator(current_++);
  }
  constexpr matrix_row_iterator& operator--() {
    --current_;
    return *this;
  }
  constexpr matrix_row_iterator operator--(int) {
    return matrix_row_iterator(current_--);
  }

  constexpr matrix_row_iterator& operator+=(difference_type dif) {
    current_ += dif;
    return *this;
  }
  constexpr matrix_row_iterator operator+(difference_type dif) const {
    return matrix_row_iterator(current_ + dif);
  }
  constexpr friend matrix_row_iterator
  operator+(difference_type dif, matrix_row_iterator self) {
    return matrix_row_iterator(self.current_ + dif);
  }
  constexpr matrix_row_iterator& operator-=(difference_type dif) {
    current_ -= dif;
    return *this;
  }
  constexpr matrix_row_iterator operator-(difference_type dif) const {
    return matrix_row_iterator(current_ - dif);
  }
  constexpr difference_type operator-(matrix_row_iterator other) const {
    return current_ - other.current_;
  }

  constexpr reference operator[](difference_type dif) { return current_[dif]; }
};

template <typename T, std::size_t Width>
class matrix_const_row_iterator {
  matrix_row<T, Width> const* current_;

  constexpr matrix_const_row_iterator(matrix_row<T, Width> const* underlying_)
      : current_(underlying_) {}

public:
  template <typename T, std::size_t Height, std::size_t Width>
  friend class matrix;

  using value_type = matrix_row;
  using reference = matrix_row const&;
  using pointer = matrix_row const*;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

  constexpr bool operator==(matrix_const_row_iterator other) {
    return current_ == other.current_;
  }
  constexpr bool operator!=(matrix_const_row_iterator other) {
    return current_ != other.current_;
  }
  constexpr bool operator<(matrix_const_row_iterator other) {
    return current_ < other.current_;
  }
  constexpr bool operator>(matrix_const_row_iterator other) {
    return current_ > other.current_;
  }
  constexpr bool operator<=(matrix_const_row_iterator other) {
    return current_ <= other.current_;
  }
  constexpr bool operator>=(matrix_const_row_iterator other) {
    return current_ >= other.current_;
  }

  constexpr reference operator*() { return *current_; }
  constexpr pointer operator->() { return current_; }

  constexpr matrix_const_row_iterator& operator++() {
    ++current_;
    return *this;
  }
  constexpr matrix_const_row_iterator operator++(int) {
    return matrix_const_row_iterator(current_++);
  }
  constexpr matrix_const_row_iterator& operator--() {
    --current_;
    return *this;
  }
  constexpr matrix_const_row_iterator operator--(int) {
    return matrix_const_row_iterator(current_--);
  }

  constexpr matrix_const_row_iterator& operator+=(difference_type dif) {
    current_ += dif;
    return *this;
  }
  constexpr matrix_const_row_iterator operator+(difference_type dif) const {
    return matrix_const_row_iterator(current_ + dif);
  }
  constexpr friend matrix_const_row_iterator
  operator+(difference_type dif, matrix_const_row_iterator self) {
    return matrix_const_row_iterator(self.current_ + dif);
  }
  constexpr matrix_const_row_iterator& operator-=(difference_type dif) {
    current_ -= dif;
    return *this;
  }
  constexpr matrix_const_row_iterator operator-(difference_type dif) const {
    return matrix_const_row_iterator(current_ - dif);
  }
  constexpr difference_type operator-(matrix_const_row_iterator other) const {
    return current_ - other.current_;
  }

  constexpr reference operator[](difference_type dif) { return current_[dif]; }
};

template <typename T, std::size_t Height, std::size_t Width>
class matrix {
  std::array<matrix_row<T, Width>, Height> underlying_;

public:
  using row_iterator = matrix_row_iterator<T, Width>;
  using const_row_iterator = matrix_const_row_iterator<T, Width>;
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
