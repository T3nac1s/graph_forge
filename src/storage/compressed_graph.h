#ifndef GRAPH_FORGE_STORAGE_COMPRESSED_GRAPH_H_
#define GRAPH_FORGE_STORAGE_COMPRESSED_GRAPH_H_

#include <numeric>
#include <ranges>
#include <span>
#include <type_traits>
#include <vector>

#include "utils/concepts.h"
#include "utils/helpers.h"

namespace graph_forge {

template <typename Weight>
  requires std::is_arithmetic_v<Weight>
class WeightedCompressedGraph {
 public:
  template <std::ranges::forward_range Edges>
  WeightedCompressedGraph(size_t n, const Edges& edges)
      : n_(n), offsets_(n + 1) {
    for (const auto& edge : edges) {
      auto [u, v] = FmtUwEdge(edge);
      ++offsets_[u];
    }
    std::partial_sum(offsets_.begin(), offsets_.end(), offsets_.begin());
    edges_.resize(offsets_[n_]);
    for (const auto& edge : edges) {
      auto [u, v, w] = FmtWtEdge(edge);
      edges_[--offsets_[u]] = std::pair{v, w};
    }
  }

  auto size() const { return n_; }

  auto operator[](size_t u) const {
    return std::span(edges_.data() + offsets_[u],
                     edges_.data() + offsets_[u + 1]);
  }

 private:
  size_t n_;
  std::vector<size_t> offsets_;
  std::vector<std::pair<size_t, Weight>> edges_;
};

class UnweightedCompressedGraph {
 public:
  template <std::ranges::forward_range Edges>
  UnweightedCompressedGraph(size_t n, const Edges& edges)
      : n_(n), offsets_(n + 1) {
    for (const auto& edge : edges) {
      auto [u, v] = FmtUwEdge(edge);
      ++offsets_[u];
    }
    std::partial_sum(offsets_.begin(), offsets_.end(), offsets_.begin());
    edges_.resize(offsets_[n_]);
    for (const auto& edge : edges) {
      auto [u, v] = FmtUwEdge(edge);
      edges_[--offsets_[u]] = v;
    }
  }

  auto size() const { return n_; }

  auto operator[](size_t u) const {
    return std::span(edges_.data() + offsets_[u],
                     edges_.data() + offsets_[u + 1]);
  }

 private:
  size_t n_;
  std::vector<size_t> offsets_;
  std::vector<size_t> edges_;
};

static_assert(AnyGraph<UnweightedCompressedGraph>);
static_assert(AnyGraph<WeightedCompressedGraph<int>>);
static_assert(UnweightedGraph<UnweightedCompressedGraph>);
static_assert(WeightedGraph<WeightedCompressedGraph<int>>);

}  // namespace graph_forge

#endif