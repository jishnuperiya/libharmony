#********* Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
#**
#**
#**  Version : $Header:$
#**
#**
#**  Purpose : CMake build script for the harmony project.
#**
#**
#**  See Also: https://cmake.org/cmake/help/latest/
#**            for more on the CMake language.
#**
#**            https://crascit.com/2015/03/28/enabling-cxx11-in-cmake/
#**            for more on specifying the C++ standard.
#**
#**            https://stackoverflow.com/a/59108287
#**            for more on specifying compiler options.
#**
#**
#*****************************************************************************

cmake_minimum_required(VERSION 3.20.2)

project(harmony
  VERSION       0.1.0.1
  HOMEPAGE_URL  "https://github.com/jishnuperiya/repo-no-name")

#*****************************************************************************

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(Doxygen    1.9.8  REQUIRED)
find_package(DocTest    2.4.11 REQUIRED)
find_package(RapidCheck        REQUIRED)

set(CMAKE_CXX_STANDARD          23 )
set(CMAKE_CXX_STANDARD_REQUIRED ON )
set(CMAKE_CXX_EXTENSIONS        OFF)

enable_testing()

add_compile_options(-Wall)

#*****************************************************************************

add_library(harmony-lib STATIC
  src/pitch.cpp
  src/frequency.cpp
  src/note.cpp
  src/chord.cpp
  src/progression.cpp
  )

target_link_libraries(harmony-lib)

target_include_directories(harmony-lib PUBLIC src)

set_target_properties(harmony-lib PROPERTIES OUTPUT_NAME harmony)

#*****************************************************************************

add_executable(harmony
  src/main.cpp )

target_link_libraries(harmony
  harmony-lib)

  #*****************************************************************************

add_executable(harmony-test
  test/main.cpp
  test/test_pitch.cpp
  test/test_frequency.cpp
  test/test_note.cpp
  test/test_chord.cpp
  test/test_progression.cpp
  test/test_voicing.cpp
  test/test_note_set.cpp)


if(TARGET rapidcheck)
  if(MSVC)
    target_compile_options(rapidcheck PRIVATE /FIcstdint)
  else()
    target_compile_options(rapidcheck PRIVATE -include cstdint)
  endif()
endif()


target_link_libraries(harmony-test
  harmony-lib
  rapidcheck
  doctest::doctest)

#*****************************************************************************

add_test(NAME harmony.example COMMAND harmony-test)

#*****************************************************************************

#*****************************************************************************#
# Doxygen documentation
#*****************************************************************************#

if(DOXYGEN_FOUND)

  set(DOXYGEN_IN  ${CMAKE_SOURCE_DIR}/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)

  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

  add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
  )

endif()

