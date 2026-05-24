#include "storage/compressed_graph.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

namespace graph_forge {
namespace {

template <typename Range, typename Value>
bool Contains(Range&& range, Value value) {
  return std::ranges::find(range, value) != std::ranges::end(range);
}

TEST(CompressedGraph, UnweightedBuildsCSR) {
  std::vector<std::pair<size_t, size_t>> edges{{0, 1}, {0, 2}, {1, 2}, {2, 0}};
  UnweightedCompressedGraph graph(3, edges);

  EXPECT_EQ(graph.size(), 3u);
  EXPECT_EQ(graph[0].size(), 2u);
  EXPECT_EQ(graph[1].size(), 1u);
  EXPECT_EQ(graph[2].size(), 1u);

  EXPECT_TRUE(Contains(graph[0], size_t{1}));
  EXPECT_TRUE(Contains(graph[0], size_t{2}));
  EXPECT_TRUE(Contains(graph[1], size_t{2}));
  EXPECT_TRUE(Contains(graph[2], size_t{0}));
}

TEST(CompressedGraph, WeightedBuildsCSRWithWeights) {
  std::vector<std::tuple<size_t, size_t, int>> edges{
      {0, 1, 5}, {0, 2, 7}, {1, 2, 3}};
  WeightedCompressedGraph<int> graph(3, edges);

  EXPECT_EQ(graph.size(), 3u);
  EXPECT_EQ(graph[0].size(), 2u);
  EXPECT_EQ(graph[1].size(), 1u);

  std::vector<std::pair<size_t, int>> neighbors(graph[0].begin(),
                                                 graph[0].end());
  std::ranges::sort(neighbors);

  EXPECT_EQ(neighbors[0].first, 1u);
  EXPECT_EQ(neighbors[0].second, 5);
  EXPECT_EQ(neighbors[1].first, 2u);
  EXPECT_EQ(neighbors[1].second, 7);
  EXPECT_EQ(graph[1][0].first, 2u);
  EXPECT_EQ(graph[1][0].second, 3);
}

TEST(CompressedGraph, HandlesEmptyGraph) {
  std::vector<std::pair<size_t, size_t>> edges;
  UnweightedCompressedGraph graph(5, edges);

  EXPECT_EQ(graph.size(), 5u);
  for (size_t u = 0; u < graph.size(); ++u) {
    EXPECT_EQ(graph[u].size(), 0u);
  }
}

}  // namespace
}  // namespace graph_forge
