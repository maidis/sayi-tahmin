PROJECT(sayi-tahmin)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


Find_Package(Gettext REQUIRED)
Find_Package(Curses REQUIRED)

INCLUDE_DIRECTORIES(${GETTEXT_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${CURSES_INCLUDE_DIR})

if ( NOT GETTEXT_FOUND )
    message(FATAL_ERROR "GETTEXT not found !")
endif ( NOT GETTEXT_FOUND )

if ( NOT CURSES_FOUND )
    message(FATAL_ERROR "CURSES not found !")
endif ( NOT CURSES_FOUND )


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(SRC_DIR ${PROJECT_SOURCE_DIR})

include_directories(
        ${PROJECT_BINARY_DIR}
        ${GETTEXT_INCLUDE_DIR}
        ${CURSES_INCLUDE_DIR}
)

SET(CMAKE_CXX_FLAGS "-Wall -g")

# Déclaration de l'exécutable
file(GLOB Sources ${SRC_DIR}/*.cpp)
add_executable(sayi-tahmin ${Sources})

target_link_libraries(
    sayi-tahmin
    ${GETTEXT_LIBRARY}
    ${CURSES_LIBRARY}
)

install(TARGETS sayi-tahmin RUNTIME DESTINATION bin)
if("${CMAKE_SYSTEM_NAME}" MATCHES "Linux") 
        install(FILES sayi-tahmin.desktop DESTINATION share/applications/)
        install(FILES sayi-tahmin.png DESTINATION share/pixmaps/)
        install(FILES COPYING README TODO DESTINATION share/doc/sayi-tahmin/)
endif("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")

# http://stackoverflow.com/questions/2694742/is-there-a-cmake-function-to-update-pot-files
# http://stackoverflow.com/questions/2876110/cmake-module-for-gettext-support
GETTEXT_CREATE_TRANSLATIONS(sayi-tahmin.pot ALL tr.po)
