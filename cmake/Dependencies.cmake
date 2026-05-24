include(FetchContent)

option(GRAPH_FORGE_USE_SYSTEM_GTEST
       "Use system-installed Google Test instead of FetchContent" OFF)

if(DEFINED ENV{GRAPH_FORGE_GTEST_URL})
  set(GRAPH_FORGE_GTEST_URL "$ENV{GRAPH_FORGE_GTEST_URL}")
else()
  set(GRAPH_FORGE_GTEST_URL
      "https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip")
endif()

set(FETCHCONTENT_BASE_DIR
    "${CMAKE_SOURCE_DIR}/.cache/fetchcontent"
    CACHE PATH "Directory for FetchContent downloads")

if(GRAPH_FORGE_USE_SYSTEM_GTEST)
  find_package(GTest 1.15 REQUIRED)
else()
  FetchContent_Declare(
    googletest
    URL ${GRAPH_FORGE_GTEST_URL}
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()
