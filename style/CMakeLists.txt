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
set(INSPIRE_HAVE_QTQUICK ${Qt5Quick_FOUND})

find_package( KF5FrameworkIntegration CONFIG )
set_package_properties(KF5FrameworkIntegration PROPERTIES
    DESCRIPTION "KF5 Framework Integration"
    URL "https://projects.kde.org/projects/frameworks/frameworkintegration"
    TYPE OPTIONAL
    PURPOSE "Required to use KStyle convenience functionalities in style")

set(INSPIRE_HAVE_KSTYLE ${KF5FrameworkIntegration_FOUND})

find_package(XCB COMPONENTS XCB)
set_package_properties(XCB PROPERTIES
    DESCRIPTION "X protocol C-language Binding"
    URL "https://xcb.freedesktop.org"
    TYPE OPTIONAL
    PURPOSE "Required to pass style properties to native Windows on X11 Platform"
)

find_package(KF5Wayland CONFIG)
set(INSPIRE_HAVE_KWAYLAND ${KF5Wayland_FOUND})

if(UNIX AND NOT APPLE)
    set(INSPIRE_HAVE_X11 ${XCB_XCB_FOUND})
    if (XCB_XCB_FOUND)
        find_package(Qt5 REQUIRED CONFIG COMPONENTS X11Extras)
    endif()
else()
    set(INSPIRE_HAVE_X11 FALSE)
endif()

configure_file(config-inspire.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-inspire.h )

set(Inspire_SRCS
    animations/inspireanimation.cpp
    animations/inspireanimations.cpp
    animations/inspireanimationdata.cpp
    animations/inspirebaseengine.cpp
    animations/inspirebusyindicatordata.cpp
    animations/inspirebusyindicatorengine.cpp
    animations/inspiredialdata.cpp
    animations/inspiredialengine.cpp
    animations/inspireenabledata.cpp
    animations/inspiregenericdata.cpp
    animations/inspireheaderviewdata.cpp
    animations/inspireheaderviewengine.cpp
    animations/inspirescrollbardata.cpp
    animations/inspirescrollbarengine.cpp
    animations/inspirespinboxengine.cpp
    animations/inspirespinboxdata.cpp
    animations/inspirestackedwidgetdata.cpp
    animations/inspirestackedwidgetengine.cpp
    animations/inspiretabbarengine.cpp
    animations/inspiretabbardata.cpp
    animations/inspiretoolboxengine.cpp
    animations/inspiretransitiondata.cpp
    animations/inspiretransitionwidget.cpp
    animations/inspirewidgetstateengine.cpp
    animations/inspirewidgetstatedata.cpp
    inspireaddeventfilter.cpp
    inspireblurhelper.cpp
    inspirehelper.cpp
    inspiremnemonics.cpp
    inspiresplitterproxy.cpp
    inspirestyle.cpp
    inspirestyleplugin.cpp
    inspirewindowmanager.cpp
)
add_definitions(-DQT_PLUGIN)

if (MSVC)
    add_definitions(-D_USE_MATH_DEFINES) # Needed for M_PI on MSVC
endif()

include_directories(
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR} # for inspire-config.h
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/animations/
)

set(LIBRARY_NAME "inspire-qt${QT_VERSION_NUMBER}")

add_library(${LIBRARY_NAME} MODULE ${Inspire_SRCS})
target_link_libraries(${LIBRARY_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTDBUS_LIBRARY})

if( INSPIRE_HAVE_QTQUICK )
    target_link_libraries(${LIBRARY_NAME} Qt5::Quick)
endif()

if(KF5FrameworkIntegration_FOUND)
    target_link_libraries(${LIBRARY_NAME} KF5::Style)
endif()

if(INSPIRE_HAVE_X11)
    target_link_libraries(${LIBRARY_NAME} ${XCB_LIBRARIES})
    target_link_libraries(${LIBRARY_NAME} Qt5::X11Extras)
endif()

if(INSPIRE_HAVE_KWAYLAND)
    target_link_libraries(${LIBRARY_NAME} KF5::WaylandClient)
endif()

target_link_libraries(${LIBRARY_NAME} KF5::ConfigCore KF5::ConfigWidgets KF5::GuiAddons KF5::IconThemes KF5::WindowSystem KF5::Style)
set_target_properties(${LIBRARY_NAME} PROPERTIES
    LINK_FLAGS "-Wl,--no-undefined"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    OUTPUT_NAME "inspire"
    PREFIX "")

install(TARGETS ${LIBRARY_NAME} DESTINATION "${QT_PLUGINS_DIR}/styles")
install(FILES inspire.themerc  DESTINATION  ${DATA_INSTALL_DIR}/kstyle/themes)
