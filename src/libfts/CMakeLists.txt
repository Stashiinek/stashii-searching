set(target_name libfts)



add_library(${target_name} STATIC
    libfts/funct.cpp
    libfts/funct.hpp)

target_include_directories(
      ${target_name}
      PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
