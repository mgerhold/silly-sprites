function(setup_angelscript_addon_dependencies)
    # Debugger
    add_library(angelscript_debugger STATIC
            ${angelscript_SOURCE_DIR}/../../../add_on/debugger/debugger.h
            ${angelscript_SOURCE_DIR}/../../../add_on/debugger/debugger.cpp
    )
    target_include_system_directories(angelscript_debugger
            PUBLIC ${angelscript_SOURCE_DIR}/../../../add_on/debugger
    )
    target_link_system_libraries(angelscript_debugger PRIVATE angelscript)

    # Array
    add_library(angelscript_array STATIC
            ${angelscript_SOURCE_DIR}/../../../add_on/scriptarray/scriptarray.h
            ${angelscript_SOURCE_DIR}/../../../add_on/scriptarray/scriptarray.cpp
    )
    target_include_system_directories(angelscript_array
            PUBLIC ${angelscript_SOURCE_DIR}/../../../add_on/array
    )
    target_link_system_libraries(angelscript_array PRIVATE angelscript)

    # Math
    add_library(angelscript_math STATIC
            ${angelscript_SOURCE_DIR}/../../../add_on/scriptmath/scriptmath.h
            ${angelscript_SOURCE_DIR}/../../../add_on/scriptmath/scriptmath.cpp
            ${angelscript_SOURCE_DIR}/../../../add_on/scriptmath/scriptmathcomplex.h
            ${angelscript_SOURCE_DIR}/../../../add_on/scriptmath/scriptmathcomplex.cpp
    )
    target_include_system_directories(angelscript_math
            PUBLIC ${angelscript_SOURCE_DIR}/../../../add_on/scriptmath
    )
    target_link_system_libraries(angelscript_math PRIVATE angelscript)

    # Datetime
    add_library(angelscript_datetime STATIC
            ${angelscript_SOURCE_DIR}/../../../add_on/datetime/datetime.h
            ${angelscript_SOURCE_DIR}/../../../add_on/datetime/datetime.cpp
    )
    target_include_system_directories(angelscript_datetime
            PUBLIC ${angelscript_SOURCE_DIR}/../../../add_on/datetime
    )
    target_link_system_libraries(angelscript_datetime PRIVATE angelscript)

    # std::string
    add_library(angelscript_scriptstdstring STATIC
            ${angelscript_SOURCE_DIR}/../../../add_on/scriptstdstring/scriptstdstring.h
            ${angelscript_SOURCE_DIR}/../../../add_on/scriptstdstring/scriptstdstring.cpp
            ${angelscript_SOURCE_DIR}/../../../add_on/scriptstdstring/scriptstdstring_utils.cpp
    )
    target_include_system_directories(angelscript_scriptstdstring
            PUBLIC ${angelscript_SOURCE_DIR}/../../../add_on/scriptstdstring
    )
    target_link_system_libraries(angelscript_scriptstdstring PRIVATE angelscript)

    # script builder
    add_library(angelscript_scriptbuilder STATIC
            ${angelscript_SOURCE_DIR}/../../../add_on/scriptbuilder/scriptbuilder.h
            ${angelscript_SOURCE_DIR}/../../../add_on/scriptbuilder/scriptbuilder.cpp
    )
    target_include_system_directories(angelscript_scriptbuilder
            PUBLIC ${angelscript_SOURCE_DIR}/../../../add_on/scriptbuilder
    )
    target_link_system_libraries(angelscript_scriptbuilder PRIVATE angelscript)
endfunction()
