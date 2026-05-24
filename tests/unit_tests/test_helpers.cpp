#include "storage/adjacency_list.h"
#include "utils/helpers.h"

#include <gtest/gtest.h>

#include <tuple>
#include <utility>
#include <vector>

namespace graph_forge {
namespace {

TEST(Helpers, ReadVerticesAndWeights) {
  EXPECT_EQ(GetVertex(size_t{3}), 3u);
  EXPECT_EQ(GetVertex(std::pair<size_t, int>{5, 7}), 5u);
  EXPECT_EQ(GetArrowWeight(size_t{3}), 1);
  EXPECT_EQ(GetArrowWeight(std::pair<size_t, int>{5, 7}), 7);
  EXPECT_EQ(GetArrowWeight(std::pair<size_t, size_t>{5, 7}), 7u);

  EXPECT_EQ(GetEdgeWeight(std::pair<size_t, int>{1, 2}), 1);

  auto edge = std::tuple<size_t, size_t, int>{1, 2, 9};
  EXPECT_EQ(GetTail(edge), 1u);
  EXPECT_EQ(GetHead(edge), 2u);
  EXPECT_EQ(GetEdgeWeight(edge), 9);
}

TEST(Helpers, FormatEdgesAndTraverseGraph) {
  UnweightedAdjacencyList graph(2);
  graph.InsertEdge(0, 1);

  auto formatted = FmtUwEdge(std::pair<size_t, size_t>{0, 1});
  EXPECT_EQ(formatted.first, 0u);
  EXPECT_EQ(formatted.second, 1u);

  std::vector<size_t> visited;
  ForEachUw(graph, 0, [&](size_t v) { visited.push_back(v); });
  ASSERT_EQ(visited.size(), 1u);
  EXPECT_EQ(visited[0], 1u);

  WeightedAdjacencyList<int> weighted_graph(2);
  weighted_graph.InsertEdge(0, 1, 4);

  std::vector<std::pair<size_t, int>> weighted_visited;
  ForEachWt(weighted_graph, 0, [&](size_t v, int w) {
    weighted_visited.emplace_back(v, w);
  });
  ASSERT_EQ(weighted_visited.size(), 1u);
  EXPECT_EQ(weighted_visited[0].first, 1u);
  EXPECT_EQ(weighted_visited[0].second, 4);
}

}  // namespace
}  // namespace graph_forge
