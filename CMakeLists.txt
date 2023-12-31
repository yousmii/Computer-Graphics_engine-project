cmake_minimum_required(VERSION 3.5)

project(engine)

############################################################
# Set compiler flags
############################################################
# If supported by your compiler, you can add the -Wall, -Wextra, –fstack-protector-all and -g3 flags here.
set(OWN_GXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################
set(engine_sources
	src/engine.cc
	src/utils/ini_configuration.cc
	src/utils/l_parser.cc
		src/utils/easy_image.cc
		src/l_systems.cc
		src/generate.cc
		src/utils/vector3d.cc
		src/2D/points_n_lines.cc
		src/3D/transformations.cc
		src/3D/wireframes.cpp
		src/3D/world3D.cpp
		src/3D/figure.cpp
		src/utils/utilities.cpp
        src/3D/zbuffer.cpp
)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_executable( ${exe_name} ${engine_sources} )
install( TARGETS ${exe_name} DESTINATION ${PROJECT_SOURCE_DIR}/ )
