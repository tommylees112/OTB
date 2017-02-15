INCLUDE_ONCE_MACRO(GEOTIFF)

SETUP_SUPERBUILD(GEOTIFF)

# declare dependencies
ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(GEOTIFF TIFF PROJ JPEG ZLIB)

set(GEOTIFF_SB_CONFIG)
ADD_SUPERBUILD_CMAKE_VAR(GEOTIFF TIFF_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(GEOTIFF TIFF_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(GEOTIFF PROJ_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(GEOTIFF PROJ_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(GEOTIFF ZLIB_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(GEOTIFF ZLIB_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(GEOTIFF JPEG_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(GEOTIFF JPEG_LIBRARY)

#RK: we are forced to use autoconf on osx due to cmake's find_* functions
#Do we need to use the same of Linux ?
if(UNIX)
  set(GEOTIFF_SB_CONFIG)
  ADD_SUPERBUILD_CONFIGURE_VAR(GEOTIFF PROJ_ROOT     --with-proj)
  ADD_SUPERBUILD_CONFIGURE_VAR(GEOTIFF TIFF_ROOT     --with-libtiff)
  ADD_SUPERBUILD_CONFIGURE_VAR(GEOTIFF JPEG_ROOT     --with-jpeg)
  ADD_SUPERBUILD_CONFIGURE_VAR(GEOTIFF ZLIB_ROOT     --with-libz)

  ExternalProject_Add(GEOTIFF
    PREFIX GEOTIFF
    URL "http://download.osgeo.org/geotiff/libgeotiff/libgeotiff-1.4.1.tar.gz"
    URL_MD5 48bdf817e6e7a37671cc1f41b01e10fc
    SOURCE_DIR ${GEOTIFF_SB_SRC}
    BINARY_DIR ${GEOTIFF_SB_SRC}
    INSTALL_DIR ${SB_INSTALL_PREFIX}
    DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
    DEPENDS ${GEOTIFF_DEPENDENCIES}
    CONFIGURE_COMMAND
    ${SB_ENV_CONFIGURE_CMD}
    ${GEOTIFF_SB_SRC}/configure
    ${SB_CONFIGURE_ARGS}
    ${GEOTIFF_SB_CONFIG}
    LOG_BUILD 1
    LOG_INSTALL 1
    )

  # [LOG_CONFIGURE 1]           # Wrap configure in script to log output
  # [LOG_BUILD 1]               # Wrap build in script to log output
  # [LOG_TEST 1]                # Wrap test in script to log output
  # [LOG_INSTALL 1]             # Wrap install in script to log output
  SUPERBUILD_PATCH_SOURCE(GEOTIFF)

else()

  ExternalProject_Add(GEOTIFF
    PREFIX GEOTIFF
    URL "http://download.osgeo.org/geotiff/libgeotiff/libgeotiff-1.4.1.tar.gz"
    URL_MD5 48bdf817e6e7a37671cc1f41b01e10fc
    SOURCE_DIR ${GEOTIFF_SB_SRC}
    BINARY_DIR ${GEOTIFF_SB_BUILD_DIR}
    INSTALL_DIR ${SB_INSTALL_PREFIX}
    DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
    DEPENDS ${GEOTIFF_DEPENDENCIES}
    CMAKE_CACHE_ARGS
    ${SB_CMAKE_CACHE_ARGS}
    -DBUILD_TESTING:BOOL=OFF
    -DPROJ4_OSGEO4W_HOME:PATH=${SB_INSTALL_PREFIX}
    ${GEOTIFF_SB_CONFIG}
    CMAKE_COMMAND ${SB_CMAKE_COMMAND}
    )

endif()

set(_SB_GEOTIFF_INCLUDE_DIR ${SB_INSTALL_PREFIX}/include)
if(WIN32)
  set(_SB_GEOTIFF_LIBRARY ${SB_INSTALL_PREFIX}/lib/geotiff_i.lib)
elseif(UNIX)
  set(_SB_GEOTIFF_LIBRARY ${SB_INSTALL_PREFIX}/lib/libgeotiff${CMAKE_SHARED_LIBRARY_SUFFIX})
endif()
