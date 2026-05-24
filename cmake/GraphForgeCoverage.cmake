option(GRAPH_FORGE_ENABLE_COVERAGE "Enable code coverage instrumentation" OFF)

function(graph_forge_apply_coverage target)
  if(NOT GRAPH_FORGE_ENABLE_COVERAGE)
    return()
  endif()

  if(MSVC)
    message(WARNING "Coverage instrumentation is not supported for MSVC.")
    return()
  endif()

  target_compile_options(${target} PRIVATE --coverage -fprofile-arcs -ftest-coverage)
  target_link_options(${target} PRIVATE --coverage)
endfunction()
