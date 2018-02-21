#include <catch2/catch.hpp>

#include <algae/literals.h>
#include <algae/vector.h>

namespace lit = algae::literals;

TEST_CASE("dot product in R^2", "[vector]") {
  {
    auto v = lit::vec | 0 | 0 | lit::end;
    REQUIRE(dot(v, v) == 0);
  }
}

#if 0
void dot2() {
  {
    constexpr auto v = lit::vec | 0 | 0 | lit::end;
    static_assert(dot(v, v) == 0);
  }
  {
    constexpr auto v = lit::vec | 0 | 1 | lit::end;
    constexpr auto u = lit::vec | 1 | 0 | lit::end;
    static_assert(dot(v, u) == 0);
    static_assert(dot(u, v) == 0);
  }
  {
    constexpr auto v = lit::vec | 2 |  1 | lit::end;
    constexpr auto v = lit::vec | 1 | -2 | lit::end;
    static_assert(dot(v, u) == 0);
    static_assert(dot(u, v) == 0);
  }
  {
    constexpr auto v = lit::vec | 1 | 0 | lit::end;
    static_assert(dot(v, v) == 1);
  }
  {
    constexpr auto v = lit::vec | 1 | 1 | lit::end;
    static_assert(dot(v, v) == 2);
  }
  {
    constexpr auto v = lit::vec | 5 | -5 | lit::end;
    constexpr auto v = lit::vec | 1 | -2 | lit::end;
    static_assert(dot(v, u) == -5);
    static_assert(dot(u, v) == -5);
  }
}

void dot3() {
  {
    constexpr auto v = lit::vec | 0 | 0 | 0 | lit::end;
    static_assert(dot(v, v) == 0);
  }
  {
    constexpr auto v = lit::vec | 0 | 1 | 0 | lit::end;
    constexpr auto u = lit::vec | 1 | 0 | 0 | lit::end;
    static_assert(dot(v, u) == 0);
    static_assert(dot(u, v) == 0);
  }
  {
    constexpr auto v = lit::vec | -1 |  1 |  2 | lit::end;
    constexpr auto u = lit::vec |  1 | -1 | -1 | lit::end;
    static_assert(dot(v, u) == 0);
    static_assert(dot(u, v) == 0);
  }
  {
    constexpr auto v = lit::vec | 1 | 1 | 1 | lit::end;
    static_assert(dot(v, v) == 3);
  }
  {
    constexpr auto v = lit::vec | 1 | 0 | 1 | lit::end;
    constexpr auto u = lit::vec | 0 | 0 | 1 | lit::end;
    static_assert(dot(v, u) == 1);
    static_assert(dot(u, v) == 1);
  }
  {
    constexpr auto v = lit::vec | 3 | 2 | 1 | lit::end;
    constexpr auto u = lit::vec | 4 | 5 | 6 | lit::end;
    static_assert(dot(v, u) == 28);
    static_assert(dot(u, v) == 28);
  }
}

void dot4() {
  {
    constexpr auto v = lit::vec | 0 | 0 | 0 | 0 | lit::end;
    static_assert(dot(v, v) == 0);
  }
  {
    constexpr auto v = lit::vec | 0 | 1 | 1 | 0 | lit::end;
    constexpr auto u = lit::vec | 1 | 0 | 0 | 1 | lit::end;
    static_assert(dot(v, u) == 0);
    static_assert(dot(u, v) == 0);
  }
  {
    constexpr auto v = lit::vec | -1 |  1 |  2 | 1 | lit::end;
    constexpr auto u = lit::vec |  1 | -1 | -1 | 8 | lit::end;
    static_assert(dot(v, u) == 8);
    static_assert(dot(u, v) == 8);
  }
  {
    constexpr auto v = lit::vec | 1 | 1 | 1 | 1 | lit::end;
    static_assert(dot(v, v) == 4);
  }
  {
    constexpr auto v = lit::vec | 1 | 0 | 1 |  2 | lit::end;
    constexpr auto u = lit::vec | 0 | 0 | 1 | -1 | lit::end;
    static_assert(dot(v, u) == -1);
    static_assert(dot(u, v) == -1);
  }
  {
    constexpr auto v = lit::vec | 4 | 3 | 2 | 1 | lit::end;
    constexpr auto u = lit::vec | 4 | 5 | 6 | 7 | lit::end;
    static_assert(dot(v, u) == 50);
    static_assert(dot(u, v) == 50);
  }
}
#endif
