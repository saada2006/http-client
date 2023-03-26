file(GLOB_RECURSE source "*.cpp" "*.h" "*.hpp" ".c")

add_executable("client" ${source})

if(WIN32)
    target_link_libraries("client" PRIVATE "ws2_32" "iphlpapi")
endif(WIN32)