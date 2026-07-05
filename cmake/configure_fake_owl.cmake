set(CONFIGURE_FAKE_OWL_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE INTERNAL "")

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
    set_target_properties(${targetName} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
    # TODO: make this work:
    #target_compile_definitions(${targetName} PUBLIC __CUDA_ARCH__)
    target_compile_definitions(${targetName} PUBLIC FAKE_OWL_DEFINE_ENTRY_POINTS)
    set_target_properties(${targetName} PROPERTIES LINKER_LANGUAGE "CXX")
    set_source_files_properties(${targetName} PROPERTIES LANGUAGE "CXX")
    target_link_libraries(${targetName} ${fakeOwl_LIBRARY} ${ARG_LINK_LIBRARIES})
    if (MSVC)
        target_sources(${targetName} PRIVATE "${CONFIGURE_FAKE_OWL_DIR}/optix_launch_params_shim.cpp")
    endif()
    #set_property(TARGET ${targetName} PROPERTY INTERPROCEDURAL_OPTIMIZATION True)
    #set_property(TARGET ${targetName} PROPERTY COMPILE_FLAGS "-lto")

    set(embedded_file ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/fakeOwl_${targetName}_embedded.c)

    file(
        GENERATE OUTPUT ${embedded_file}
        CONTENT
"#ifdef __cplusplus
extern \"C\" {
#endif

const unsigned char ${output_var}[] = \"$<TARGET_FILE:${targetName}>\";

#ifdef __cplusplus
}
#endif"
    )

    set(${output_var} ${embedded_file})

endmacro()
