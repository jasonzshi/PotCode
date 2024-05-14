# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(MODEL_FOLDER .)
set(EI_SDK_FOLDER edge-impulse-sdk)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/Users/jasonshi/pico/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)
#edge impulse 
include(${MODEL_FOLDER}/edge-impulse-sdk/cmake/utils.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(PotCode C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(PotCode 
PotCode.cpp
edge-impulse-sdk/porting/raspberry/ei_classifier_porting.cpp

 )

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

# add FREERTOS subdirectory
add_subdirectory(FreeRTOS)

#add SD subdirectory
add_subdirectory(no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI build)

# Add the standard library to the build
target_link_libraries(PotCode
        pico_stdlib pico_sync pico_time hardware_gpio hardware_pwm hardware_adc hardware_pio freertos FatFs_SPI)


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

# funky ml bits
target_include_directories(PotCode PRIVATE
    ${MODEL_FOLDER}
    ${MODEL_FOLDER}/classifer
    ${MODEL_FOLDER}/tflite-model
    ${MODEL_FOLDER}/model-parameters
)

target_include_directories(PotCode PRIVATE
    ${EI_SDK_FOLDER}
    ${EI_SDK_FOLDER}/third_party/ruy
    ${EI_SDK_FOLDER}/third_party/gemmlowp
    ${EI_SDK_FOLDER}/third_party/flatbuffers/include
    ${EI_SDK_FOLDER}/third_party
    ${EI_SDK_FOLDER}/tensorflow
    ${EI_SDK_FOLDER}/dsp
    ${EI_SDK_FOLDER}/classifier
    ${EI_SDK_FOLDER}/anomaly
    ${EI_SDK_FOLDER}/CMSIS/NN/Include
    ${EI_SDK_FOLDER}/CMSIS/DSP/PrivateInclude
    ${EI_SDK_FOLDER}/CMSIS/DSP/Include
    ${EI_SDK_FOLDER}/CMSIS/Core/Include
)

include_directories(${INCLUDES})

# find model source files
RECURSIVE_FIND_FILE(MODEL_FILES "${MODEL_FOLDER}/tflite-model" "*.cpp")
RECURSIVE_FIND_FILE(SOURCE_FILES "${EI_SDK_FOLDER}" "*.cpp")
RECURSIVE_FIND_FILE(CC_FILES "${EI_SDK_FOLDER}" "*.cc")
RECURSIVE_FIND_FILE(S_FILES "${EI_SDK_FOLDER}" "*.s")
RECURSIVE_FIND_FILE(C_FILES "${EI_SDK_FOLDER}" "*.c")
list(APPEND SOURCE_FILES ${S_FILES})
list(APPEND SOURCE_FILES ${C_FILES})
list(APPEND SOURCE_FILES ${CC_FILES})
list(APPEND SOURCE_FILES ${MODEL_FILES})

# add all sources to the project
target_sources(PotCode PRIVATE ${SOURCE_FILES})


#

# Add any user requested libraries
target_link_libraries(PotCode
        
        hardware_timer
        hardware_watchdog
        hardware_clocks
        hardware_pio
        hardware_rtc
        pico-scale
        
      
        
        )



        
pico_add_extra_outputs(PotCode)

