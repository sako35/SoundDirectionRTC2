#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SoundDirection2" for configuration "Debug"
set_property(TARGET SoundDirection2 APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SoundDirection2 PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/components/lib/SoundDirection2.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "RTC112_vc12_x64d;coil112_vc12_x64d;omniORB421_rtd;omniDynamic421_rtd;omnithread40_rtd;advapi32;ws2_32;mswsock;opencv_videostab;opencv_video;opencv_ts;opencv_superres;opencv_stitching;opencv_photo;opencv_ocl;opencv_objdetect;opencv_nonfree;opencv_ml;opencv_legacy;opencv_imgproc;opencv_highgui;opencv_gpu;opencv_flann;opencv_features2d;opencv_core;opencv_contrib;opencv_calib3d;Kinect20"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/components/bin/SoundDirection2.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS SoundDirection2 )
list(APPEND _IMPORT_CHECK_FILES_FOR_SoundDirection2 "${_IMPORT_PREFIX}/components/lib/SoundDirection2.lib" "${_IMPORT_PREFIX}/components/bin/SoundDirection2.dll" )

# Import target "SoundDirection2Comp" for configuration "Debug"
set_property(TARGET SoundDirection2Comp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SoundDirection2Comp PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/components/bin/SoundDirection2Comp.exe"
  )

list(APPEND _IMPORT_CHECK_TARGETS SoundDirection2Comp )
list(APPEND _IMPORT_CHECK_FILES_FOR_SoundDirection2Comp "${_IMPORT_PREFIX}/components/bin/SoundDirection2Comp.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
