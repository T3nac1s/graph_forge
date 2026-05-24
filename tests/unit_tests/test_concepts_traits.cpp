#include "storage/adjacency_list.h"
#include "storage/compressed_graph.h"
#include "utils/concepts.h"
#include "utils/traits.h"

#include <gtest/gtest.h>

#include <tuple>
#include <utility>

namespace graph_forge {
namespace {

TEST(Concepts, DetectArrowAndEdgeTypes) {
  static_assert(UnweightedArrow<size_t>);
  static_assert(WeightedArrow<std::pair<size_t, int>>);
  static_assert(WeightedArrow<std::pair<size_t, size_t>>);
  static_assert(WeightedArrow<std::tuple<size_t, size_t, int>>);

  static_assert(UnweightedEdge<std::pair<size_t, size_t>>);
  static_assert(UnweightedEdge<std::pair<size_t, int>>);
  static_assert(WeightedEdge<std::tuple<size_t, size_t, int>>);
  static_assert(UnweightedEdge<std::tuple<size_t, size_t, int>>);
}

TEST(Traits, ExposeWeightAndFlags) {
  static_assert(ArrowTraits<size_t>::kIsWeighted == false);
  static_assert(ArrowTraits<std::pair<size_t, double>>::kIsWeighted == true);
  static_assert(ArrowTraits<std::pair<size_t, size_t>>::kIsWeighted == true);

  static_assert(EdgeTraits<std::pair<size_t, size_t>>::kIsWeighted == false);
  static_assert(
      EdgeTraits<std::tuple<size_t, size_t, long long>>::kIsWeighted == true);

  static_assert(std::is_same_v<ArrowTraits<std::pair<size_t, int>>::Weight,
                               int>);
  static_assert(
      std::is_same_v<EdgeTraits<std::tuple<size_t, size_t, double>>::Weight,
                     double>);
}

TEST(Traits, GraphTypesModelConceptsAndTraits) {
  static_assert(UnweightedGraph<UnweightedAdjacencyList>);
  static_assert(WeightedGraph<WeightedAdjacencyList<int>>);
  static_assert(UnweightedGraph<UnweightedCompressedGraph>);
  static_assert(WeightedGraph<WeightedCompressedGraph<double>>);

  static_assert(GraphTraits<UnweightedAdjacencyList>::kIsWeighted == false);
  static_assert(GraphTraits<WeightedAdjacencyList<int>>::kIsWeighted == true);
  static_assert(
      std::is_same_v<GraphTraits<WeightedAdjacencyList<int>>::Weight, int>);
}

}  // namespace
}  // namespace graph_forge
