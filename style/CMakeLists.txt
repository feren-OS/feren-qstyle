################# Qt/KDE #################
find_package(Qt5 REQUIRED CONFIG COMPONENTS Widgets DBus)
find_package(KF5 REQUIRED COMPONENTS
    I18n
    Config
    GuiAddons
    IconThemes
    ConfigWidgets
    WindowSystem)

find_package(Qt5 COMPONENTS Quick)
set(FEREN_HAVE_QTQUICK ${Qt5Quick_FOUND})

find_package( KF5FrameworkIntegration CONFIG )
set_package_properties(KF5FrameworkIntegration PROPERTIES
    DESCRIPTION "KF5 Framework Integration"
    URL "https://projects.kde.org/projects/frameworks/frameworkintegration"
    TYPE OPTIONAL
    PURPOSE "Required to use KStyle convenience functionalities in style")

set(FEREN_HAVE_KSTYLE ${KF5FrameworkIntegration_FOUND})

find_package(XCB COMPONENTS XCB)
set_package_properties(XCB PROPERTIES
    DESCRIPTION "X protocol C-language Binding"
    URL "https://xcb.freedesktop.org"
    TYPE OPTIONAL
    PURPOSE "Required to pass style properties to native Windows on X11 Platform"
)

find_package(KF5Wayland CONFIG)
set(FEREN_HAVE_KWAYLAND ${KF5Wayland_FOUND})

if(UNIX AND NOT APPLE)
    set(FEREN_HAVE_X11 ${XCB_XCB_FOUND})
    if (XCB_XCB_FOUND)
        find_package(Qt5 REQUIRED CONFIG COMPONENTS X11Extras)
    endif()
else()
    set(FEREN_HAVE_X11 FALSE)
endif()

configure_file(config-feren.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-feren.h )

set(Feren_SRCS
    animations/ferenanimation.cpp
    animations/ferenanimations.cpp
    animations/ferenanimationdata.cpp
    animations/ferenbaseengine.cpp
    animations/ferenbusyindicatordata.cpp
    animations/ferenbusyindicatorengine.cpp
    animations/ferendialdata.cpp
    animations/ferendialengine.cpp
    animations/ferenenabledata.cpp
    animations/ferengenericdata.cpp
    animations/ferenheaderviewdata.cpp
    animations/ferenheaderviewengine.cpp
    animations/ferenscrollbardata.cpp
    animations/ferenscrollbarengine.cpp
    animations/ferenspinboxengine.cpp
    animations/ferenspinboxdata.cpp
    animations/ferenstackedwidgetdata.cpp
    animations/ferenstackedwidgetengine.cpp
    animations/ferentabbarengine.cpp
    animations/ferentabbardata.cpp
    animations/ferentoolboxengine.cpp
    animations/ferentransitiondata.cpp
    animations/ferentransitionwidget.cpp
    animations/ferenwidgetstateengine.cpp
    animations/ferenwidgetstatedata.cpp
    debug/ferenwidgetexplorer.cpp
    ferenaddeventfilter.cpp
    ferenblurhelper.cpp
    ferenhelper.cpp
    ferenmnemonics.cpp
    ferensplitterproxy.cpp
    ferenstyle.cpp
    ferenstyleplugin.cpp
    ferenwindowmanager.cpp
)
add_definitions(-DQT_PLUGIN)

if (MSVC)
    add_definitions(-D_USE_MATH_DEFINES) # Needed for M_PI on MSVC
endif()

include_directories(
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR} # for feren-config.h
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/animations/
    ${CMAKE_CURRENT_SOURCE_DIR}/debug/
)

set(LIBRARY_NAME "feren-qstyle")

add_library(${LIBRARY_NAME} MODULE ${Feren_SRCS})
target_link_libraries(${LIBRARY_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTDBUS_LIBRARY})
if( FEREN_HAVE_QTQUICK )
    target_link_libraries(${LIBRARY_NAME} Qt5::Quick)
endif()
if(KF5FrameworkIntegration_FOUND)
    target_link_libraries(${LIBRARY_NAME} KF5::Style)
endif()
target_link_libraries(${LIBRARY_NAME} KF5::ConfigCore KF5::ConfigWidgets KF5::GuiAddons KF5::IconThemes KF5::WindowSystem KF5::Style)
set_target_properties(${LIBRARY_NAME} PROPERTIES
    LINK_FLAGS "-Wl,--no-undefined"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    OUTPUT_NAME "feren"
    PREFIX "")

install(TARGETS ${LIBRARY_NAME} DESTINATION "${QT_PLUGINS_DIR}/styles")
install(FILES feren.themerc  DESTINATION  ${DATA_INSTALL_DIR}/kstyle/themes)
