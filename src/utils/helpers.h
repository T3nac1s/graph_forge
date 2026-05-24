#ifndef GRAPH_FORGE_UTILS_HELPERS_H_
#define GRAPH_FORGE_UTILS_HELPERS_H_

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

#include "utils/concepts.h"
#include "utils/traits.h"

namespace graph_forge {

inline auto GetVertex(const AnyArrow auto& arrow) {
  if constexpr (WeightedArrow<std::remove_cvref_t<decltype(arrow)>>) {
    return static_cast<size_t>(get<0>(arrow));
  } else {
    return static_cast<size_t>(arrow);
  }
}

inline auto GetArrowWeight(const AnyArrow auto& arrow) {
  if constexpr (WeightedArrow<std::remove_cvref_t<decltype(arrow)>>) {
    return get<1>(arrow);
  } else {
    return 1;
  }
}

inline auto GetEdgeWeight(const AnyEdge auto& edge) {
  if constexpr (WeightedEdge<std::remove_cvref_t<decltype(edge)>>) {
    return get<2>(edge);
  } else {
    return 1;
  }
}

inline auto GetTail(const AnyEdge auto& edge) {
  return static_cast<size_t>(get<0>(edge));
}

inline auto GetHead(const AnyEdge auto& edge) {
  return static_cast<size_t>(get<1>(edge));
}

inline auto FmtUwArrow(const AnyArrow auto& arrow) {
  return GetVertex(arrow);
}

inline auto FmtWtArrow(const AnyArrow auto& arrow) {
  return std::pair{GetVertex(arrow), GetArrowWeight(arrow)};
}

inline auto FmtUwEdge(const AnyEdge auto& edge) {
  return std::pair{GetTail(edge), GetHead(edge)};
}

inline auto FmtWtEdge(const AnyEdge auto& edge) {
  return std::tuple{GetTail(edge), GetHead(edge), GetEdgeWeight(edge)};
}

template <AnyGraph G, std::invocable<size_t> O>
auto ForEachUw(const G& graph, size_t vertex, O operation) {
  for (const auto& arrow : graph[vertex]) {
    operation(GetVertex(arrow));
  }
}

template <AnyGraph G, std::invocable<size_t, typename GraphTraits<G>::Weight> O>
auto ForEachWt(const G& graph, size_t vertex, O operation) {
  for (const auto& arrow : graph[vertex]) {
    operation(GetVertex(arrow), GetArrowWeight(arrow));
  }
}

}  // namespace graph_forge

#endif