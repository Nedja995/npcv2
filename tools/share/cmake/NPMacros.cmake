MACRO(REQUIRED_THIRD target description targetName)
	OPTION("THIRD_${target}_DEV" "${description}" YES)
	SET("THIRD_${target}_NAME" ${targetName})
	SET("THIRD_${target}_SRC"
		"${CMAKE_SOURCE_DIR}/../" 
		CACHE PATH 
		"Path to extern project. Or can download with next option"
	)
	#not work for now
	#get_filename_component("THIRD_${target}_REL" "THIRD_${target}_SRC" REALPATH)
	OPTION("THIRD_${target}_DOWNLOAD" "If THIRD_${target}_SRC doesn't set this is requried" YES)
ENDMACRO()
