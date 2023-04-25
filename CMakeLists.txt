cmake_minimum_required(VERSION 3.22)
project(DataTypes C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(DataTypes
        Types/dynamic_list.c
        Types/dynamic_list.h
        Types/hash_map.c
        Types/hash_map.h
        Types/linked_list.c
        Types/linked_list.h
        Types/string.c
        Types/string.h
        Types/value.c
        Types/value.h
        Types/queue.c
        Types/queue.h
        Types/vector.c
        Types/vector.h
        common.c
        common.h
        main.c Context/scope.c Context/scope.h)
