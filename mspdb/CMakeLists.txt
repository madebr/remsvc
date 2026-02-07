include(cmake/detectcpu.cmake)

DetectTargetCPUArchitectures(DETECTED_ARCHS)

cmake_dependent_option(USE_ORIGINAL_MSPDB "Use original MSPDB instead of remspdb" TRUE "WIN32;CPU_X86" FALSE)

add_library(remspdb41 SHARED
    src/crc32.cpp
    src/mspdb41.def
)
target_include_directories(remspdb41 PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")
target_include_directories(remspdb41 PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/decomp>")
if(WIN32)
    set_property(TARGET remspdb41 PROPERTY PREFIX "")
endif()

if(USE_ORIGINAL_MSPDB)
    add_library(MSPDB::MSPDB41 SHARED IMPORTED GLOBAL)
    set_property(TARGET MSPDB::MSPDB41 PROPERTY IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/x86/mspdb41.lib")
    set_property(TARGET MSPDB::MSPDB41 PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include")
else()
    add_library(MSPDB::MSPDB41 ALIAS remspdb41)
endif()
