set(target_name app)

add_executable(${target_name})

include(CompileOptions)
set_compile_options(${target_name})

target_sources(
    ${target_name}
    PRIVATE
      app/main.cpp
)

target_include_directories(
      ${target_name}
      PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )

target_link_libraries(
    ${target_name}
    PRIVATE
      libfts
      CLI11
)
