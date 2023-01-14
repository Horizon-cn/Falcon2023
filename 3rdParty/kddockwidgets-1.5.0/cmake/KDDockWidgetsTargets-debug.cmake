#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "KDAB::kddockwidgets" for configuration "Debug"
set_property(TARGET KDAB::kddockwidgets APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(KDAB::kddockwidgets PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/kddockwidgetsd.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/kddockwidgetsd.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS KDAB::kddockwidgets )
list(APPEND _IMPORT_CHECK_FILES_FOR_KDAB::kddockwidgets "${_IMPORT_PREFIX}/lib/kddockwidgetsd.lib" "${_IMPORT_PREFIX}/bin/kddockwidgetsd.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
