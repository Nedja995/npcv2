
#
########################
# 	LIBRARY HEADERS
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
# FILTERS HEADERS
SET (filters_headers
	${NPCV_INCLUDE_DIR}/filters/IPMatrixApply.h
	${NPCV_INCLUDE_DIR}/filters/IProcessImage.h
	${NPCV_INCLUDE_DIR}/filters/ProcessGray.h
	${NPCV_INCLUDE_DIR}/filters/IPBlending.h
)
# SEGMENTATION HEADERS
SET (segmentation_header
	${NPCV_INCLUDE_DIR}/segmentation/Treshold.h
)
# MORPHOLOGY HEADERS
SET (morphology_header
	${NPCV_INCLUDE_DIR}/morphology/Erosion.h
)
# geometric
SET (geometric_headers
	${NPCV_INCLUDE_DIR}/geometric/Zoom.h
)
# classification
SET (classification_headers
	${NPCV_INCLUDE_DIR}/classification/RegionEdge.h
)
# freatures
SET (freatures_headers
	${NPCV_INCLUDE_DIR}/freatures/EdgeDetectCanny.h
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
	${NPCV_INCLUDE_DIR}/types/Pixel.h
#	${NPCV_INCLUDE_DIR}/types/
)
# utils
SET (utils_headers
	${NPCV_INCLUDE_DIR}/utils/Profiler.h
	${NPCV_INCLUDE_DIR}/utils/ImageStreamSTB.h
	${NPCV_INCLUDE_DIR}/utils/ImageStreamNP.h
	${NPCV_INCLUDE_DIR}/utils/ResourceManager.h
	${NPCV_INCLUDE_DIR}/utils/SamplingImage.h
	${NPCV_INCLUDE_DIR}/utils/Sampling.h
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
	${filters_headers}
	${segmentation_headers}
	${morphology_header}
	${freatures_headers}
	${classification_headers}
	${types_headers}
	${utils_headers}
	${ui_headers}
)

SOURCE_GROUP("Header Files\\\\abs" FILES ${abs_headers})
SOURCE_GROUP("Header Files\\\\types" FILES ${types_headers})
SOURCE_GROUP("Header Files\\\\filters" FILES ${filters_headers})
SOURCE_GROUP("Header Files\\\\morphology" FILES ${morphology_header})
SOURCE_GROUP("Header Files\\\\segmentation" FILES ${segmentation_headers})
SOURCE_GROUP("Header Files\\\\geometric" FILES ${geometric_headers})
SOURCE_GROUP("Header Files\\\\freatures" FILES ${freatures_headers})
SOURCE_GROUP("Header Files\\\\classification" FILES ${classification_headers})
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
# FILTERS SRC
SET (filters_source
	${NPCV_SRC_DIR}/filters/IPMatrixApply.cpp
	${NPCV_SRC_DIR}/filters/IProcessImage.cpp
	${NPCV_SRC_DIR}/filters/IPBlending.cpp
	${NPCV_SRC_DIR}/filters/ProcessGray.cpp	
)
# segmentation
SET (segmentation_source
	${NPCV_SRC_DIR}/segmentation/Treshold.cpp
)
# MORPHOLOGY SRC
SET (morphology_source
	${NPCV_SRC_DIR}/morphology/Erosion.cpp
)
# geometric
SET (geometric_source
	${NPCV_SRC_DIR}/geometric/Zoom.cpp
)
# freatures
SET (freatures_source
	${NPCV_SRC_DIR}/freatures/EdgeDetectCanny.cpp
)
# classification
SET (classification_source
	${NPCV_SRC_DIR}/classification/RegionEdge.cpp
)
# types
SET (types_source
	${NPCV_SRC_DIR}/types/Image.cpp
	${NPCV_SRC_DIR}/types/Pixel.cpp
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
	${NPCV_SRC_DIR}/utils/Sampling.cpp
	${NPCV_SRC_DIR}/utils/converters/NPipeRequestToImageProcess.cpp
#	${NPCV_SRC_DIR}/utils/
)

SET (npcv_source
	${npcvbase_source}
	${filters_source}
	${segmentation_source}
	${morphology_source}
	${geometric_source}
	${classification_source}
	${freatures_source}
	${types_source}
	${utils_source}
	${ui_source}
)

SOURCE_GROUP("Source Files\\\\types" FILES ${types_source})
SOURCE_GROUP("Source Files\\\\filters" FILES ${filters_source})
SOURCE_GROUP("Source Files\\\\segmentation" FILES ${segmentation_source})
SOURCE_GROUP("Source Files\\\\morphology" FILES ${morphology_source})
SOURCE_GROUP("Source Files\\\\geometric" FILES ${geometric_source})
SOURCE_GROUP("Source Files\\\\freatures" FILES ${freatures_source})
SOURCE_GROUP("Source Files\\\\classification" FILES ${classification_source})
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
