cmake_minimum_required(VERSION 3.10)

# Set the project name
project(cpp)

# Ignore the warning
add_compile_options(-w)

# Add the executable
add_executable(${PROJECT_NAME} 
    test_crypto.cpp
    aes_crypto.cpp
    des_crypto.cpp
    file_utils.cpp
)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the warning level
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W3)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

# Set the preprocessor definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:WIN32;_DEBUG;_CONSOLE>
  $<$<CONFIG:Release>:WIN32;NDEBUG;_CONSOLE>
)

# Set the include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/cryptopp)

# Set the library directories and link libraries
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/cryptopp/.vs/build/x64/Linux/libcryptopp.a)
  elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/cryptopp/.vs/build/x64/Mac/libcryptopp.a)
  else()
  target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/cryptopp/.vs/build/x64/Release/libcryptopp.a)
  endif()
endif()
