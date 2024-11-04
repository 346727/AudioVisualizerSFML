cmake_minimum_required(VERSION 3.14)
project(audio_visualizer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# If using Homebrew on macOS, set up paths
if(APPLE)
    # Check if we're on Apple Silicon
    execute_process(
        COMMAND uname -m
        OUTPUT_VARIABLE ARCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(${ARCH} STREQUAL "arm64")
        set(BREW_PREFIX "/opt/homebrew")
    else()
        set(BREW_PREFIX "/usr/local")
    endif()
    
    # Add Homebrew paths
    list(APPEND CMAKE_PREFIX_PATH "${BREW_PREFIX}")
    
    # Set SFML_DIR to help find SFML
    set(SFML_DIR "${BREW_PREFIX}/lib/cmake/SFML")
endif()

# Find SFML package
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

# Explicitly set FFTW3 paths
set(FFTW3_INCLUDE_DIR "${BREW_PREFIX}/include")
set(FFTW3_LIBRARY "${BREW_PREFIX}/lib/libfftw3.dylib")

# Add executable
add_executable(${PROJECT_NAME} main.cpp)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${FFTW3_INCLUDE_DIR}
)

# Link directories
link_directories(${BREW_PREFIX}/lib)

# Link libraries with full paths for FFTW3
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-audio
    sfml-window
    sfml-system
    ${FFTW3_LIBRARY}
)

# For macOS, set RPATH
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "${BREW_PREFIX}/lib"
    )
endif()

# Set additional compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

# Specify the source directory for the songs
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/songs")
set(TARGET_SONGS_DIR "${CMAKE_CURRENT_BINARY_DIR}/songs")

# Create a custom command to copy the songs directory to the build directory
file(GLOB SONG_FILES "${SOURCE_DIR}/*")  # Get all files in the songs directory
foreach(SONG_FILE ${SONG_FILES})
    get_filename_component(SONG_NAME ${SONG_FILE} NAME)  # Get just the filename
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${SONG_FILE} ${TARGET_SONGS_DIR}/${SONG_NAME}
    )
endforeach()
