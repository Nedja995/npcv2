################################################
#
#
# 	Third paty projects
#
#
#################################################

if(THIRD_NCPPCORE_DOWNLOAD)
	#######
	# Paths
	#
	get_filename_component(THIRD_NCPPCORE_REL ${THIRD_NCPPCORE_SRC} REALPATH)

	find_package(Threads REQUIRED)

	# Enable ExternalProject CMake module
	include(ExternalProject)

	# Download and install GoogleTest
	 ExternalProject_Add(
		 NCPPCORE
		 URL https://github.com/Nedja995/ncpp-core/archive/master.zip
		# SOURCE_DIR ./extern/ #${THIRD_FIRST}
		 PREFIX ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/first
		 #Disable install step
		 INSTALL_COMMAND ""
	 )

	# Set gtest properties
	 ExternalProject_Get_Property(NCPPCORE source_dir binary_dir)
	 set_target_properties(NCPPCORE PROPERTIES
		 "imported_location" "${binary_dir}/NCPPCORE.a"
		 "imported_link_interface_libraries" "${cmake_thread_libs_init}"
	    "interface_include_directories" "${source_dir}/include"
		"LIBRARY_OUTPUT_PATH" "${MAINFOLDER}/lib"
		"BINARY_DIR" "${MAINFOLDER}/lib"
	 )

	# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
	include_directories("${source_dir}/include")

	include_directories(NCPPCORE ${source_dir}/include)


	# Second argument need when extern project is out of source tree directory
	#ADD_SUBDIRECTORY(${THIRD_NCPPCORE_REL} "${CMAKE_CURRENT_BINARY_DIR}/fdep")

	target_link_libraries(NCPPCORE ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/NCPPCORE.lib)
else()
	get_filename_component(THIRD_NCPPCORE_REL ${THIRD_NCPPCORE_SRC} REALPATH)
	add_subdirectory("${THIRD_NCPPCORE_REL}" "${CMAKE_CURRENT_BINARY_DIR}/path")
	target_link_libraries(${project_BIN} ${THIRD_NCPPCORE_NAME})
	#add_dependencies(${project_BIN} NCPPCORE)
	#SET_TARGET_PROPERTIES(NCPPCORE PROPERTIES "LIBRARY_OUTPUT_PATH" "${MAINFOLDER}/bin")
	
endif()
