#ifndef GRAPH_FORGE_UTILS_CONCEPTS_H_
#define GRAPH_FORGE_UTILS_CONCEPTS_H_

#include <concepts>
#include <cstddef>
#include <ranges>
#include <type_traits>
#include <utility>

namespace graph_forge {

template <typename Type>
concept UnweightedArrow = requires(const Type& arrow) {
  { arrow } -> std::convertible_to<size_t>;
};

template <typename Type>
concept WeightedArrow = requires(const Type& arrow) {
  { get<0>(arrow) } -> std::convertible_to<size_t>;
  requires std::is_arithmetic_v<std::remove_cvref_t<decltype(get<1>(arrow))>>;
};

template <typename Type>
concept AnyArrow = UnweightedArrow<Type> || WeightedArrow<Type>;

template <typename Type>
concept UnweightedEdge = requires(const Type& edge) {
  { get<0>(edge) } -> std::convertible_to<size_t>;
  { get<1>(edge) } -> std::convertible_to<size_t>;
};

template <typename Type>
concept WeightedEdge = requires(const Type& edge) {
  { get<0>(edge) } -> std::convertible_to<size_t>;
  { get<1>(edge) } -> std::convertible_to<size_t>;
  requires std::is_arithmetic_v<std::remove_cvref_t<decltype(get<2>(edge))>>;
};

template <typename Type>
concept AnyEdge = UnweightedEdge<Type> || WeightedEdge<Type>;

template <typename Type>
concept UnweightedGraph = requires(const Type& graph, size_t u) {
  { std::ranges::size(graph) } -> std::convertible_to<size_t>;
  { graph[u] } -> std::ranges::forward_range;
  requires UnweightedArrow<std::ranges::range_value_t<decltype(graph[u])>>;
};

template <typename Type>
concept WeightedGraph = requires(const Type& graph, size_t u) {
  { std::ranges::size(graph) } -> std::convertible_to<size_t>;
  { graph[u] } -> std::ranges::forward_range;
  requires WeightedArrow<std::ranges::range_value_t<decltype(graph[u])>>;
};

template <typename Type>
concept AnyGraph = UnweightedGraph<Type> || WeightedGraph<Type>;

}  // namespace graph_forge

#endif