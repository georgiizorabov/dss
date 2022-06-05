project(KVS)

set(HEADER_FILES
        fileHandler.h
        Filter.h
        json.h
        kvs.h
        Log.h
        SparseSSTable.h
        SStable.h
        )

set(SOURCE_FILES
        fileHandler.cpp
        Filter.cpp
        kvs.cpp
        Log.cpp
        SparseSSTable.cpp
        SSTable.cpp
        )

add_library(KVS_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})