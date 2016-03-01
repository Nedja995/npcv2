
#
########################
# 	NPCV HEADERS
#
#
# npcv base
SET (npcvbase_headers
	${NPCV_INCLUDE_DIR}/Config.h

	${NPCV_INCLUDE_DIR}/LogListenerDebug.h
	${NPCV_INCLUDE_DIR}/Toolset.h
	${NPCV_INCLUDE_DIR}/appinfo.h
	${NPCV_INCLUDE_DIR}/Application.h
)
# processes
SET (processes_headers
	${NPCV_INCLUDE_DIR}/processes/IPMatrixApply.h
	${NPCV_INCLUDE_DIR}/processes/IProcessImage.h
	${NPCV_INCLUDE_DIR}/processes/ProcessGray.h
	${NPCV_INCLUDE_DIR}/processes/IPBlending.h
)
# abstractions
SET (abs_headers
	${NPCV_INCLUDE_DIR}/abs/IFilePath.h
	${NPCV_INCLUDE_DIR}/abs/IImageStream.h
	${NPCV_INCLUDE_DIR}/abs/ILogListener.h
	${NPCV_INCLUDE_DIR}/abs/IProcess.h
	${NPCV_INCLUDE_DIR}/abs/IDialogFileSelect.h
)
# types
SET (types_headers
	${NPCV_INCLUDE_DIR}/types/Image.h
#	${NPCV_INCLUDE_DIR}/types/
)
# utils
SET (utils_headers
	${NPCV_INCLUDE_DIR}/utils/Profiler.h
	${NPCV_INCLUDE_DIR}/utils/ImageStreamSTB.h
	${NPCV_INCLUDE_DIR}/utils/ImageStreamNP.h
	${NPCV_INCLUDE_DIR}/utils/ResourceManager.h
	${NPCV_INCLUDE_DIR}/utils/SamplingImage.h
	${NPCV_INCLUDE_DIR}/utils/converters/NPipeRequestToImageProcess.h
#	${NPCV_INCLUDE_DIR}/utils/
)
# ui
SET (ui_headers
	${NPCV_INCLUDE_DIR}/ui/DialogFileSelectWindows.h
)

SET (npcv_headers 
	${npcvbase_headers}
	${abs_headers}
	${processes_headers}
	${types_headers}
	${utils_headers}
	${ui_headers}
)

SOURCE_GROUP("Header Files\\\\abs" FILES ${abs_headers})
SOURCE_GROUP("Header Files\\\\types" FILES ${types_headers})
SOURCE_GROUP("Header Files\\\\processes" FILES ${processes_headers})
SOURCE_GROUP("Header Files\\\\utils" FILES ${utils_headers})
SOURCE_GROUP("Header Files\\\\ui" FILES ${ui_headers})
	
	
#
############################
#
#	NPCV SOURCES
#	
# npcv base
SET (npcvbase_source
	${NPCV_SRC_DIR}/Log.cpp
	${NPCV_SRC_DIR}/LogListenerDebug.cpp
	${NPCV_SRC_DIR}/Toolset.cpp
	${NPCV_SRC_DIR}/Application.cpp
)
# processes
SET (processes_source
	${NPCV_SRC_DIR}/processes/IPMatrixApply.cpp
	${NPCV_SRC_DIR}/processes/IProcessImage.cpp
	${NPCV_SRC_DIR}/processes/IPBlending.cpp
	${NPCV_SRC_DIR}/processes/ProcessGray.cpp
)
# types
SET (types_source
	${NPCV_SRC_DIR}/types/Image.cpp
#	${NPCV_SRC_DIR}/types/
)
# ui
SET (ui_source
	${NPCV_SRC_DIR}/ui/DialogFileSelectWindows.cpp
)
# utils
SET (utils_source
	${NPCV_SRC_DIR}/utils/Profiler.cpp
	${NPCV_SRC_DIR}/utils/ImageStreamSTB.cpp
	${NPCV_SRC_DIR}/utils/ImageStreamNP.cpp
	${NPCV_SRC_DIR}/utils/ResourceManager.cpp
	${NPCV_SRC_DIR}/utils/SamplingImage.cpp
	${NPCV_SRC_DIR}/utils/converters/NPipeRequestToImageProcess.cpp
#	${NPCV_INCLUDE_DIR}/utils/
)

SET (npcv_source
	${npcvbase_source}
	${processes_source}
	${types_source}
	${utils_source}
	${ui_source}
)

SOURCE_GROUP("Source Files\\\\types" FILES ${types_source})
SOURCE_GROUP("Source Files\\\\processes" FILES ${processes_source})
SOURCE_GROUP("Source Files\\\\utils" FILES ${utils_source})	
SOURCE_GROUP("Source Files\\\\ui" FILES ${ui_source})	
	
#SET (project_LIBS ${Boost_LIBRARIES} ${QT_LIBRARIES} ${Log4Cxx_LIBRARIES})


ADD_LIBRARY(${PROJECT_NAME} ${npcv_source} ${npcv_headers})
#TARGET_LINK_LIBRARIES(${project_BIN} ${project_LIBS})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)

include_directories(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/include
									${CMAKE_SOURCE_DIR}/thirdparty/include)

# #
# # Add third lib FIRST
# #
# INCLUDE_DIRECTORIES(${THIRD_FIRST_SRC}/src)

# ADD_DEPENDENCIES(${project_BIN} ${THIRD_FIRST_NAME})

# if(MSVC)
	# TARGET_LINK_LIBRARIES( ${project_BIN} 
		# ${THIRD_FIRST_SRC}/lib/${CMAKE_CFG_INTDIR}/${THIRD_FIRST_NAME}.lib)
# else()
	# TARGET_LINK_LIBRARIES(${project_BIN} ${THIRD_FIRST_NAME})
# endif()
