
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was sentry-config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################
include(CMakeFindDependencyMacro)

set(SENTRY_BACKEND crashpad)
set(SENTRY_TRANSPORT winhttp)
set(SENTRY_BUILD_SHARED_LIBS ON)
set(SENTRY_LINK_PTHREAD ON)
set(SENTRY_TRANSPORT_COMPRESSION OFF)
set(SENTRY_BREAKPAD_SYSTEM )
set(CRASHPAD_ZLIB_SYSTEM OFF)

if(NOT SENTRY_BUILD_SHARED_LIBS)
    if(SENTRY_TRANSPORT_COMPRESSION OR CRASHPAD_ZLIB_SYSTEM)
    	find_dependency(ZLIB)
    endif()
    if(SENTRY_BACKEND STREQUAL "breakpad" AND SENTRY_BREAKPAD_SYSTEM)
    	find_dependency(PkgConfig)
    	pkg_check_modules(BREAKPAD REQUIRED IMPORTED_TARGET breakpad-client)
    endif()
    if(SENTRY_TRANSPORT STREQUAL "curl")
    	find_dependency(CURL COMPONENTS AsynchDNS)
    endif()
    if(SENTRY_LINK_PTHREAD)
        set(THREADS_PREFER_PTHREAD_FLAG ON)
    	find_dependency(Threads)
    endif()
endif()

include("${CMAKE_CURRENT_LIST_DIR}/sentry_crashpad-targets.cmake" OPTIONAL)
include("${CMAKE_CURRENT_LIST_DIR}/sentry-targets.cmake")
