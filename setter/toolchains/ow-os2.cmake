if(NOT ${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux|Windows")
    message(FATAL_ERROR "Unsupported system")
endif()

if(NOT ${CMAKE_HOST_SYSTEM_PROCESSOR} MATCHES "x86_64|i386")
    message(FATAL_ERROR "Unsupported architecture")
endif()

if("$ENV{WATCOM}" STREQUAL "")
    if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
        set(ENV{WATCOM} "/opt/watcom")
    else()
        set(ENV{WATCOM} "C:\\WATCOM")
    endif()
endif()

if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    if(${CMAKE_HOST_SYSTEM_PROCESSOR} MATCHES "x86_64")
        set(WATCOM_BIN_PATH "$ENV{WATCOM}/binl64/")
        set(ENV{PATH} "$ENV{WATCOM}/binl64:$ENV{WATCOM}/binl:$ENV{PATH}")
    else()
        set(WATCOM_BIN_PATH "$ENV{WATCOM}/binl/")
        set(ENV{PATH} "$ENV{WATCOM}/binl:$ENV{PATH}")
    endif()

    set(ENV{EDPATH} "$ENV{WATCOM}/eddat")
    set(ENV{WIPFC} "$ENV{WATCOM}/wipfc")
else()
    if(${CMAKE_HOST_SYSTEM_PROCESSOR} MATCHES "x86_64")
        set(WATCOM_BIN_PATH "$ENV{WATCOM}\\binnt64\\")
        set(ENV{PATH} "$ENV{WATCOM}\\binnt64;$ENV{WATCOM}/binnt;$ENV{PATH}")
    else()
        set(ENV{PATH} "$ENV{WATCOM}\\binnt;$ENV{PATH}")
        set(WATCOM_BIN_PATH "$ENV{WATCOM}\\binnt\\")
    endif()

    set(ENV{EDPATH} "$ENV{WATCOM}\\eddat")
    set(ENV{WIPFC} "$ENV{WATCOM}\\wipfc")
endif()

add_compile_options(-3r)
add_compile_options(-mf)
add_compile_options(-l=os2v2)
set(CMAKE_SYSTEM_NAME OS2)
set(CMAKE_SYSTEM_PROCESSOR X86)
set(CMAKE_C_COMPILER "${WATCOM_BIN_PATH}wcl386")