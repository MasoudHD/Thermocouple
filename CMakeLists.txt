cmake_minimum_required(VERSION 3.5)
project(Thermocouple VERSION 0.1.0 LANGUAGES C)


set(SRC_FILES
        ./main.c
        src/thermocouple.c
        src/Tables/K_Type.c
)

set (INC_FILES
    inc
)

add_executable(Thermocouple ${SRC_FILES})

target_include_directories(Thermocouple PUBLIC ${INC_FILES})
