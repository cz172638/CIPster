
function(opener_add_definition)
    foreach(ARG ${ARGV})
        set_property(GLOBAL APPEND PROPERTY OPENER_DEFINITION ${ARG})
    endforeach(ARG)
endfunction()

##############################################
# Adds platform specific include directories #
##############################################
macro(opener_platform_support ARGS)

    if(OpENer_PLATFORM STREQUAL "")
        message(FATAL_ERROR "No platform selected!")
    endif()

    include( ${OpENer_BUILDSUPPORT_DIR}/${OpENer_PLATFORM}/OpENer_PLATFORM_${ARGS}.cmake)
    opener_platform_spec()
endmacro()


#######################################
# Adds common Include directories     #
#######################################
macro(opener_common_includes)
    set( SRC_DIR "${PROJECT_SOURCE_DIR}/src" )
    set( CIP_SRC_DIR "${SRC_DIR}/cip" )
    set( ENET_ENCAP_SRC_DIR "${SRC_DIR}/enet_encap" )
    set( PORTS_SRC_DIR "${SRC_DIR}/ports")
    set( UTILS_SRC_DIR "${SRC_DIR}/utils")

    include_directories(
        ${PROJECT_SOURCE_DIR}
        ${SRC_DIR}
        ${CIP_SRC_DIR}
        ${ENET_ENCAP_SRC_DIR}
        ${PORTS_SRC_DIR}
        ${UTILS_SRC_DIR}
        ${OpENer_CIP_OBJECTS_DIR}
        )
endmacro()

macro(opener_add_cip_object NAME DESCRIPTION)
  set(OpENer_CIP_OBJECT_${NAME} OFF CACHE BOOL "${DESCRIPTION}")

  foreach(dependencies ${ARGN})
    if(NOT ${dependencies})
        return()
    endif()
  endforeach()

  if( NOT OpENer_CIP_OBJECT_${NAME} )
    return()
  endif()

endmacro()


#######################################
# Creates options for trace level     #
#######################################
macro(createTraceLevelOptions)
    add_definitions( -DOPENER_WITH_TRACES )
    set( TRACE_LEVEL 0 )
    set( OpENer_TRACE_LEVEL_ERROR ON CACHE BOOL "Error trace level" )
    set( OpENer_TRACE_LEVEL_WARNING ON CACHE BOOL "Warning trace level" )
    set( OpENer_TRACE_LEVEL_STATE ON CACHE BOOL "State trace level" )
    set( OpENer_TRACE_LEVEL_INFO ON CACHE BOOL "Info trace level" )

    if(OpENer_TRACE_LEVEL_ERROR)
        math( EXPR TRACE_LEVEL "${TRACE_LEVEL} + 1" )
    endif()

    if(OpENer_TRACE_LEVEL_WARNING)
        math( EXPR TRACE_LEVEL "${TRACE_LEVEL} + 2" )
    endif()

    if(OpENer_TRACE_LEVEL_STATE)
        math( EXPR TRACE_LEVEL "${TRACE_LEVEL} + 4" )
    endif()

    if(OpENer_TRACE_LEVEL_INFO)
        math( EXPR TRACE_LEVEL "${TRACE_LEVEL} + 8" )
    endif()

    add_definitions(-DOPENER_TRACE_LEVEL=${TRACE_LEVEL})
endmacro()
