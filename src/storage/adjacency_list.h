#ifndef GRAPH_FORGE_STORAGE_ADJACENCY_LIST_H_
#define GRAPH_FORGE_STORAGE_ADJACENCY_LIST_H_

#include <ranges>
#include <type_traits>
#include <vector>

#include "utils/concepts.h"

namespace graph_forge {

template <typename Weight>
  requires std::is_arithmetic_v<Weight>
class WeightedAdjacencyList {
 public:
  WeightedAdjacencyList(size_t n) : data_(n) {}

  WeightedAdjacencyList(size_t n, size_t m) : data_(n) {
    if (n == 0)
      return;
    auto average_order = m / n;
    for (auto& list : data_)
      list.reserve(average_order);
  }

  auto InsertEdge(size_t u, size_t v, Weight w) { data_[u].emplace_back(v, w); }

  auto size() const { return data_.size(); }

  const auto& operator[](size_t u) const { return data_[u]; }

 private:
  std::vector<std::vector<std::pair<size_t, Weight>>> data_;
};

class UnweightedAdjacencyList {
 public:
  UnweightedAdjacencyList(size_t n) : data_(n) {}

  UnweightedAdjacencyList(size_t n, size_t m) : data_(n) {
    if (n == 0)
      return;
    auto average_order = m / n;
    for (auto& list : data_)
      list.reserve(average_order);
  }

  auto InsertEdge(size_t u, size_t v) { data_[u].emplace_back(v); }

  auto size() const { return data_.size(); }

  const auto& operator[](size_t u) const { return data_[u]; }

 private:
  std::vector<std::vector<size_t>> data_;
};

static_assert(AnyGraph<UnweightedAdjacencyList>);
static_assert(AnyGraph<WeightedAdjacencyList<int>>);
static_assert(UnweightedGraph<UnweightedAdjacencyList>);
static_assert(WeightedGraph<WeightedAdjacencyList<int>>);

}  // namespace graph_forge

#endif