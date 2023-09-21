#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "tmxparser" for configuration ""
set_property(TARGET tmxparser APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(tmxparser PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libtmxparser.so.2.1.0"
  IMPORTED_SONAME_NOCONFIG "libtmxparser.so.2"
  )

list(APPEND _cmake_import_check_targets tmxparser )
list(APPEND _cmake_import_check_files_for_tmxparser "${_IMPORT_PREFIX}/lib/libtmxparser.so.2.1.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
