cmake_minimum_required(VERSION 3.25)
project(ProfilingTools CXX)

add_executable(baseline src/main.cpp)

# Define options properly
option(ENABLE_TRACY "Enable Tracy profiler" OFF)
option(ENABLE_PERF "Enable GNU profiler" OFF)
option(ENABLE_GPERF_MEM "Enable gperftools memory profiler (tcmalloc)" OFF)
option(ENABLE_GPERF_CPU "Enable gperftools CPU profiler" OFF)

# Tracy
if (ENABLE_TRACY)
    message(STATUS "Tracy profiler enabled")
    add_subdirectory(tracy)
    target_link_libraries(original PUBLIC Tracy::TracyClient)
endif()

# gperftools memory profiler
if (ENABLE_GPERF_MEM)
    message(STATUS "gperftools memory profiler enabled")
    target_link_libraries(original PUBLIC tcmalloc)
endif()

# gperftools CPU profiler
if (ENABLE_GPERF_CPU)
    message(STATUS "gperftools CPU profiler enabled")
    target_link_libraries(original PUBLIC profiler)
endif()
