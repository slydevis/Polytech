cmake_minimum_required(VERSION 3.9)
project(display_image)

find_package(OpenCV REQUIRED )
set( NAME_SRC
        image_profile_gray.cpp
        image_profile_color.cpp
        )

set( NAME_HEADERS

        )

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
link_directories( ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable( display_image ${NAME_SRC} ${NAME_HEADERS} )

target_link_libraries( display_image ${OpenCV_LIBS} )
