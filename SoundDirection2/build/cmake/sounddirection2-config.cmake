# SoundDirection2 CMake config file
#
# This file sets the following variables:
# SoundDirection2_FOUND - Always TRUE.
# SoundDirection2_INCLUDE_DIRS - Directories containing the SoundDirection2 include files.
# SoundDirection2_IDL_DIRS - Directories containing the SoundDirection2 IDL files.
# SoundDirection2_LIBRARIES - Libraries needed to use SoundDirection2.
# SoundDirection2_DEFINITIONS - Compiler flags for SoundDirection2.
# SoundDirection2_VERSION - The version of SoundDirection2 found.
# SoundDirection2_VERSION_MAJOR - The major version of SoundDirection2 found.
# SoundDirection2_VERSION_MINOR - The minor version of SoundDirection2 found.
# SoundDirection2_VERSION_REVISION - The revision version of SoundDirection2 found.
# SoundDirection2_VERSION_CANDIDATE - The candidate version of SoundDirection2 found.

message(STATUS "Found SoundDirection2-1.0.0")
set(SoundDirection2_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(SoundDirection2_INCLUDE_DIRS
#    "C:/Program Files/SoundDirection2/include/sounddirection2-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(SoundDirection2_IDL_DIRS
#    "C:/Program Files/SoundDirection2/include/sounddirection2-1/idl")
set(SoundDirection2_INCLUDE_DIRS
    "C:/Program Files/SoundDirection2/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(SoundDirection2_IDL_DIRS
    "C:/Program Files/SoundDirection2/include//idl")


if(WIN32)
    set(SoundDirection2_LIBRARIES
        "C:/Program Files/SoundDirection2/components/lib/sounddirection2.lib"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(SoundDirection2_LIBRARIES
        "C:/Program Files/SoundDirection2/components/lib/sounddirection2.dll"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(SoundDirection2_DEFINITIONS ${<dependency>_DEFINITIONS})

set(SoundDirection2_VERSION 1.0.0)
set(SoundDirection2_VERSION_MAJOR 1)
set(SoundDirection2_VERSION_MINOR 0)
set(SoundDirection2_VERSION_REVISION 0)
set(SoundDirection2_VERSION_CANDIDATE )

