cmake_minimum_required(VERSION 3.10.2)
project("LuaDiagnosticsHook")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lua_diagnostics SHARED
    lua_diagnostics.cpp
)

# Pulls in the native Android logging libraries for system diagnostic stability
find_library(log-lib log)
target_link_libraries(lua_diagnostics ${log-lib})
