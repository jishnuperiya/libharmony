# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/git-repo/libharmony/out/build/x64-Debug/_deps/doctest-src")
  file(MAKE_DIRECTORY "C:/git-repo/libharmony/out/build/x64-Debug/_deps/doctest-src")
endif()
file(MAKE_DIRECTORY
  "C:/git-repo/libharmony/out/build/x64-Debug/_deps/doctest-build"
  "C:/git-repo/libharmony/out/build/x64-Debug/_deps/doctest-subbuild/doctest-populate-prefix"
  "C:/git-repo/libharmony/out/build/x64-Debug/_deps/doctest-subbuild/doctest-populate-prefix/tmp"
  "C:/git-repo/libharmony/out/build/x64-Debug/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp"
  "C:/git-repo/libharmony/out/build/x64-Debug/_deps/doctest-subbuild/doctest-populate-prefix/src"
  "C:/git-repo/libharmony/out/build/x64-Debug/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/git-repo/libharmony/out/build/x64-Debug/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/git-repo/libharmony/out/build/x64-Debug/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
