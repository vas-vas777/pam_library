cmake_minimum_required(VERSION 3.26)
project(sdk_for_token)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/Qt6/Qt6Config.cmake")
find_package(OpenSSL)
find_package(Boost)
#include(FetchContent)
#FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
#        GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
#FetchContent_MakeAvailable(cpr)
#FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
#        GIT_TAG 2553fc41450301cd09a9271c8d2c3e0cf3546b73) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
#FetchContent_MakeAvailable(cpr)
#find_package(cpr REQUIRED)

if (NOT MSVC)
    link_libraries(${OPENSSL_LIBRARIES})
else ()
endif ()
find_package(Qt6 COMPONENTS
        #Core
        #Gui
        #Widgets
        SerialPort
        #Network
        REQUIRED)

add_library(sdk_for_token SHARED
        source/gost_3410_2012.cpp
        source/gost_3411_2012_calc.c
        source/gost_3412_2015_calc.c
        source/SerialQt.cpp
        source/functions_for_pam.cpp
        #gost_3410_2012.h
        #mongoose.c
        )

target_link_libraries(sdk_for_token PRIVATE
        #Qt6::Core
        #Qt6::Gui
        #Qt6::Widgets
        Qt6::SerialPort
        #Qt6::Network
        #cpr::cpr
)