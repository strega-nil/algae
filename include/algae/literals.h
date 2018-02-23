#pragma once

#include <tuple>
#include <utility>

#include <algae/vector.h>

namespace algae::literals {

struct end_literal_t {};
constexpr static end_literal_t end;

struct vector_literal_t {
  template <typename... Ts>
  struct builder {
    std::tuple<Ts&&...> underlying;

    template <typename T>
    constexpr auto operator|(T&& t) && {
      return builder<Ts..., T>{std::tuple_cat(
          std::move(underlying), std::tuple<T&&>(std::forward<T>(t)))};
    }

    // this is this way because my current version of MSVC
    // doesn't support constexpr lambdas
    struct make_vector_generic {
      template <typename... Ts>
      constexpr auto operator()(Ts&&... ts) {
        return make_vector(std::forward<Ts>(ts)...);
      }
    };

    constexpr auto operator|(literals::end_literal_t) && {
      return std::apply(make_vector_generic{}, std::move(underlying));
    }
  };

  template <typename T>
  constexpr auto operator|(T&& t) const {
    return builder<T>{std::tuple<T&&>(std::forward<T>(t))};
  }
};

constexpr static vector_literal_t vec;

} // namespace algae::literals
