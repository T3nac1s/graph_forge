#include "storage/adjacency_list.h"
#include "utils/concepts.h"

#include <gtest/gtest.h>

namespace graph_forge {
namespace {

TEST(AdjacencyList, UnweightedStoresNeighbors) {
  UnweightedAdjacencyList graph(4, 6);
  EXPECT_EQ(graph.size(), 4u);

  graph.InsertEdge(0, 1);
  graph.InsertEdge(0, 2);
  graph.InsertEdge(1, 3);

  EXPECT_EQ(graph[0].size(), 2u);
  EXPECT_EQ(graph[1].size(), 1u);
  EXPECT_EQ(graph[2].size(), 0u);

  const UnweightedAdjacencyList& const_graph = graph;
  EXPECT_EQ(const_graph[0].size(), 2u);
  static_assert(UnweightedGraph<UnweightedAdjacencyList>);
}

TEST(AdjacencyList, WeightedStoresNeighborWeights) {
  WeightedAdjacencyList<long long> graph(3, 4);
  graph.InsertEdge(0, 1, 10);
  graph.InsertEdge(1, 2, 20);

  EXPECT_EQ(graph[0][0].first, 1u);
  EXPECT_EQ(graph[0][0].second, 10);
  EXPECT_EQ(graph[1][0].second, 20);

  const WeightedAdjacencyList<long long>& const_graph = graph;
  EXPECT_EQ(const_graph[1][0].first, 2u);
  static_assert(WeightedGraph<WeightedAdjacencyList<long long>>);
}

TEST(AdjacencyList, ReserveConstructorAcceptsEdgeCount) {
  UnweightedAdjacencyList graph(10, 100);
  for (size_t i = 0; i < 9; ++i) {
    graph.InsertEdge(i, i + 1);
  }
  EXPECT_EQ(graph[0].size(), 1u);
  EXPECT_EQ(graph[8].size(), 1u);
}

TEST(AdjacencyList, ZeroVertexReserveConstructor) {
  UnweightedAdjacencyList graph(0, 10);
  EXPECT_EQ(graph.size(), 0u);

  WeightedAdjacencyList<int> weighted_graph(0, 10);
  EXPECT_EQ(weighted_graph.size(), 0u);
}

}  // namespace
}  // namespace graph_forge
