cmake_minimum_required(VERSION 3.12)
project(CheatersCheetahCheatCpp)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_STATIC "Build the library with static links to libstdc++, libgcc, etc." OFF)
set(CCC_PROXY_LIB_NAME "winhttp" CACHE STRING "Output library file name")
set(SOURCES_FOLDER "src")
set(LIB_FOLDER "lib")
#set(MINGW_INCLUDE_FOLDER "/usr/x86_64-w64-mingw32/include/")

if(BUILD_STATIC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb")

add_subdirectory(${LIB_FOLDER}/PolyHook_2_0)

file(GLOB_RECURSE SOURCE_FILES
        "${SOURCES_FOLDER}/*.cpp"
)
add_library(CheatersCheetahCheatCpp SHARED ${SOURCE_FILES} dll.def)

add_dependencies(CheatersCheetahCheatCpp PolyHook_2)

target_link_libraries(CheatersCheetahCheatCpp PUBLIC PolyHook_2)

set_target_properties(CheatersCheetahCheatCpp PROPERTIES PREFIX "") # nuke the lib prefix from our libSuperHak
set_target_properties(CheatersCheetahCheatCpp PROPERTIES OUTPUT_NAME ${CCC_PROXY_LIB_NAME})

# i dont think this is actually necessary.
# i think clion was just misleading me because because i didn't set mingw build tools
#if (MINGW AND UNIX)
#    target_include_directories(CheatersCheetahCheatCpp SYSTEM PUBLIC ${MINGW_INCLUDE_FOLDER})
#endif()
target_include_directories(CheatersCheetahCheatCpp PUBLIC ${LIB_FOLDER}/PolyHook_2_0)
target_include_directories(CheatersCheetahCheatCpp PUBLIC ${LIB_FOLDER}/Il2CppInspectorPro/Il2CppInspector.Common/Cpp)
# this is stupid
target_include_directories(CheatersCheetahCheatCpp PUBLIC ${LIB_FOLDER}/PolyHook_2_0/zydis/include)
target_include_directories(CheatersCheetahCheatCpp PUBLIC ${LIB_FOLDER}/PolyHook_2_0/zydis/dependencies/zycore/include)
