# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/Users/jasonshi/pico/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(PotCode C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(PotCode PotCode.cpp )

pico_set_program_name(PotCode "PotCode")
pico_set_program_version(PotCode "0.1")

pico_enable_stdio_uart(PotCode 1)
pico_enable_stdio_usb(PotCode 1)


# add git libs
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  option(GIT_SUBMODULE "Check submodules during build" ON)
  if(GIT_SUBMODULE)
    message(STATUS "Submodule Update")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
      message(FATAL_ERROR "git submodule update --init failed ")
    endif()
  endif() 
endif()
# check submodules
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/pico-scale/CMakeLists.txt")
  message(FATAL_ERROR "missing submodules nani??")
endif()
# add scale subdirectory
add_subdirectory(extern/pico-scale)

# Add the standard library to the build
target_link_libraries(PotCode
        pico_stdlib pico_sync pico_time hardware_gpio hardware_pwm hardware_adc hardware_pio)


# Add the standard include files to the build
target_include_directories(PotCode PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
 
)

target_include_directories(PotCode  
PUBLIC extern/pico-scale
PUBLIC extern/pico-scale/src
PUBLIC extern/pico-scale/include
PUBLIC extern/pico-scale/extern/hx711-pico-c/include 
)

#find pot libs
#find_library(POTCODE_LIBRARY scale HINTS extern/pico-scale/include)

# Add any user requested libraries
target_link_libraries(PotCode
        
        hardware_timer
        hardware_watchdog
        hardware_clocks
        hardware_pio
        pico-scale
        
      
        
        )



        
pico_add_extra_outputs(PotCode)

