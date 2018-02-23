#include <type_traits>

#include <catch2/catch.hpp>

#include <algae/literals.h>
#include <algae/vector.h>

namespace lit = algae::literals;

#define REQUIRE_DOT(fst, snd) REQUIRE(dot((fst), (snd)) == answer)

TEST_CASE("constexpr vectors", "[vector]") {
  SECTION("vector of int literals") {
    constexpr algae::vector<int, 3> _ = lit::vec | 0 | 1 | 2 | lit::end;
  }
  SECTION("vector of class-type literals") {
    struct foo {};
    constexpr algae::vector<foo, 3> _ =
        lit::vec | foo{} | foo{} | foo{} | lit::end;
  }
  SECTION("vector of class-type with no copy constructor literals") {
    struct foo {
      foo(foo const&) = delete;
      constexpr foo(foo&&) = default;
    };
    constexpr algae::vector<foo, 3> _ =
        lit::vec | foo{} | foo{} | foo{} | lit::end;
  }
  SECTION("dot product of no-copy class vectors") {
    struct foo {
      constexpr foo() = default;
      foo(foo const&) = delete;
      foo operator=(foo const&) = delete;
      constexpr foo(foo&&) = default;
      constexpr foo& operator=(foo&&) = default;
      constexpr foo(int) {}
      constexpr foo operator+(foo const&) && { return foo(); }
      constexpr foo operator*(foo const&)const& { return foo(); }
    };
    constexpr algae::vector<foo, 3> v =
        lit::vec | foo() | foo() | foo() | lit::end;
    constexpr algae::vector<foo, 3> u =
        lit::vec | foo() | foo() | foo() | lit::end;
    constexpr foo dot_prod = dot(v, u);
  }
}

TEST_CASE("literals", "[vector]") {
  SECTION("all-same-type") {
    auto v = lit::vec | 0 | 1 | 2 | lit::end;
    REQUIRE(std::is_same<decltype(v), algae::vector<int, 3>>());
    REQUIRE(v[0] == 0);
    REQUIRE(v[1] == 1);
    REQUIRE(v[2] == 2);
    REQUIRE(v == algae::make_vector(0, 1, 2));
  }
  SECTION("first-different-type") {
    auto v0 = 0.0;
    auto v1 = 1;
    auto v2 = 2;
    auto v = lit::vec | v0 | v1 | v2 | lit::end;
    REQUIRE(std::is_same<decltype(v), algae::vector<double, 3>>());
    REQUIRE(v[0] == 0.0);
    REQUIRE(v[1] == 1.0);
    REQUIRE(v[2] == 2.0);
    REQUIRE(v == algae::make_vector(0., 1, 2));
  }
}

TEST_CASE("equality") {
  SECTION("same types") {
    auto v = lit::vec | 0 | 1 | 2 | lit::end;
    auto u = lit::vec | 0 | 1 | 2 | lit::end;
    auto w = lit::vec | 1 | 2 | 3 | lit::end;
    REQUIRE(v == u);
    REQUIRE(not(v != u));
    REQUIRE(v != w);
    REQUIRE(not(v == w));
  }
  SECTION("different types") {
    auto v = lit::vec | 0.0 | 1 | 2 | lit::end;
    auto u = lit::vec | 0 | 1 | 2 | lit::end;
    auto w = lit::vec | 1 | 2 | 3 | lit::end;
    REQUIRE(v == u);
    REQUIRE(not(v != u));
    REQUIRE(v != w);
    REQUIRE(not(v == w));
  }
}

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
    auto v = lit::vec | -1 | 1 | 2 | lit::end;
    auto u = lit::vec | 1 | -1 | 1 | lit::end;
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
    auto v = lit::vec | -1 | 1 | 2 | 1 | lit::end;
    auto u = lit::vec | 1 | -1 | -1 | 8 | lit::end;
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
    auto v = lit::vec | 1 | 0 | 1 | 2 | lit::end;
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
