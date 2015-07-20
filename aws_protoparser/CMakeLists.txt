# This CMake file is manually tested on Windows and Linux.

# Set particularly high to force up-to-date systems only.
cmake_minimum_required (VERSION 2.7)
project (aws_protoparser)

# Tell AWS_PROTOC where to find the input/output for protobuf files.
set(_PROTOC_DIR "${PROJECT_SOURCE_DIR}/proto")
set(_PROTOC_CPP_OUT "${PROJECT_BINARY_DIR}/protoc")

# The default ProtoBuf code isn't great; but I've fixed this below.

# Shared project
set(_PROTOPARSER_LINKAGE SHARED)

#--------------------------------------------------------------------
# This function uses the default/find_package "ProtoBuf" code to
# locate and then execute .proto files which are found beyond the
# initial directory.  While this isn't ideal (it isn't super fast
# or even remotely optimised) it works fine and tends not to cause
# any issues in my testing.
#--------------------------------------------------------------------

find_package(Protobuf REQUIRED)
function(AWS_PROTOC SRCS HDRS)
	file(MAKE_DIRECTORY "${_PROTOC_CPP_OUT}")

	# Throw the error
	if(NOT ARGN)
		message(SEND_ERROR "Error: AWS_PROTOC() called without any proto files")
		return()
	endif()

	# Set a basic include
	set(_protobuf_include_path -I ${_PROTOC_DIR})

	# Clear
	set(${SRCS})
	set(${HDRS})

	# Step through
	foreach(FIL ${ARGN})
		get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
		get_filename_component(DIR ${FIL} DIRECTORY)
		get_filename_component(FIL_WE ${FIL} NAME_WE)

		file(MAKE_DIRECTORY "${_PROTOC_CPP_OUT}/${DIR}/")

		list(APPEND ${SRCS} "${_PROTOC_CPP_OUT}/${DIR}/${FIL_WE}.pb.cc")
		list(APPEND ${HDRS} "${_PROTOC_CPP_OUT}/${DIR}/${FIL_WE}.pb.h")

		execute_process(
			COMMAND	${PROTOBUF_PROTOC_EXECUTABLE} --cpp_out=${_PROTOC_CPP_OUT} --proto_path=${_PROTOC_DIR} ${_PROTOC_DIR}/${FIL}
		)

		# Notify the user of the command so they can debug issues.
		message(STATUS "protoc --cpp_out=${_PROTOC_CPP_OUT} --proto_path=${_PROTOC_DIR} ${_PROTOC_DIR}/${FIL}")
	endforeach()

	set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
	set(${SRCS} ${${SRCS}} PARENT_SCOPE)
	set(${HDRS} ${${HDRS}} PARENT_SCOPE)
endfunction()


#--------------------------------------------------------------------
#
#                         SOURCE FILE WORK
#
#--------------------------------------------------------------------

# Proto files to compile
AWS_PROTOC(PROTO_SRCS PROTO_HDRS
	"ConfigProtoV2.proto"
	# Proto3 support (waiting for stability)
	#"ConfigProtoV3.proto"
)

# Common include for all targets
include_directories(
	"${PROJECT_SOURCE_DIR}"
	${PROTOBUF_INCLUDE_DIRS}
	${_PROTOC_CPP_OUT}
)

# Includies
set(ACT_PROTOPARSER_SOURCES
	${PROTO_HDRS}
	"aws_protoparser.hpp"
	
	${PROTO_SRCS}
	"example.cpp"
)


add_executable(aws_protoparser_test ${ACT_PROTOPARSER_SOURCES})
target_link_libraries(aws_protoparser_test ${PROTOBUF_LIBRARIES})


#--------------------------------------------------------------------
#
#                        Platform Support
#
#--------------------------------------------------------------------

# Windows code
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	# Dynamic libraries (if you need them...)
	#SET_TARGET_PROPERTIES(aws_protoparser_test PROPERTIES COMPILE_FLAGS "-DPROTOBUF_USE_DLLS")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

# Mac OS X specific code
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	add_definitions("-std=c++11")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

# Linux specific code
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	add_definitions("-std=c++11")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")