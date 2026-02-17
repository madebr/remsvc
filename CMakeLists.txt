cmake_minimum_required(VERSION 3.30)
project(remsvc C)

include(CMakeDependentOption)

add_subdirectory(mspdb)

cmake_dependent_option(REMSVC_MSPDB "Enabled MS PDB 4.1 support" OFF "TARGET MSPDB::MSPDB41" OFF)
cmake_dependent_option(REMSVC_RECCMP "Build accurate executables" OFF "MSVC" OFF)

if(REMSVC_RECCMP)
    set(CMAKE_C_FLAGS "/W2 /GX /J /D \"WIN32\" /D \"_WINDOWS\"")
    set(CMAKE_C_FLAGS_DEBUG "/Gm /Zi /Od /D \"_DEBUG\"")
    set(CMAKE_C_FLAGS_RELEASE "/D \"NDEBUG\"")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "/Zi /D \"NDEBUG\"")
    set(CMAKE_C_FLAGS_MINSIZEREL "/Os /D \"NDEBUG\"")

    set(CMAKE_EXE_LINKER_FLAGS "/machine:I386")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/incremental:yes /debug")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/incremental:no")
    set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/incremental:no /debug")
    set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "/incremental:no")

    set(CMAKE_SHARED_LINKER_FLAGS "/machine:I386")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/incremental:yes /debug")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/incremental:no")
    set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "/incremental:no /debug")
    set(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL "/incremental:no")

    set(CMAKE_STATIC_LINKER_FLAGS "/machine:I386")

    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/decomp/compat")
    add_compile_definitions(REMSVC_RECCMP)
endif()

if(GNU)
    add_compile_options(-Wall -Wextra)
elseif(MSVC)
    add_compile_options(-W2)
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/decomp")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/portable")


add_executable(redumpbin
    frontend/dumpbin.c
)
if(MINGW)
    target_link_libraries(redumpbin PRIVATE msvcr90)
endif()
if(REMSVC_MSPDB)
    target_compile_definitions(redumpbin PRIVATE WITH_MSPDB)
    target_link_libraries(redumpbin PRIVATE MSPDB::MSPDB41)
endif()
if(REMSVC_RECCMP)
    set_property(TARGET redumpbin PROPERTY OUTPUT_NAME "DUMPBIN")
    set_property(TARGET redumpbin PROPERTY SUFFIX ".EXE")
endif()
set_property(TARGET redumpbin PROPERTY C_STANDARD 90)


add_executable(recl
    frontend/frontend.rc
    frontend/forms.c
    frontend/main.c
    frontend/compile.c
    frontend/util.c
    frontend/dos.c
)
if(MINGW)
    target_link_libraries(recl PRIVATE msvcr90)
endif()
if(REMSVC_MSPDB)
    target_compile_definitions(recl PRIVATE WITH_MSPDB)
    target_link_libraries(recl PRIVATE MSPDB::MSPDB41)
else()
    target_include_directories(recl PRIVATE $<TARGET_PROPERTY:MSPDB::MSPDB41,INTERFACE_INCLUDE_DIRECTORIES>)
endif()
if(REMSVC_RECCMP)
    set_property(TARGET recl PROPERTY OUTPUT_NAME "CL")
    set_property(TARGET recl PROPERTY SUFFIX ".EXE")
    target_compile_options(recl PRIVATE "/O1")
endif()
set_property(TARGET recl PROPERTY C_STANDARD 90)

add_executable(relib
    lib/lib.rc
    lib/main.c
)
set_property(TARGET relib PROPERTY C_STANDARD 90)
if(REMSVC_RECCMP)
    set_property(TARGET relib PROPERTY OUTPUT_NAME "LIB")
    set_property(TARGET relib PROPERTY SUFFIX ".EXE")
    target_compile_options(relib PRIVATE "/O2")
endif()

message(STATUS "REMSVC_MSPDB:  ${REMSVC_MSPDB}")
message(STATUS "REMSVC_RECCMP: ${REMSVC_RECCMP}")
