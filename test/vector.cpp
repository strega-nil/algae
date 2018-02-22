#include <catch2/catch.hpp>

#include <algae/literals.h>
#include <algae/vector.h>

namespace lit = algae::literals;

#define REQUIRE_DOT(fst, snd) REQUIRE(dot((fst), (snd)) == answer)

TEST_CASE("dot product in R^2", "[vector]") {
  SECTION("dot(0, 0)") {
    auto v = lit::vec | 0 | 0 | lit::end;
    auto answer = 0;
    REQUIRE_DOT(v, v);
  }
  SECTION("dot(<0, 1>, <1, 0>)") {
    auto v = lit::vec | 0 | 1 | lit::end;
    auto u = lit::vec | 1 | 0 | lit::end;
    auto answer = 0;
    REQUIRE_DOT(v, u);
    REQUIRE_DOT(u, v);
  }
  SECTION("dot(<2, 1>, <1, -2>)") {
    auto v = lit::vec | 2 | 1 | lit::end;
    auto u = lit::vec | 1 | -2 | lit::end;
    auto answer = 2 - 2;
    REQUIRE_DOT(v, u);
    REQUIRE_DOT(u, v);
  }
  SECTION("dot(<1, 0>, <1, 0>)") {
    auto v = lit::vec | 1 | 0 | lit::end;
    auto answer = 1 + 0;
    REQUIRE_DOT(v, v);
  }
  SECTION("dot(<1, 1>, <1, 1>)") {
    auto v = lit::vec | 1 | 1 | lit::end;
    auto answer = 1 + 1;
    REQUIRE_DOT(v, v);
  }
  SECTION("dot(<5, -5>, <1, -2>)") {
    auto v = lit::vec | 5 | -5 | lit::end;
    auto u = lit::vec | 1 | -2 | lit::end;
    auto answer = 5 + 10;
    REQUIRE_DOT(v, u);
    REQUIRE_DOT(u, v);
  }
}

TEST_CASE("dot product in R^3", "[vector]") {
  SECTION("dot(0, 0)") {
    auto v = lit::vec | 0 | 0 | 0 | lit::end;
    auto answer = 0;
    REQUIRE_DOT(v, v);
  }
  SECTION("dot(<0, 1, 0>, <1, 0, 1>)") {
    auto v = lit::vec | 0 | 1 | 0 | lit::end;
    auto u = lit::vec | 1 | 0 | 1 | lit::end;
    auto answer = 0;
    REQUIRE_DOT(v, u);
    REQUIRE_DOT(u, v);
  }
  SECTION("dot(<-1, 1, 2>, <1, -1, -1>)") {
    auto v = lit::vec | -1 |  1 | 2 | lit::end;
    auto u = lit::vec |  1 | -1 | 1 | lit::end;
    auto answer = -1 - 1 + 2;
    REQUIRE_DOT(v, u);
    REQUIRE_DOT(u, v);
  }
  SECTION("dot(<1, 1, 1>, <1, 1, 1>)") {
    auto v = lit::vec | 1 | 1 | 1 | lit::end;
    auto answer = 1 + 1 + 1;
    REQUIRE_DOT(v, v);
  }
  SECTION("dot(<1, 0, 1>, <0, 0, 1>)") {
    auto v = lit::vec | 1 | 0 | 1 | lit::end;
    auto u = lit::vec | 0 | 0 | 1 | lit::end;
    auto answer = 0 + 0 + 1;
    REQUIRE_DOT(v, u);
    REQUIRE_DOT(u, v);
  }
  SECTION("dot(<3, 2, 1>, <4, 5, 6>)") {
    auto v = lit::vec | 3 | 2 | 1 | lit::end;
    auto u = lit::vec | 4 | 5 | 6 | lit::end;
    auto answer = 12 + 10 + 6;
    REQUIRE_DOT(v, u);
    REQUIRE_DOT(u, v);
  }
}

TEST_CASE("dot product in R^4", "[vector]") {
  SECTION("dot(0, 0)") {
    auto v = lit::vec | 0 | 0 | 0 | 0 | lit::end;
    auto answer = 0;
    REQUIRE_DOT(v, v);
  }
  SECTION("dot(<0, 1, 1, 0>, <1, 0, 0, 1>)") {
    auto v = lit::vec | 0 | 1 | 1 | 0 | lit::end;
    auto u = lit::vec | 1 | 0 | 0 | 1 | lit::end;
    auto answer = 0 + 0 + 0 + 0;
    REQUIRE_DOT(v, u);
    REQUIRE_DOT(u, v);
  }
  SECTION("dot(<-1, 1, 2, 1>, <1, -1, -1, 8>)") {
    auto v = lit::vec | -1 |  1 |  2 | 1 | lit::end;
    auto u = lit::vec |  1 | -1 | -1 | 8 | lit::end;
    auto answer = -1 - 1 - 2 + 8;
    REQUIRE_DOT(v, u);
    REQUIRE_DOT(u, v);
  }
  SECTION("dot(<1, 1, 1, 1>, <1, 1, 1, 1>)") {
    auto v = lit::vec | 1 | 1 | 1 | 1 | lit::end;
    auto answer = 1 + 1 + 1 + 1;
    REQUIRE_DOT(v, v);
  }
  SECTION("dot(<1, 0, 1, 2>, <0, 0, 1, -1>)") {
    auto v = lit::vec | 1 | 0 | 1 |  2 | lit::end;
    auto u = lit::vec | 0 | 0 | 1 | -1 | lit::end;
    auto answer = 0 + 0 + 1 - 2;
    REQUIRE_DOT(v, u);
    REQUIRE_DOT(u, v);
  }
  SECTION("dot(<4, 3, 2, 1>, <5, 6, 7, 8>") {
    auto v = lit::vec | 4 | 3 | 2 | 1 | lit::end;
    auto u = lit::vec | 5 | 6 | 7 | 8 | lit::end;
    auto answer = 20 + 18 + 14 + 8;
    REQUIRE_DOT(v, u);
    REQUIRE_DOT(u, v);
  }
}

#undef REQUIRE_DOT