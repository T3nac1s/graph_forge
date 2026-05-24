# Header-only overlay port template for graph_forge.
# Update REF and SHA512 when publishing to a registry.

set(VCPKG_BUILD_TYPE release)

vcpkg_from_github(
  OUT_SOURCE_PATH SOURCE_PATH
  REPO graph-forge/graph_forge
  REF "v${VERSION}"
  SHA512 0
  HEAD_REF main
)

file(
  COPY "${SOURCE_PATH}/src/"
  DESTINATION "${CURRENT_PACKAGES_DIR}/include"
  FILES_MATCHING
  PATTERN "*.h"
  PATTERN "*.hpp"
)

file(
  INSTALL "${CMAKE_CURRENT_LIST_DIR}/copyright"
  DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
  RENAME copyright
)

file(
  WRITE "${CURRENT_PACKAGES_DIR}/share/${PORT}/graph_forgeConfig.cmake"
  "include(\"\${CMAKE_CURRENT_LIST_DIR}/graph_forgeTargets.cmake\")\n"
)

file(
  WRITE "${CURRENT_PACKAGES_DIR}/share/${PORT}/graph_forgeTargets.cmake"
  "add_library(graph_forge::graph_forge INTERFACE IMPORTED)\n"
  "set_target_properties(graph_forge::graph_forge PROPERTIES\n"
  "  INTERFACE_INCLUDE_DIRECTORIES \"\${CMAKE_CURRENT_LIST_DIR}/../../include\"\n"
  ")\n"
)
