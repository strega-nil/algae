#pragma once

#include <cstddef>

namespace algae {

// matrix_row::iterator

template <typename T>
class matrix_row_iterator {
  T* current_;
  constexpr matrix_row_iterator(T* ptr) : current_(ptr) {}

public:
  template <typename T, std::size_t Width>
  friend class matrix_row;

  using value_type = T;
  using reference = T & ;
  using pointer = T * ;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

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
  constexpr matrix_row_iterator operator++(int) { return matrix_row_iterator(current_++); }
  constexpr matrix_row_iterator& operator--() {
    --current_;
    return *this;
  }
  constexpr matrix_row_iterator operator--(int) { return matrix_row_iterator(current_--); }

  constexpr matrix_row_iterator& operator+=(difference_type dif) {
    current_ += dif;
    return *this;
  }
  constexpr matrix_row_iterator operator+(difference_type dif) const {
    return matrix_row_iterator(current_ + dif);
  }
  constexpr friend matrix_row_iterator operator+(difference_type dif, matrix_row_iterator self) {
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

  constexpr reference operator[](difference_type dif) {
    return current_[dif];
  }
};

template <typename T>
class matrix_row_const_iterator {
  T const* current_;
  constexpr matrix_row_const_iterator(T* ptr) : current_(ptr) {}

public:
  template <typename T, std::size_t Width>
  friend class matrix_row;

  using value_type = T;
  using reference = T const&;
  using pointer = T const*;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

  constexpr bool operator==(matrix_row_const_iterator other) {
    return current_ == other.current_;
  }
  constexpr bool operator!=(matrix_row_const_iterator other) {
    return current_ != other.current_;
  }
  constexpr bool operator<(matrix_row_const_iterator other) {
    return current_ < other.current_;
  }
  constexpr bool operator>(matrix_row_const_iterator other) {
    return current_ > other.current_;
  }
  constexpr bool operator<=(matrix_row_const_iterator other) {
    return current_ <= other.current_;
  }
  constexpr bool operator>=(matrix_row_const_iterator other) {
    return current_ >= other.current_;
  }

  constexpr reference operator*() { return *current_; }
  constexpr pointer operator->() { return current_; }

  constexpr matrix_row_const_iterator& operator++() {
    ++current_;
    return *this;
  }
  constexpr matrix_row_const_iterator operator++(int) { return matrix_row_const_iterator(current_++); }
  constexpr matrix_row_const_iterator& operator--() {
    --current_;
    return *this;
  }
  constexpr matrix_row_const_iterator operator--(int) { return matrix_row_const_iterator(current_--); }

  constexpr matrix_row_const_iterator& operator+=(difference_type dif) {
    current_ += dif;
    return *this;
  }
  constexpr matrix_row_const_iterator operator+(difference_type dif) const {
    return matrix_row_const_iterator(current_ + dif);
  }
  constexpr friend matrix_row_const_iterator operator+(difference_type dif, matrix_row_const_iterator self) {
    return matrix_row_const_iterator(self.current_ + dif);
  }
  constexpr matrix_row_const_iterator& operator-=(difference_type dif) {
    current_ -= dif;
    return *this;
  }
  constexpr matrix_row_const_iterator operator-(difference_type dif) const {
    return matrix_row_const_iterator(current_ - dif);
  }
  constexpr difference_type operator-(matrix_row_const_iterator other) const {
    return current_ - other.current_;
  }

  constexpr reference operator[](difference_type dif) {
    return current_[dif];
  }
};

// matrix::row_iterator

template <typename T, std::size_t Width>
class matrix_iterator_row {
  matrix_row<T, Width>* current_;

  constexpr matrix_iterator_row(matrix_row<T, Width>* underlying_)
    : current_(underlying_) {}

public:
  template <typename T, std::size_t Height, std::size_t Width>
  friend class matrix;

  using value_type = matrix_row;
  using reference = matrix_row&;
  using pointer = matrix_row*;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

  constexpr bool operator==(matrix_iterator_row other) {
    return current_ == other.current_;
  }
  constexpr bool operator!=(matrix_iterator_row other) {
    return current_ != other.current_;
  }
  constexpr bool operator<(matrix_iterator_row other) {
    return current_ < other.current_;
  }
  constexpr bool operator>(matrix_iterator_row other) {
    return current_ > other.current_;
  }
  constexpr bool operator<=(matrix_iterator_row other) {
    return current_ <= other.current_;
  }
  constexpr bool operator>=(matrix_iterator_row other) {
    return current_ >= other.current_;
  }

  constexpr reference operator*() { return *current_; }
  constexpr pointer operator->() { return current_; }

  constexpr matrix_iterator_row& operator++() {
    ++current_;
    return *this;
  }
  constexpr matrix_iterator_row operator++(int) {
    return matrix_iterator_row(current_++);
  }
  constexpr matrix_iterator_row& operator--() {
    --current_;
    return *this;
  }
  constexpr matrix_iterator_row operator--(int) {
    return matrix_iterator_row(current_--);
  }

  constexpr matrix_iterator_row& operator+=(difference_type dif) {
    current_ += dif;
    return *this;
  }
  constexpr matrix_iterator_row operator+(difference_type dif) const {
    return matrix_iterator_row(current_ + dif);
  }
  constexpr friend matrix_iterator_row
    operator+(difference_type dif, matrix_iterator_row self) {
    return matrix_iterator_row(self.current_ + dif);
  }
  constexpr matrix_iterator_row& operator-=(difference_type dif) {
    current_ -= dif;
    return *this;
  }
  constexpr matrix_iterator_row operator-(difference_type dif) const {
    return matrix_iterator_row(current_ - dif);
  }
  constexpr difference_type operator-(matrix_iterator_row other) const {
    return current_ - other.current_;
  }

  constexpr reference operator[](difference_type dif) { return current_[dif]; }
};

template <typename T, std::size_t Width>
class matrix_const_iterator_row {
  matrix_row<T, Width> const* current_;

  constexpr matrix_const_iterator_row(matrix_row<T, Width> const* underlying_)
    : current_(underlying_) {}

public:
  template <typename T, std::size_t Height, std::size_t Width>
  friend class matrix;

  using value_type = matrix_row;
  using reference = matrix_row const&;
  using pointer = matrix_row const*;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

  constexpr bool operator==(matrix_const_iterator_row other) {
    return current_ == other.current_;
  }
  constexpr bool operator!=(matrix_const_iterator_row other) {
    return current_ != other.current_;
  }
  constexpr bool operator<(matrix_const_iterator_row other) {
    return current_ < other.current_;
  }
  constexpr bool operator>(matrix_const_iterator_row other) {
    return current_ > other.current_;
  }
  constexpr bool operator<=(matrix_const_iterator_row other) {
    return current_ <= other.current_;
  }
  constexpr bool operator>=(matrix_const_iterator_row other) {
    return current_ >= other.current_;
  }

  constexpr reference operator*() { return *current_; }
  constexpr pointer operator->() { return current_; }

  constexpr matrix_const_iterator_row& operator++() {
    ++current_;
    return *this;
  }
  constexpr matrix_const_iterator_row operator++(int) {
    return matrix_const_iterator_row(current_++);
  }
  constexpr matrix_const_iterator_row& operator--() {
    --current_;
    return *this;
  }
  constexpr matrix_const_iterator_row operator--(int) {
    return matrix_const_iterator_row(current_--);
  }

  constexpr matrix_const_iterator_row& operator+=(difference_type dif) {
    current_ += dif;
    return *this;
  }
  constexpr matrix_const_iterator_row operator+(difference_type dif) const {
    return matrix_const_iterator_row(current_ + dif);
  }
  constexpr friend matrix_const_iterator_row
    operator+(difference_type dif, matrix_const_iterator_row self) {
    return matrix_const_iterator_row(self.current_ + dif);
  }
  constexpr matrix_const_iterator_row& operator-=(difference_type dif) {
    current_ -= dif;
    return *this;
  }
  constexpr matrix_const_iterator_row operator-(difference_type dif) const {
    return matrix_const_iterator_row(current_ - dif);
  }
  constexpr difference_type operator-(matrix_const_iterator_row other) const {
    return current_ - other.current_;
  }

  constexpr reference operator[](difference_type dif) { return current_[dif]; }
};


}