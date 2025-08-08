cmake_minimum_required(VERSION 3.10)
project(iotSF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

include_directories(
    include
    ${LIBUSB_INCLUDE_DIRS}
)
link_directories(${LIBUSB_LIBRARY_DIRS})

add_executable(iotSF
    src/main.cpp
    src/wifi/usb/usb_detector.cpp
)

target_link_libraries(iotSF
    ${LIBUSB_LIBRARIES}
)
target_compile_options(iotSF PRIVATE ${LIBUSB_CFLAGS_OTHER})
