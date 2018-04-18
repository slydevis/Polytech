cmake_minimum_required(VERSION 3.8)
project(TP1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES png.cpp)

find_package(OpenSSL)
if(OpenSSL_FOUND)
    message("OPENSSL FOUND")
    include_directories(${OPENSSL_ROOT_DIR})
    message("${OPENSSL_ROOT_DIR}")

    find_package(PNG)
    if(PNG_FOUND)
        message("PNG FOUND")
        include_directories(${PNG_ROOT_DIR})
        message("${PNG_ROOT_DIR}")
    endif()

    add_executable(TP1 ${SOURCE_FILES})

    target_link_libraries(TP1 ${OPENSSL_LIBRARIES})
    message("${OPENSSL_LIBRARIES}")
endif()

if(PNG_FOUND)

    target_link_libraries(TP1 ${PNG_LIBRARIES})
    message("${PNG_LIBRARIES}")
endif()