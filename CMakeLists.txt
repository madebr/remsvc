cmake_minimum_required(VERSION 3.30)
project(remsvc C CXX)

include(CMakeDependentOption)

add_subdirectory(mspdb)

cmake_dependent_option(REMSVC_MSPDB "Enabled MS PDB 4.1 support" OFF "TARGET MSPDB::MSPDB41" OFF)
cmake_dependent_option(REMSVC_RECCMP "Build accurate executables" OFF "MSVC" OFF)

if(REMSVC_RECCMP)
    set(CMAKE_C_FLAGS "/W2 /GX /D \"WIN32\" /D \"_WINDOWS\"")
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

add_executable(rec1
    c1/afar.cpp
    c1/afar.h
    c1/aglobals.cpp
    c1/aglobals.h
    c1/agrammar.cpp
    c1/agrammar.h
    c1/ainline.cpp
    c1/ainline.h
    c1/alexer.cpp
    c1/alexer.h
    c1/alloc.cpp
    c1/alloc.h
    c1/aoutline.cpp
    c1/aoutline.h
    c1/atrees.cpp
    c1/atrees.h
    c1/based.cpp
    c1/based.h
    c1/bigmath.cpp
    c1/bigmath.h
    c1/c1_types.h
    c1/cast.cpp
    c1/cast.h
    c1/chksum.cpp
    c1/chksum.h
    c1/cmath.cpp
    c1/cmath.h
    c1/<common>.cpp
    c1/<common>.h
    c1/const.cpp
    c1/const.h
    c1/cvserver.cpp
    c1/cvserver.h
    c1/cvtoil.cpp
    c1/cvtoil.h
    c1/dict.cpp
    c1/dict.h
    c1/error.cpp
    c1/error.h
    c1/esubit.cpp
    c1/esubit.h
    c1/esu.cpp
    c1/esu.h
    c1/esumem.cpp
    c1/esumem.h
    c1/esutil.cpp
    c1/esutil.h
    c1/esutree.cpp
    c1/esutree.h
    c1/findptrs.cpp
    c1/findptrs.h
    c1/fmath.cpp
    c1/fmath.h
    c1/forceinc.cpp
    c1/forceinc.h
    c1/funcs.cpp
    c1/funcs.h
    c1/function.cpp
    c1/function.h
    c1/getflags.cpp
    c1/getflags.h
    c1/globals.cpp
    c1/globals.h
    c1/grammar.cpp
    c1/grammar.h
    c1/gramut.cpp
    c1/gramut.h
    c1/iccLINE.cpp
    c1/iccLINE.h
    c1/iccpch.cpp
    c1/iccpch.h
    c1/il.cpp
    c1/il.h
    c1/ilsink.cpp
    c1/ilsink.h
    c1/initil.cpp
    c1/initil.h
    c1/initmain.cpp
    c1/initmain.h
    c1/intrin.cpp
    c1/intrin.h
    c1/io.cpp
    c1/io.h
    c1/ipm.cpp
    c1/ipm.h
    c1/iset.cpp
    c1/iset.h
    c1/list.cpp
    c1/list.h
    c1/loops.cpp
    c1/loops.h
    c1/main.cpp
    c1/main.h
    c1/mre.cpp
    c1/mre.h
    c1/nbrowser.cpp
    c1/nbrowser.h
    c1/newsym.cpp
    c1/newsym.h
    c1/nheapall.cpp
    c1/nheapall.h
    c1/outdname.cpp
    c1/outdname.h
    c1/ovcheck.cpp
    c1/ovcheck.h
    c1/p0chrmap.cpp
    c1/p0chrmap.h
    c1/p0expr.cpp
    c1/p0expr.h
    c1/p0gettok.cpp
    c1/p0gettok.h
    c1/p0id.cpp
    c1/p0id.h
    c1/p0io.cpp
    c1/p0io.h
    c1/p0keys.cpp
    c1/p0keys.h
    c1/p0macros.cpp
    c1/p0macros.h
    c1/p0pragma.cpp
    c1/p0pragma.h
    c1/p0prepro.cpp
    c1/p0prepro.h
    c1/p0scan.cpp
    c1/p0scan.h
    c1/p1_init.cpp
    c1/p1_init.h
    c1/pch.cpp
    c1/pch.h
    c1/pdbmgr.cpp
    c1/pdbmgr.h
    c1/pragma.cpp
    c1/pragma.h
    c1/qtime2.cpp
    c1/qtime2.h
    c1/sigmgr.cpp
    c1/sigmgr.h
    c1/sizes.cpp
    c1/sizes.h
    c1/stmt.cpp
    c1/stmt.h
    c1/symbols.cpp
    c1/symbols.h
    c1/symtable.cpp
    c1/symtable.h
    c1/timing.cpp
    c1/timing.h
    c1/toil.cpp
    c1/toil.h
    c1/toinil.cpp
    c1/toinil.h
    c1/Token_IO.cpp
    c1/Token_IO.h
    c1/tokens.cpp
    c1/tokens.h
    c1/trees.cpp
    c1/trees.h
    c1/typebldr.cpp
    c1/typebldr.h
    c1/types.cpp
    c1/types.h
    c1/typesym.cpp
    c1/typesym.h
    c1/yyaction.cpp
    c1/yyaction.h
    c1/zeegee.cpp
    c1/zeegee.h

    c1/zz_diagnostic.cpp
    c1/zz_diagnostic.h
    c1/zz_unknown.cpp
    c1/zz_unknown.h
)
if(MINGW)
    target_link_libraries(rec1 PRIVATE msvcr90)
endif()
if(REMSVC_MSPDB)
    target_compile_definitions(rec1 PRIVATE WITH_MSPDB)
    target_link_libraries(rec1 PRIVATE MSPDB::MSPDB41)
endif()
if(REMSVC_RECCMP)
    set_property(TARGET rec1 PROPERTY OUTPUT_NAME "C1")
    set_property(TARGET rec1 PROPERTY SUFFIX ".EXE")
endif()
set_property(TARGET rec1 PROPERTY C_STANDARD 90)

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
