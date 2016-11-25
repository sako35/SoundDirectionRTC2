#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Furimuki" for configuration "Debug"
set_property(TARGET Furimuki APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Furimuki PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/components/lib/Furimuki.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "RTC112_vc12_x64d;coil112_vc12_x64d;omniORB421_rtd;omniDynamic421_rtd;omnithread40_rtd;advapi32;ws2_32;mswsock"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/components/bin/Furimuki.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Furimuki )
list(APPEND _IMPORT_CHECK_FILES_FOR_Furimuki "${_IMPORT_PREFIX}/components/lib/Furimuki.lib" "${_IMPORT_PREFIX}/components/bin/Furimuki.dll" )

# Import target "FurimukiComp" for configuration "Debug"
set_property(TARGET FurimukiComp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(FurimukiComp PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/components/bin/FurimukiComp.exe"
  )

list(APPEND _IMPORT_CHECK_TARGETS FurimukiComp )
list(APPEND _IMPORT_CHECK_FILES_FOR_FurimukiComp "${_IMPORT_PREFIX}/components/bin/FurimukiComp.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
