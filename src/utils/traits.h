#ifndef GRAPH_FORGE_UTILS_TRAITS_H_
#define GRAPH_FORGE_UTILS_TRAITS_H_

#include <cstddef>
#include <limits>
#include <type_traits>
#include <utility>

#include "utils/concepts.h"

namespace graph_forge {

template <typename Type, bool = WeightedArrow<Type>>
struct ArrowTraits;

template <typename Type>
struct ArrowTraits<Type, true> {
  static constexpr bool kIsArrow = AnyArrow<Type>;
  static constexpr bool kIsWeighted = true;
  using Weight = std::remove_cvref_t<decltype(get<1>(std::declval<Type>()))>;
  using Vertex = size_t;
  static constexpr Weight kMaximum = std::numeric_limits<Weight>::max();
  static constexpr Weight kMinimum = std::numeric_limits<Weight>::min();
};

template <typename Type>
struct ArrowTraits<Type, false> {
  static constexpr bool kIsArrow = AnyArrow<Type>;
  static constexpr bool kIsWeighted = false;
  using Weight = int;
  using Vertex = size_t;
  static constexpr Weight kMaximum = std::numeric_limits<Weight>::max();
  static constexpr Weight kMinimum = std::numeric_limits<Weight>::min();
};

template <typename Type, bool = WeightedEdge<Type>>
struct EdgeTraits;

template <typename Type>
struct EdgeTraits<Type, true> {
  static constexpr bool kIsEdge = AnyEdge<Type>;
  static constexpr bool kIsWeighted = true;
  using Weight = std::remove_cvref_t<decltype(get<2>(std::declval<Type>()))>;
  using Vertex = size_t;
  static constexpr Weight kMaximum = std::numeric_limits<Weight>::max();
  static constexpr Weight kMinimum = std::numeric_limits<Weight>::min();
};

template <typename Type>
struct EdgeTraits<Type, false> {
  static constexpr bool kIsEdge = AnyEdge<Type>;
  static constexpr bool kIsWeighted = false;
  using Weight = int;
  using Vertex = size_t;
  static constexpr Weight kMaximum = std::numeric_limits<Weight>::max();
  static constexpr Weight kMinimum = std::numeric_limits<Weight>::min();
};

template <typename Type, bool = WeightedGraph<Type>>
struct GraphTraits;

template <typename Type>
struct GraphTraits<Type, true> {
  static constexpr bool kIsGraph = AnyGraph<Type>;
  static constexpr bool kIsWeighted = true;
  using ArrowType =
      std::ranges::range_value_t<decltype(std::declval<const Type&>()[0])>;
  using Weight = typename ArrowTraits<ArrowType>::Weight;
  using Vertex = size_t;
  static constexpr Weight kMaximum = std::numeric_limits<Weight>::max();
  static constexpr Weight kMinimum = std::numeric_limits<Weight>::min();
};

template <typename Type>
struct GraphTraits<Type, false> {
  static constexpr bool kIsGraph = AnyGraph<Type>;
  static constexpr bool kIsWeighted = false;
  using ArrowType =
      std::ranges::range_value_t<decltype(std::declval<const Type&>()[0])>;
  using Weight = int;
  using Vertex = size_t;
  static constexpr Weight kMaximum = std::numeric_limits<Weight>::max();
  static constexpr Weight kMinimum = std::numeric_limits<Weight>::min();
};

}  // namespace graph_forge

#endif
