#pragma once

#include <array>
#include <iterator>
#include <cstddef>

#include <algae/iterator.h>

// TODO(ubsan): later
namespace algae {

#include "_matrix_row.h"

template <typename T, std::size_t Height, std::size_t Width>
class matrix {
  std::array<matrix_row<T, Width>, Height> underlying_;
public:
  // note: this will be done in a better way eventually
  // too lazy to TMP right now
  matrix(std::array<std::array<T, Width>, Height> init) {
    using std::begin;
    using std::end;
    for (auto& [src, dst] : range::zip(init, underlying_)) {
      std::move(begin(src), end(src), begin(dst));
    }
  }
};

}
