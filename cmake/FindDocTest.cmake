#********* Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
#**
#**
#**  Version : $Header:$
#**
#**
#**  Purpose : CMake FindModule script for the DocTest external project.
#**
#**
#**  See Also: https://cmake.org/cmake/help/latest/module/FetchContent.html#fetchcontent
#**            for more on the FetchContent command.
#**
#**            https://github.com/cambridgesemantics/doctest
#**            for more on the DocTest project.
#**                                                                     0-0
#**                                                                   (| v |)
#***********************************************************************w*w***

include(FetchContent)

#*****************************************************************************

FetchContent_Declare(DocTest
  GIT_REPOSITORY  https://github.com/cambridgesemantics/doctest.git
  GIT_TAG         0caf89db479b44f4c3e9f99ae01451410287e804 # v2.4.11.1
)

FetchContent_MakeAvailable(DocTest)

#*****************************************************************************
