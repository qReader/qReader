cmake_minimum_required(VERSION 3.0)
project(dao)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++17")
SET(ENABLE_MYSQL ON)
if (ENABLE_MYSQL)
add_definitions(-DORMPP_ENABLE_MYSQL)
set(SOURCE_FILES userInfo.cpp userInfo.h dbng.hpp unit_test.hpp pg_types.h
        type_mapping.hpp utility.hpp entity.hpp mysql.hpp
        connection_pool.hpp ormpp_cfg.hpp)
endif()
INCLUDE_DIRECTORIES(
                    ${CMAKE_SOURCE_DIR}/iguana
                   )
	   
#add_executable(ormpp ${SOURCE_FILES})


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
aux_source_directory(. DIR_USERINFO_SRCS)
add_library(dao ${DIR_USERINFO_SRCS})
if (ENABLE_MYSQL)
	target_link_libraries(dao mysqlclient)
endif()
