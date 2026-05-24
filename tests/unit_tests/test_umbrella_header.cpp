#include "graph_forge/graph_forge.hpp"

#include <gtest/gtest.h>

namespace graph_forge {
namespace {

TEST(UmbrellaHeader, IncludesAllModules) {
  UnweightedAdjacencyList graph(1);
  graph.InsertEdge(0, 0);
  EXPECT_EQ(graph.size(), 1u);

  static_assert(AnyGraph<UnweightedAdjacencyList>);
  static_assert(UnweightedArrow<size_t>);
}

}  // namespace
}  // namespace graph_forge
