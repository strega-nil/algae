cmake_minimum_required(VERSION 3.5)

project(algae VERSION 0.1 LANGUAGES CXX)

add_executable(algae
  source/main.cpp)

target_include_directories(algae PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE source)

target_compile_features(algae PUBLIC cxx_std_17)

if(MSVC)
  target_compile_options(algae
    PUBLIC
      /D_SCL_SECURE_NO_WARNINGS
    PRIVATE
      /WX)
else()
  target_compile_options(algae
    PRIVATE
      -Wall -Wextra -Werror)
endif()