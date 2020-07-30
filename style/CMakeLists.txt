
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

set(LIBRARY_NAME "feren-qt${QT_VERSION_NUMBER}")

add_library(${LIBRARY_NAME} MODULE ${Feren_SRCS})
target_link_libraries(${LIBRARY_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTDBUS_LIBRARY})
set_target_properties(${LIBRARY_NAME} PROPERTIES
    LINK_FLAGS "-Wl,--no-undefined"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    OUTPUT_NAME "feren"
    PREFIX "")

install(TARGETS ${LIBRARY_NAME} DESTINATION "${QT_PLUGINS_DIR}/styles")
