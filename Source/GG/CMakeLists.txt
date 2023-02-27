cmake_minimum_required(VERSION 3.8)

message("\n=== ADDING GG PROJECTS ===")

set(GG_INC ${ROOTDIR}/Include/GG)
set(GG_SRC ${ROOTDIR}/Source/GG)

function( GG_PROJ N IncDir SrcDir )
    set(PROJECT ${N})
    set(INCDIR ${IncDir})
    set(SRCDIR ${SrcDir})
    
    message("PROJECT: ${PROJECT}")
    message("INC DIR: ${INCDIR}")
    message("SRC DIR: ${SRCDIR}")
    message("\n")
    add_subdirectory(${N})
    
endfunction()


GG_PROJ( Common ${GG_INC}/Common ${GG_SRC}/Common )
GG_PROJ( EntitySystem ${GG_INC}/EntitySystem ${GG_SRC}/EntitySystem )
GG_PROJ( App ${GG_INC}/App ${GG_SRC}/App )
GG_PROJ( Core ${GG_INC}/Core ${GG_SRC}/Core )
GG_PROJ( Rendering ${GG_INC}/Rendering ${GG_SRC}/Rendering ) 