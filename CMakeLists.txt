cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(katas CXX)

add_definitions(-std=c++11)

include(CTest)

if (BUILD_TESTING)
  include(ExternalProject)
  set(GMOCK_URL ${PROJECT_SOURCE_DIR}/3rdparty/gmock-1.7.0.zip)
  if (NOT EXISTS ${GMOCK_URL})
    set(GMOCK_URL https://googlemock.googlecode.com/files/gmock-1.7.0.zip)
  endif()

  ExternalProject_Add(GMock
    URL ${GMOCK_URL}
    URL_HASH SHA1=f9d9dd882a25f4069ed9ee48e70aff1b53e3c5a5
    CMAKE_CACHE_ARGS "-DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}"
    INSTALL_COMMAND ""
    )
  ExternalProject_Get_Property(GMock SOURCE_DIR BINARY_DIR)
  set(GTEST_INCLUDE_DIR ${SOURCE_DIR}/gtest/include)
  set(GTEST_LIBRARY
    ${BINARY_DIR}/gtest/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX})
  set(GTEST_MAIN_LIBRARY
    ${BINARY_DIR}/gtest/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})
  set(GMOCK_INCLUDE_DIR ${SOURCE_DIR}/include)
  set(GMOCK_LIBRARY
    ${BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gmock${CMAKE_STATIC_LIBRARY_SUFFIX})
  set(GMOCK_MAIN_LIBRARY
    ${BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gmock_main${CMAKE_STATIC_LIBRARY_SUFFIX})
  find_package(GTest REQUIRED)
  set(GMOCK_INCLUDE_DIRS ${GMOCK_INCLUDE_DIR} ${GTEST_INCLUDE_DIRS})
  set(GMOCK_BOTH_LIBRARIES
    ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY} ${GTEST_BOTH_LIBRARIES})

  include_directories(${GMOCK_INCLUDE_DIRS})

  add_subdirectory(karate_chop)
endif()

# vim: set et sw=2 :
