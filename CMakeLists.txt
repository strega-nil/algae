cmake_minimum_required(VERSION 3.6)

project(algae VERSION 0.1 LANGUAGES CXX)

### LIBRARY ###

add_library(algae INTERFACE)

target_include_directories(algae
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_compile_features(algae INTERFACE cxx_std_17)
if(MSVC)
  target_compile_options(algae
    INTERFACE
      /permissive-
      /Zc:externConstexpr
      /Zc:inline
      /Zc:rvalueCast
      /Zc:strictStrings
      /Zc:throwingNew
      /D_SCL_SECURE_NO_WARNINGS)
endif()

### EXECUTABLE (for homework) ###

add_executable(algae_calc
  source/main.cpp)

target_link_libraries(algae_calc algae)
target_compile_features(algae_calc PUBLIC cxx_std_17)
target_include_directories(algae_calc
  PRIVATE
    source)


### TESTING ###

add_executable(algae_test
  test/main.cpp
  test/vector.cpp)
target_link_libraries(algae_test algae)
target_include_directories(algae_test
  PRIVATE
    test)

### FLAGS ###

if(MSVC)
  # hack to deal with cmake automatically inserting /W3; stolen from llvm
  string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

function(add_flags to)
  if(MSVC)
    target_compile_options(${to}
      PRIVATE
        /W4
        /WX)
  else()
    target_compile_options(${to}
      PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror)
  endif()
endfunction()

add_flags(algae_calc)
add_flags(algae_test)
