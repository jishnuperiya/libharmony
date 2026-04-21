#********* Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
#**
#**
#**  Version : $Header:$
#**
#**
#**  Purpose : CMake FindModule script for the RapidCheck external project.
#**
#**
#**  See Also: https://cmake.org/cmake/help/latest/module/FetchContent.html#fetchcontent
#**            for more on the FetchContent command.
#**
#**            https://github.com/cambridgesemantics/rapidcheck
#**            for more on the RapidCheck project.
#**                                                                     0-0
#**                                                                   (| v |)
#***********************************************************************w*w***

include(FetchContent)

#*****************************************************************************

FetchContent_Declare(RapidCheck
  GIT_REPOSITORY  https://github.com/cambridgesemantics/rapidcheck.git
  GIT_TAG         25383bd789d29ef3179f38f4528cb987b61c3f33 # v1.1.0
)

FetchContent_MakeAvailable(RapidCheck)

#*****************************************************************************
