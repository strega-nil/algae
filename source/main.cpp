#include <complex>
#include <iostream>

#include <algae/literals.h>
#include <algae/matrix.h>
#include <algae/vector.h>

template <typename... Ts> void ignore(Ts&&...) {}

namespace lit = algae::literals;
using namespace std::literals;

int main() {
  algae::matrix<int, 3, 3> mat(
      std::array<std::array<int, 3>, 3>{{{0, 1, 2}, {3, 4, 5}, {6, 7, 8}}});

  return 0;
}
