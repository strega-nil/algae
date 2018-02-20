#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <memory>
#include <numeric>
#include <tuple>
#include <type_traits>
#include <utility>

#include <algae/iterator.h>
#include <algae/misc.h>

namespace algae {

template <typename T, std::size_t Rows>
class vector {
  T storage_[Rows];

public:
  template <typename... Ts>
  constexpr vector(algae::list_init_t, Ts&&... ts)
      : storage_{std::forward<Ts>(ts)...} {}

  // TODO(ubsan): wrap these up!
  using iterator = T*;
  using const_iterator = T const*;
  using reverse_iterator = T*;
  using const_reverse_iterator = T const*;

  constexpr iterator begin() noexcept { return std::begin(storage_); }
  constexpr iterator end() noexcept { return std::end(storage_); }
  constexpr const_iterator begin() const noexcept {
    return std::cbegin(storage_);
  }
  constexpr const_iterator end() const noexcept { return std::cend(storage_); }
  constexpr const_iterator cbegin() const noexcept {
    return std::cbegin(storage_);
  }
  constexpr const_iterator cend() const noexcept { return std::cend(storage_); }

  constexpr reverse_iterator rbegin() noexcept { return std::rbegin(storage_); }
  constexpr reverse_iterator rend() noexcept { return std::rend(storage_); }
  constexpr const_reverse_iterator rbegin() const noexcept {
    return std::crbegin(storage_);
  }
  constexpr const_reverse_iterator rend() const noexcept {
    return std::crend(storage_);
  }
  constexpr const_reverse_iterator crbegin() const noexcept {
    return std::crbegin(storage_);
  }
  constexpr const_reverse_iterator crend() const noexcept {
    return std::crend(storage_);
  }

  constexpr auto& operator[](std::size_t idx) & { return storage_[idx]; }
  constexpr auto const& operator[](std::size_t idx) const & {
    return storage_[idx];
  }
  constexpr auto&& operator[](std::size_t idx) && {
    return std::move(storage_[idx]);
  }
  constexpr auto const&& operator[](std::size_t idx) const && {
    return std::move(storage_[idx]);
  }

  template <std::size_t Idx>
  constexpr T& get() & {
    return storage_[Idx];
  }
  template <std::size_t Idx>
  constexpr T const& get() const & {
    return storage_[Idx];
  }
  template <std::size_t Idx>
  constexpr T&& get() && {
    return std::move(storage_[Idx]);
  }
  template <std::size_t Idx>
  constexpr T const&& get() const && {
    return std::move(storage_[Idx]);
  }
};

template <typename T, typename... Ts>
constexpr auto make_vector(T&& first, Ts&&... rest) {
  auto constexpr Rows = sizeof...(Ts) + 1;
  using Type = std::decay_t<T>;

  return vector<Type, Rows>(
      algae::list_init, std::forward<T>(first), std::forward<Ts>(rest)...);
}

namespace impl {
struct dot_op_fn {
  template <typename T, typename Pr>
  constexpr void operator()(T& lhs, Pr const& pr) {
    // if one uses +=, it ICEs MSVC v15.5.6
    lhs = lhs + (pr.first * pr.second);
  }
};
} // namespace impl

template <typename T, std::size_t N>
constexpr auto dot(vector<T, N> const& lhs, vector<T, N> const& rhs) {
  return iter::accumulate_in_place(
      iter::zip(iter::adl_begin(lhs), iter::adl_begin(rhs)),
      iter::zip(iter::adl_end(lhs), iter::adl_end(rhs)),
      T(0),
      impl::dot_op_fn{});
}

} // namespace algae

namespace std {

template <typename T, std::size_t N>
class tuple_size<::algae::vector<T, N>>
    : public std::integral_constant<std::size_t, N> {};

template <std::size_t I, typename T, std::size_t N>
class tuple_element<I, ::algae::vector<T, N>> {
public:
  using type = T;
};

} // namespace std
