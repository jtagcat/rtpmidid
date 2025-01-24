project(rtpmidid)
cmake_minimum_required(VERSION 3.2)
add_definitions("-std=gnu++17 -Wall -Werror")
# set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fstack-protector-strong -fsanitize=address")
# set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fstack-protector-strong")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer")

message(STATUS "Build type ${CMAKE_BUILD_TYPE}")

# if debug build add -O0
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions ("-O0 -g")
else()
  add_definitions ("-O2")
endif()



# Add option to enable/disable tests
option(ENABLE_TESTS "Enable tests" ON)
# option to enable precompiled headers
option(ENABLE_PCH "Enable precompiled headers" ON)

if (ENABLE_PCH)
  # show a log message
  message(STATUS "Precompiled headers enabled")
else(ENABLE_PCH)
  # show a log message
  message(STATUS "Precompiled headers disabled")
endif(ENABLE_PCH)

include(FindPkgConfig)
pkg_check_modules(AVAHI REQUIRED avahi-client)
pkg_check_modules(FMT REQUIRED fmt)
pkg_check_modules(ALSA REQUIRED alsa)


include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/include)
enable_testing()

execute_process(
  COMMAND bash -c "git describe --match \"v[0-9]*\" --tags --abbrev=5 HEAD | sed 's/^v//g' | sed 's/-/~/g' | tr -d '\n'"
  OUTPUT_VARIABLE RTPMIDID_VERSION
)
add_definitions(-DRTPMIDID_VERSION=\"${RTPMIDID_VERSION}\")
message(STATUS "Version ${RTPMIDID_VERSION}")

add_subdirectory(lib)
add_subdirectory(src)

if (ENABLE_TESTS STREQUAL "ON")
  add_subdirectory(tests)
endif()