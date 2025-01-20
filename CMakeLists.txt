cmake_minimum_required(VERSION 3.14)
project(audio_visualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if(APPLE)
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
    
    list(APPEND CMAKE_PREFIX_PATH "${BREW_PREFIX}")
    
    set(SFML_DIR "${BREW_PREFIX}/lib/cmake/SFML")
endif()

find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)


set(FFTW3_INCLUDE_DIR "${BREW_PREFIX}/include")
set(FFTW3_LIBRARY "${BREW_PREFIX}/lib/libfftw3.dylib")

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/Source_Code")
set(HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/Headers")

file(GLOB SOURCES "${SRC_DIR}/*.cpp")

add_executable(audio_visualizer
    main.cpp
    src/source_code/AudioVisualizer.cpp
    src/source_code/SongPanel.cpp
    src/source_code/SettingsPanel.cpp
    src/source_code/tinyfiledialogs.c
)

include_directories(${CMAKE_SOURCE_DIR}/src/Headers)


target_include_directories(${PROJECT_NAME} PRIVATE
    ${FFTW3_INCLUDE_DIR}
    ${HEADER_DIR}  
)

link_directories(${BREW_PREFIX}/lib)

# FFTW3 includes
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-audio
    sfml-window
    sfml-system
    ${FFTW3_LIBRARY}
)

# macOS, RPATH
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "${BREW_PREFIX}/lib"
    )
endif()


if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

# Lokalizacja plików mp3
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/songs")
set(TARGET_SONGS_DIR "${CMAKE_CURRENT_BINARY_DIR}/songs")

# Komenda kopiujaca pliki mp3 do lokalizacji builda
file(GLOB SONG_FILES "${SOURCE_DIR}/*")  
foreach(SONG_FILE ${SONG_FILES})
    get_filename_component(SONG_NAME ${SONG_FILE} NAME) 
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${SONG_FILE} ${TARGET_SONGS_DIR}/${SONG_NAME}
    )
endforeach()

# Add a variable for the font source path
set(FONT_SOURCE ${CMAKE_SOURCE_DIR}/src/Fonts/Arial.ttf)

# Add a post-build command to copy the font to the runtime directory
add_custom_command(
    TARGET audio_visualizer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${FONT_SOURCE}
        $<TARGET_FILE_DIR:audio_visualizer>/Arial.ttf
)

