set(SDL_SHARED OFF)
set(SDL_STATIC ON)
add_subdirectory(SDL)

add_subdirectory(glad EXCLUDE_FROM_ALL)

# Assimp
FetchContent_Declare(
  assimp_proj
  GIT_REPOSITORY https://github.com/assimp/assimp.git
  GIT_TAG        master
  GIT_SHALLOW    TRUE   # For faster cloning, requires Git 2.15+
)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static library" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Disable building tests" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "Do not treat Assimp warnings as hard errors" FORCE)
FetchContent_MakeAvailable(assimp_proj)