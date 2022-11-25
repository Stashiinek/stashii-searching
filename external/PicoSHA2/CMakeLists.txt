include(FetchContent)
FetchContent_Declare(
  PicoSHA2
  GIT_REPOSITORY https://github.com/okdshin/PicoSHA2
  GIT_TAG v1.0.0
  GIT_SHALLOW TRUE
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}
)

FetchContent_MakeAvailable(PicoSHA2)
