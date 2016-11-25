# Furimuki CMake config file
#
# This file sets the following variables:
# Furimuki_FOUND - Always TRUE.
# Furimuki_INCLUDE_DIRS - Directories containing the Furimuki include files.
# Furimuki_IDL_DIRS - Directories containing the Furimuki IDL files.
# Furimuki_LIBRARIES - Libraries needed to use Furimuki.
# Furimuki_DEFINITIONS - Compiler flags for Furimuki.
# Furimuki_VERSION - The version of Furimuki found.
# Furimuki_VERSION_MAJOR - The major version of Furimuki found.
# Furimuki_VERSION_MINOR - The minor version of Furimuki found.
# Furimuki_VERSION_REVISION - The revision version of Furimuki found.
# Furimuki_VERSION_CANDIDATE - The candidate version of Furimuki found.

message(STATUS "Found Furimuki-1.0.0")
set(Furimuki_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Furimuki_INCLUDE_DIRS
#    "C:/Program Files/Furimuki/include/furimuki-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Furimuki_IDL_DIRS
#    "C:/Program Files/Furimuki/include/furimuki-1/idl")
set(Furimuki_INCLUDE_DIRS
    "C:/Program Files/Furimuki/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Furimuki_IDL_DIRS
    "C:/Program Files/Furimuki/include//idl")


if(WIN32)
    set(Furimuki_LIBRARIES
        "C:/Program Files/Furimuki/components/lib/furimuki.lib"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Furimuki_LIBRARIES
        "C:/Program Files/Furimuki/components/lib/furimuki.dll"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Furimuki_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Furimuki_VERSION 1.0.0)
set(Furimuki_VERSION_MAJOR 1)
set(Furimuki_VERSION_MINOR 0)
set(Furimuki_VERSION_REVISION 0)
set(Furimuki_VERSION_CANDIDATE )

