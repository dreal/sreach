cmake_minimum_required(VERSION 2.8.7)
project(STATSMT CXX)
set(STATSMT_VERSION_MAJOR 0)
set(STATSMT_VERSION_MINOR 1)

set(CMAKE_COLOR_MAKEFILE ON)
enable_testing()

# Added for CTest
include(CTest)
# Added for External Projects
include(ExternalProject)

set(STATSMT_EXTRA_LINKER_FLAGS "")
set(STATSMT_EXTRA_CXX_FLAGS "")

################################################################
# Set Module Path
################################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

################################################################
# Initialize CXXFLAGS.
################################################################
set(CMAKE_CXX_FLAGS                "-Wall -Wextra -std=c++11 ${STATSMT_EXTRA_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG          "-g -DSTATSMT_DEBUG -DSTATSMT_TRACE -fno-inline")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

################################################################
# Test coverage
################################################################
if("${TESTCOV}" MATCHES "ON")
  include(CodeCoverage)
  message(STATUS "Enable test-coverage")
  set(CMAKE_CXX_FLAGS_DEBUG        "${CMAKE_CXX_FLAGS_DEBUG} -O0 -fprofile-arcs -ftest-coverage --coverage")
  setup_target_for_coverage(cov ${STATSMT_SOURCE_DIR}/script/run_tests.sh coverage)
endif()

################################################################
# Compiler-specific C++11 activation.
################################################################
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
  execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  if (NOT (GCC_VERSION VERSION_GREATER 4.8 OR GCC_VERSION VERSION_EQUAL 4.8))
    message(FATAL_ERROR "${PROJECT_NAME} requires g++ 4.8 or greater.")
  endif ()
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-mismatched-tags -Qunused-arguments")
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # In OSX, clang requires "-stdlib=libc++" to support C++11
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(STATSMT_EXTRA_LINKER_FLAGS "-stdlib=libc++")
  endif ()
else ()
  message(FATAL_ERROR "Your C++ compiler does not support C++11.")
endif ()

################################################################
# Fix Paths
################################################################
SET(CMAKE_SYSTEM_INCLUDE_PATH ${CMAKE_SYSTEM_INCLUDE_PATH}
  /usr/local/include /opt/local/include
  /usr/include/w32api
  /usr/X11R6/include /usr/include/X11
  /usr/pkg/include
  /opt/csw/include /opt/include
  /usr/include /include
  )
SET(CMAKE_SYSTEM_LIBRARY_PATH ${CMAKE_SYSTEM_LIBRARY_PATH}
  $ENV{LD_LIBRARY_PATH}
  /usr/local/lib /opt/local/lib
  /usr/lib/w32api
  /usr/X11R6/lib /usr/lib/X11
  /usr/pkg/lib
  /opt/csw/lib /opt/lib
  /usr/lib /lib
  )
SET(CMAKE_SYSTEM_PROGRAM_PATH ${CMAKE_SYSTEM_PROGRAM_PATH}
  /usr/local/bin /usr/pkg/bin /usr/bin /sbin /bin
  )
SET(CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES
  ${CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES}
  /usr/lib64 /usr/lib32 /usr/lib /lib
  )

################################################################
# Packages
################################################################
# Bison & Flex
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS regex)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(EXTRA_LIBS ${Boost_LIBRARIES} ${EXTRA_LIBS})
endif()
find_package(GSL REQUIRED)
include_directories(${GSL_INCLUDE_DIRS})
set(EXTRA_LIBS ${EXTRA_LIBS} "-L${GSL_LIBRARY_DIRS}" ${GSL_LIBRARIES})

################################################################
# External: set up include dir
################################################################
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

################################################################
# Include Directories
################################################################
include_directories(${STATSMT_SOURCE_DIR})
add_library(replace replace.cpp)
set(STATSMT_LIBS ${STATSMT_LIBS} replace)

add_library(simulation simulation.cpp)
set(STATSMT_LIBS ${STATSMT_LIBS} simulation)

add_library(evalrv evalrv.cpp)
set(STATSMT_LIBS ${STATSMT_LIBS} evalrv)

add_library(prereplace prereplace.cpp)
set(STATSMT_LIBS ${STATSMT_LIBS} prereplace)

add_library(presim presim.cpp)
set(STATSMT_LIBS ${STATSMT_LIBS} presim)

add_library(pdrh2drh pdrh2drh.cpp)
set(STATSMT_LIBS ${STATSMT_LIBS} pdrh2drh)

set(EXTRA_LIBS ${STATSMT_LIBS} ${EXTRA_LIBS})
add_executable(sreach statSMT_sq.cpp)
target_link_libraries(sreach ${EXTRA_LIBS})
