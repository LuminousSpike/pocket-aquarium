cmake_minimum_required(VERSION 3.20)
project(pocket_aquarium C)

# Set the GBDK home directory
if(NOT DEFINED ENV{GBDK_HOME})
  set(GBDK_HOME "./gbdk")
else()
  set(GBDK_HOME $ENV{GBDK_HOME})
endif()

get_filename_component(GBDK_HOME "${GBDK_HOME}" ABSOLUTE)

# Find the LCC compiler
find_program(LCC "${GBDK_HOME}/bin/lcc" REQUIRED)

# Set compiler and linker flags
set(CMAKE_C_COMPILER ${LCC})
set(CMAKE_C_FLAGS "-Wm-yC -I\"${GBDK_HOME}/include\" -msm83 -D__PORT_sm83 -D__TARGET_GB -D__SDCC")

# Add debug flags if GBDK_DEBUG is set
option(GBDK_DEBUG "Enable GBDK debug mode" OFF)
if(GBDK_DEBUG)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -debug -v")
endif()

# Set directories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(RES_DIR "${CMAKE_SOURCE_DIR}/res")
set(OBJ_DIR "${CMAKE_BINARY_DIR}/obj")

# Find all source files
file(GLOB_RECURSE SOURCES
    "${SRC_DIR}/*.c"
    "${SRC_DIR}/*.s"
    "${RES_DIR}/*.c"
)

# Set output file name
set(OUTPUT_NAME "${PROJECT_NAME}.gbc")

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Set the output directory for the final .gbc file
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${OBJ_DIR}"
    OUTPUT_NAME "${OUTPUT_NAME}"
)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Custom command to copy compile_commands.json to the project root
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_SOURCE_DIR}/compile_commands.json
)
