# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/mnt/c/git-repo/repo-no-name/build/_deps/rapidcheck-src"
  "/mnt/c/git-repo/repo-no-name/build/_deps/rapidcheck-build"
  "/mnt/c/git-repo/repo-no-name/build/_deps/rapidcheck-subbuild/rapidcheck-populate-prefix"
  "/mnt/c/git-repo/repo-no-name/build/_deps/rapidcheck-subbuild/rapidcheck-populate-prefix/tmp"
  "/mnt/c/git-repo/repo-no-name/build/_deps/rapidcheck-subbuild/rapidcheck-populate-prefix/src/rapidcheck-populate-stamp"
  "/mnt/c/git-repo/repo-no-name/build/_deps/rapidcheck-subbuild/rapidcheck-populate-prefix/src"
  "/mnt/c/git-repo/repo-no-name/build/_deps/rapidcheck-subbuild/rapidcheck-populate-prefix/src/rapidcheck-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/mnt/c/git-repo/repo-no-name/build/_deps/rapidcheck-subbuild/rapidcheck-populate-prefix/src/rapidcheck-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/mnt/c/git-repo/repo-no-name/build/_deps/rapidcheck-subbuild/rapidcheck-populate-prefix/src/rapidcheck-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
