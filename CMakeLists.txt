cmake_minimum_required(VERSION 3.20)

project(graph_forge VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(GraphForgeWarnings)

add_library(graph_forge INTERFACE)
add_library(graph_forge::graph_forge ALIAS graph_forge)

target_include_directories(graph_forge INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(graph_forge INTERFACE cxx_std_20)

graph_forge_apply_warnings(graph_forge)

install(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING
  REGEX ".*\\.(h|hpp)$"
)

install(
  TARGETS graph_forge
  EXPORT graph_forgeTargets
)

install(
  EXPORT graph_forgeTargets
  FILE graph_forgeTargets.cmake
  NAMESPACE graph_forge::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/graph_forge
)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/graph_forgeConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/graph_forgeConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/graph_forge
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/graph_forgeConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/graph_forgeConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/graph_forgeConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/graph_forge
)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()
  add_subdirectory(tests)
endif()
