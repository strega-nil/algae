#pragma once

#include <utility>

namespace algae {

// constructor tags

struct list_init_t {};
constexpr static list_init_t list_init;

struct range_init_t {};
constexpr static range_init_t range_init;

// for ADL purposes
template <std::size_t Idx, typename T>
constexpr decltype(auto) get(T&& t) {
  return std::forward<T>(t).template get<Idx>();
}

} // namespace algae