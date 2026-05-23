find_package(Threads)

set(HEADERS
    Bounds.h
    Buffer.h
    ClosestHit.h
    Context.h
    DataType.h
    Geom.h
    GeomGroup.h
    GeomType.h
    Group.h
    InstanceGroup.h
    Intersect.h
    Logging.h
    Miss.h
    Module.h
    Params.h
    Program.h
    RayGen.h
    Resource.h
    Texture.h
    Trace.h
    VarDecl.h
    Visionaray.h
    VisionarayTexture.h
)

set(SOURCES
    Bounds.cpp
    Buffer.cpp
    ClosestHit.cpp
    Context.cpp
    Geom.cpp
    GeomGroup.cpp
    GeomType.cpp
    Group.cpp
    InstanceGroup.cpp
    Intersect.cpp
    Logging.cpp
    Miss.cpp
    Module.cpp
    Params.cpp
    Program.cpp
    RayGen.cpp
    Resource.cpp
    Texture.cpp
    Trace.cpp
    VarDecl.cpp
    Visionaray.cpp
    VisionarayTexture.cpp
)

set(SOURCES
    ${SOURCES}
    fake_cuda.cpp
    owl_ext.cpp
    owl_host.cpp
)

set(fakeOwl_LIBRARY owl PARENT_SCOPE)
add_library(owl ${HEADERS} ${SOURCES})
target_link_libraries(owl PUBLIC ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(owl INTERFACE
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/owl/fakeOwl>
  $<INSTALL_INTERFACE:include>
  $<INSTALL_INTERFACE:include/owl/fakeOwl>
)
add_library(owl::owl ALIAS owl)

# =========================================================
# Install
# =========================================================

include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/owlConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/owlConfig.cmake"
  INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
)

write_basic_package_version_file(
    "owlConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(TARGETS owl
    EXPORT owl_Exports
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT libraries
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libraries
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libraries
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/owl
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT headers
    FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hh"
        PATTERN "*.hpp"
        PATTERN "*.hxx"
        PATTERN "*.inl"
        PATTERN "*.inc"
        PATTERN "*.cuh"
)

install(EXPORT owl_Exports
    NAMESPACE owl::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/owl
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/owlConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/owlConfigVersion.cmake
    ${PROJECT_SOURCE_DIR}/cmake/configure_fake_owl.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/owl
)

set(CPACK_PACKAGE_NAME "fakeOWL")
set(CPACK_PACKAGE_VENDOR "Stefan Zellmann")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "fakeOWL, CPU emulation layer for OptiX and OWL")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
include(CPack)


