cmake_minimum_required(VERSION 3.22)
project(tutorial)

SET(Boost_USE_STATIC_LIBS ON)
# ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

find_package(Boost 1.79.0 COMPONENTS log REQUIRED)
# IF(Boost_FOUND)
#     message("boost found")
# ENDIF()

add_executable(mytarget main.cpp cipheredLogger.cpp cryptography.cpp logger.cpp)
target_link_libraries(mytarget Boost::log)
# target_link_libraries(mytarget Boost::log_setup Boost::log)
