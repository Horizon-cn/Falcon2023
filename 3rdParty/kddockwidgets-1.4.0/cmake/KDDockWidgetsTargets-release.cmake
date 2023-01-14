#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "KDAB::kddockwidgets" for configuration "Release"
set_property(TARGET KDAB::kddockwidgets APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(KDAB::kddockwidgets PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/kddockwidgets.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/kddockwidgets.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS KDAB::kddockwidgets )
list(APPEND _IMPORT_CHECK_FILES_FOR_KDAB::kddockwidgets "${_IMPORT_PREFIX}/lib/kddockwidgets.lib" "${_IMPORT_PREFIX}/bin/kddockwidgets.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
