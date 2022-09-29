set(target_name libfts)



add_library(${target_name} STATIC
    libfts/summ.cpp
    libfts/summ.hpp)

target_include_directories(
      ${target_name}
      PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
