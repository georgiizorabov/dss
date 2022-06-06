project(KVS)

set(HEADER_FILES
        FileHandler.h
        Filter.h
        json.h
        KVS.h
        Log.h
        SparseSSTable.h
        SStable.h
        )

set(SOURCE_FILES
        FileHandler.cpp
        Filter.cpp
        KVS.cpp
        Log.cpp
        SparseSSTable.cpp
        SSTable.cpp
        )

add_library(KVS_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})