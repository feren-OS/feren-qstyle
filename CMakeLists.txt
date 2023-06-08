project(Inspire)

cmake_minimum_required(VERSION 3.0)

set(KF5_MIN_VERSION "5.66.0")

include(GenerateExportHeader)
include(WriteBasicConfigVersionFile)
include(FeatureSummary)

set(CMAKE_AUTOMOC ON)
add_definitions(-std=c++11)

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_SOURCE_DIR}/cmake)

include(ECMInstallIcons)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDEClangFormat)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5DBus REQUIRED)
set(QT_QTGUI_LIBRARY Qt5::Gui Qt5::Widgets)
set(QT_QTCORE_LIBRARY Qt5::Core)
set(QT_QTDBUS_LIBRARY Qt5::DBus)
#target_link_libraries(${LIBRARY_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
set(QT_VERSION_NUMBER "5")
get_target_property(REAL_QMAKE_EXECUTABLE ${Qt5Core_QMAKE_EXECUTABLE}
                    IMPORTED_LOCATION)
if (NOT QT_PLUGINS_DIR)
    execute_process(COMMAND "${REAL_QMAKE_EXECUTABLE}" -query QT_INSTALL_PLUGINS
                    OUTPUT_VARIABLE QT_PLUGINS_DIR
                    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()

find_package(KF5Package ${KF5_MIN_VERSION} CONFIG REQUIRED)

if (NOT CMAKE_INSTALL_PREFIX)
    set (CMAKE_INSTALL_PREFIX "/usr/local")
endif()

if (NOT DATA_INSTALL_DIR)
    set (DATA_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/share")
endif()
if (NOT THEME_INSTALL_DIR)
    set (THEME_INSTALL_DIR "${DATA_INSTALL_DIR}/themes")
endif()

set(INSPIRE_THEME_DIR "${THEME_INSTALL_DIR}/Inspire/qt")

add_subdirectory(style)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
