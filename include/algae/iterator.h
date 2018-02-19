#pragma once

#include <functional>
#include <iterator>

namespace algae {

namespace iter {

  template <typename T>
  constexpr auto adl_begin(T&& t) {
    using ::std::begin;
    return begin(std::forward<T>(t));
  }
  template <typename T>
  constexpr auto adl_end(T&& t) {
    using ::std::end;
    return end(std::forward<T>(t));
  }
  template <typename T>
  constexpr auto adl_cbegin(T&& t) {
    using ::std::cbegin;
    return cbegin(std::forward<T>(t));
  }
  template <typename T>
  constexpr auto adl_cend(T&& t) {
    using ::std::cend;
    return cend(std::forward<T>(t));
  }
  template <typename T>
  constexpr auto adl_rbegin(T&& t) {
    using ::std::rbegin;
    return rbegin(std::forward<T>(t));
  }
  template <typename T>
  constexpr auto adl_rend(T&& t) {
    using ::std::rend;
    return rend(std::forward<T>(t));
  }
  template <typename T>
  constexpr auto adl_crbegin(T&& t) {
    using ::std::crbegin;
    return crbegin(std::forward<T>(t));
  }
  template <typename T>
  constexpr auto adl_crend(T&& t) {
    using ::std::crend;
    return crend(std::forward<T>(t));
  }

  template <typename Iter1, typename Iter2>
  struct zip_t {
    Iter1 it1;
    Iter2 it2;

    using value_type = std::pair<
      typename std::iterator_traits<Iter1>::value_type,
      typename std::iterator_traits<Iter2>::value_type>;

    using reference = std::pair<
      typename std::iterator_traits<Iter1>::reference,
      typename std::iterator_traits<Iter2>::reference>;

    using pointer = void;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::input_iterator_tag;

    // NOTE: these are implemented not as straight equality
    // if either of the iterators are at an end, they compare unequal
    template <typename End1, typename End2>
    constexpr bool operator==(zip_t<End1, End2> const& other) {
      return (it1 == other.it1) || (it2 == other.it2);
    }
    template <typename End1, typename End2>
    constexpr bool operator!=(zip_t<End1, End2> const& other) {
      return !(*this == other);
    }

    constexpr auto operator*() {
      return reference(*it1, *it2);
    }
    constexpr auto operator*() const {
      return reference(*it1, *it2);
    }

    constexpr auto& operator++() {
      ++it1;
      ++it2;
      return *this;
    }
    constexpr auto operator++(int) {
      return zip_t<Iter1, Iter2>{it1++, it2++};
    }
  };

  template <typename It1, typename It2>
  constexpr auto zip(It1 it1, It2 it2) {
    return zip_t<It1, It2>{it1, it2};
  }

  template <typename It, typename It_end, typename T, typename Op>
  constexpr T accumulate_in_place(It first, It_end last, T init, Op op) {
    for (; first != last; ++first) {
      op(init, *first);
    }
    return init;
  }

}

namespace range {

  template <typename R1, typename R2>
  struct zip_t {
    // should be std::reference_wrapper, but that's apparently non-constexpr
    R1* r1;
    R2* r2;

    constexpr auto begin() {
      return iter::zip(iter::adl_begin(*r1), iter::adl_begin(*r2));
    }
    constexpr auto end() {
      return iter::zip(iter::adl_end(*r1), iter::adl_end(*r2));
    }
    constexpr auto cbegin() const {
      return iter::zip(iter::adl_cbegin(*r1), iter::adl_cbegin(*r2));
    }
    constexpr auto cend() const {
      return iter::zip(iter::adl_cend(*r1), iter::adl_cend(*r2));
    }
    constexpr auto begin() const {
      return cbegin();
    }
    constexpr auto end() const {
      return cend();
    }

    constexpr auto rbegin() {
      return iter::zip(iter::adl_rbegin(*r1), iter::adl_rbegin(*r2));
    }
    constexpr auto rend() {
      return iter::zip(iter::adl_rend(*r1), iter::adl_rend(*r2));
    }
    constexpr auto crbegin() const {
      return iter::zip(iter::adl_crbegin(*r1), iter::adl_crbegin(*r2));
    }
    constexpr auto crend() const {
      return iter::zip(iter::adl_crend(*r1), iter::adl_crend(*r2));
    }
    constexpr auto rbegin() const {
      return crbegin();
    }
    constexpr auto rend() const {
      return crend();
    }
  };

  template <typename R1, typename R2>
  constexpr auto zip(R1& r1, R2& r2) {
    return zip_t<R1, R2>{std::addressof(r1), std::addressof(r2)};
  }

  template <typename Range, typename T, typename Op>
  constexpr T accumulate_in_place(Range& range, T init, Op op) {
    return iter::accumulate_in_place(
      iter::adl_begin(range),
      iter::adl_end(range),
      std::move(init),
      op);
  }

}

}
