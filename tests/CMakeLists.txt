include(${CMAKE_SOURCE_DIR}/cmake/Dependencies.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/GraphForgeCoverage.cmake)

add_executable(graph_forge_tests
  unit_tests/test_concepts_traits.cpp
  unit_tests/test_helpers.cpp
  unit_tests/test_adjacency_list.cpp
  unit_tests/test_compressed_graph.cpp
  unit_tests/test_umbrella_header.cpp
)

target_link_libraries(graph_forge_tests
  PRIVATE
    graph_forge
    GTest::gtest_main
)

graph_forge_apply_warnings(graph_forge_tests)
graph_forge_apply_coverage(graph_forge_tests)

include(GoogleTest)
gtest_discover_tests(graph_forge_tests)
