# requires minimum cmake version
cmake_minimum_required(VERSION 2.8.9)

# produce the cmake var PROJECT_NAME
project(tutorial_yarp-port)

# mandatory use of these packages
find_package(YARP REQUIRED)

find_package(ICUBcontrib REQUIRED)

# extend the current search path used by cmake to load helpers
list(APPEND CMAKE_MODULE_PATH ${ICUBCONTRIB_MODULE_PATH})

include(ICUBcontribHelpers)
# specify to install in $ICUBcontrib_DIR/bin
icubcontrib_set_default_prefix()

include_directories(${YARP_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} ${YARP_LIBRARIES})

install(TARGETS tutorial_yarp-port DESTINATION bin)

icubcontrib_add_uninstall_target()
