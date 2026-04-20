# CMake generated Testfile for 
# Source directory: /mnt/c/git-repo/repo-no-name
# Build directory: /mnt/c/git-repo/repo-no-name/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[harmony.example]=] "/mnt/c/git-repo/repo-no-name/build/harmony-test")
set_tests_properties([=[harmony.example]=] PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/git-repo/repo-no-name/CMakeLists.txt;102;add_test;/mnt/c/git-repo/repo-no-name/CMakeLists.txt;0;")
subdirs("_deps/doctest-build")
subdirs("_deps/rapidcheck-build")
