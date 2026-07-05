macro(fake_owl_compile_and_embed output_var file)

    set(multiArgs LINK_LIBRARIES)
    cmake_parse_arguments(ARG "" "" "${multiArgs}" ${ARGN})

    get_filename_component(basefile ${file} NAME)
    set(targetName ${basefile})

    if (TARGET ${targetName})
        message("Target ${targetName} exists. Creating unique name to satisfy cmake...")
    endif()

    while (TARGET ${targetName})
        set(targetName ${targetName}X)
    endwhile()
    message("Adding target: ${targetName}")

    add_library(${targetName} SHARED ${file})
    # TODO: make this work:
    #target_compile_definitions(${targetName} PUBLIC __CUDA_ARCH__)
    target_compile_definitions(${targetName} PUBLIC FAKE_OWL_DEFINE_ENTRY_POINTS)
    set_target_properties(${targetName} PROPERTIES LINKER_LANGUAGE "CXX")
    set_source_files_properties(${targetName} PROPERTIES LANGUAGE "CXX")
    target_link_libraries(${targetName} ${fakeOwl_LIBRARY} ${ARG_LINK_LIBRARIES})
    #set_property(TARGET ${targetName} PROPERTY INTERPROCEDURAL_OPTIMIZATION True)
    #set_property(TARGET ${targetName} PROPERTY COMPILE_FLAGS "-lto")

    set(embedded_file ${CMAKE_CURRENT_BINARY_DIR}/fakeOwl_${targetName}_embedded.c)

    # Suffix used for dynamic libraries
    if (APPLE)
        set(suffixDL "dylib")
    elseif(WIN32)
        set(suffixDL "dll")
    else()
        set(suffixDL "so")
    endif()

    file(
        WRITE ${embedded_file}
        "#ifdef __cplusplus
        extern \"C\" {
        #endif

        const unsigned char ${output_var}[] = \"${CMAKE_CURRENT_BINARY_DIR}/lib${targetName}.${suffixDL}\";

        #ifdef __cplusplus
        }
        #endif"
    )

    set(${output_var} ${embedded_file})

endmacro()
