#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "sentry::sentry" for configuration "RelWithDebInfo"
set_property(TARGET sentry::sentry APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(sentry::sentry PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/sentry.lib"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/bin/sentry.dll"
  )

list(APPEND _cmake_import_check_targets sentry::sentry )
list(APPEND _cmake_import_check_files_for_sentry::sentry "${_IMPORT_PREFIX}/lib/sentry.lib" "${_IMPORT_PREFIX}/bin/sentry.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
