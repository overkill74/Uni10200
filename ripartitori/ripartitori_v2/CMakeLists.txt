cmake_minimum_required(VERSION 3.5)

set(TARGET      "ripartitori_v2")

project(${TARGET} VERSION 0.1 LANGUAGES CXX)

project(${TARGET} LANGUAGES CXX)

add_executable(${TARGET} main.cpp letture.cpp)

# Overkill Library
set(EXT_LIB_DIR      "$ENV{HOME}/local_$ENV{ARCHITECTURE}")

include_directories(
    "${EXT_LIB_DIR}/include"
    "${EXT_LIB_DIR}/include/overkill"
    )

find_package(Threads REQUIRED)
target_link_libraries(${TARGET}
    PRIVATE Threads::Threads
    ${EXT_LIB_DIR}/lib/liboverkilld.a
    ${EXT_LIB_DIR}/lib/libwolfssl.a
    ${EXT_LIB_DIR}/lib/libwolfmqtt.a
    ${EXT_LIB_DIR}/lib/libjansson.a
#    ${EXT_LIB_DIR}/lib/libsqlite3.a
#    libdl.so
    )
