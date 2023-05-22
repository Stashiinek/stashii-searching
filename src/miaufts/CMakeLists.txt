set(target_name miaufts)

add_library(${target_name} SHARED
    miaufts/miaufts.cpp
    miaufts/miaufts.hpp)

target_include_directories(
      ${target_name}
      PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}/build/Debug/_deps/csv-src
    )

target_link_libraries(
    ${target_name}
    PRIVATE
    	libfts
        nlohmann_json::nlohmann_json
    )
