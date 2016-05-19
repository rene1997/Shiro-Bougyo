# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


SET(CPACK_BINARY_7Z "OFF")
SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_IFW "OFF")
SET(CPACK_BINARY_NSIS "ON")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_RPM "")
SET(CPACK_BINARY_STGZ "")
SET(CPACK_BINARY_TBZ2 "")
SET(CPACK_BINARY_TGZ "")
SET(CPACK_BINARY_TXZ "")
SET(CPACK_BINARY_TZ "")
SET(CPACK_BINARY_WIX "OFF")
SET(CPACK_BINARY_ZIP "OFF")
SET(CPACK_CMAKE_GENERATOR "Visual Studio 14 2015 Win64")
SET(CPACK_COMPONENTS_ALL "development;docs;examples;runtime")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_GENERATOR "NSIS")
SET(CPACK_INSTALL_CMAKE_PROJECTS "C:/Users/Wesley/Documents/GitHub/Shiro-Bougyo/Project/wiiuse/build;WiiUse;ALL;/")
SET(CPACK_INSTALL_PREFIX "C:/Program Files/WiiUse")
SET(CPACK_MODULE_PATH "C:/Users/Wesley/Documents/GitHub/wiiuse/cmake;C:/Users/Wesley/Documents/GitHub/wiiuse/cmake/cmake-4.0.0-modules;C:/Users/Wesley/Documents/GitHub/wiiuse/cmake/cmake-4.0.0-modules/from-ITK-3.18.0")
SET(CPACK_MONOLITHIC_INSTALL "OFF")
SET(CPACK_NSIS_DISPLAY_NAME "WiiUse 0.15.0")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
SET(CPACK_NSIS_PACKAGE_NAME "WiiUse 0.15.0")
SET(CPACK_OUTPUT_CONFIG_FILE "C:/Users/Wesley/Documents/GitHub/Shiro-Bougyo/Project/wiiuse/build/CPackConfig.cmake")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "C:/Program Files (x86)/CMake/share/cmake-3.5/Templates/CPack.GenericDescription.txt")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "WiiUse built using CMake")
SET(CPACK_PACKAGE_FILE_NAME "WiiUse-0.15.0-vs14win64")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "WiiUse 0.15.0")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "WiiUse 0.15.0")
SET(CPACK_PACKAGE_NAME "WiiUse")
SET(CPACK_PACKAGE_RELOCATABLE "true")
SET(CPACK_PACKAGE_VENDOR "Humanity")
SET(CPACK_PACKAGE_VERSION "0.15.0")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MICRO "0")
SET(CPACK_PACKAGE_VERSION_MINOR "15")
SET(CPACK_PACKAGE_VERSION_PATCH "1")
SET(CPACK_RESOURCE_FILE_LICENSE "C:/Users/Wesley/Documents/GitHub/wiiuse/LICENSE")
SET(CPACK_RESOURCE_FILE_README "C:/Users/Wesley/Documents/GitHub/wiiuse/README.mkd")
SET(CPACK_RESOURCE_FILE_WELCOME "C:/Program Files (x86)/CMake/share/cmake-3.5/Templates/CPack.GenericWelcome.txt")
SET(CPACK_SET_DESTDIR "OFF")
SET(CPACK_SOURCE_7Z "ON")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "7Z;ZIP")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "C:/Users/Wesley/Documents/GitHub/Shiro-Bougyo/Project/wiiuse/build/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_TBZ2 "")
SET(CPACK_SOURCE_TGZ "")
SET(CPACK_SOURCE_TXZ "")
SET(CPACK_SOURCE_TZ "")
SET(CPACK_SOURCE_ZIP "ON")
SET(CPACK_SYSTEM_NAME "win64")
SET(CPACK_TOPLEVEL_TAG "win64")
SET(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "C:/Users/Wesley/Documents/GitHub/Shiro-Bougyo/Project/wiiuse/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()

# Configuration for component "docs"

SET(CPACK_COMPONENTS_ALL development docs examples runtime)
set(CPACK_COMPONENT_DOCS_HIDDEN TRUE)

# Configuration for component "development"

SET(CPACK_COMPONENTS_ALL development docs examples runtime)
set(CPACK_COMPONENT_DEVELOPMENT_DISPLAY_NAME "Development Files")

# Configuration for component "examples"

SET(CPACK_COMPONENTS_ALL development docs examples runtime)
set(CPACK_COMPONENT_EXAMPLES_DISPLAY_NAME "Examples")

# Configuration for component "runtime"

SET(CPACK_COMPONENTS_ALL development docs examples runtime)
set(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "Runtime Library")
set(CPACK_COMPONENT_RUNTIME_REQUIRED TRUE)