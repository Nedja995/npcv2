#
# ZOOM IMAGE
#
# Add executable/project
add_executable(Demo_ZoomImage 
	${CMAKE_SOURCE_DIR}/samples/demos/ZoomImage.cpp)
# Include npcv library
include_directories(Demo_ZoomImage ${CMAKE_SOURCE_DIR}/include)
# Link with npcv library
TARGET_LINK_LIBRARIES(Demo_ZoomImage ${PROJECT_NAME})
add_dependencies(Demo_ZoomImage ${PROJECT_NAME})


#
# CONVOLUTION MATRIX
#
# Add executable/project
add_executable(Demo_ConvolutionMatrix 
	${CMAKE_SOURCE_DIR}/samples/demos/ConvolutionMatrix.cpp)
# Include npcv library
include_directories(Demo_ConvolutionMatrix ${CMAKE_SOURCE_DIR}/include)
# Link with npcv library
TARGET_LINK_LIBRARIES(Demo_ConvolutionMatrix ${PROJECT_NAME})
add_dependencies(Demo_ConvolutionMatrix ${PROJECT_NAME}) 

#
# EDGE DETECTION
#
# Add executable/project
add_executable(Demo_EdgeDetection
	${CMAKE_SOURCE_DIR}/samples/demos/EdgeDetection.cpp)
# Include npcv library
include_directories(Demo_EdgeDetection ${CMAKE_SOURCE_DIR}/include)
# Link with npcv library
TARGET_LINK_LIBRARIES(Demo_EdgeDetection ${PROJECT_NAME})
add_dependencies(Demo_EdgeDetection ${PROJECT_NAME})

#
# OCR ClASSIFY
#
# Add executable/project
add_executable(Demo_OCRClassify
	${CMAKE_SOURCE_DIR}/samples/demos/OCRClassify.cpp)
# Include npcv library
include_directories(Demo_OCRClassify ${CMAKE_SOURCE_DIR}/include)
# Link with npcv library
TARGET_LINK_LIBRARIES(Demo_OCRClassify ${PROJECT_NAME})
add_dependencies(Demo_OCRClassify ${PROJECT_NAME})

#
# EROSION
#
# Add executable/project
add_executable(Demo_Erosion
	${CMAKE_SOURCE_DIR}/samples/demos/Erosion.cpp)
# Include npcv library
include_directories(Demo_Erosion ${CMAKE_SOURCE_DIR}/include)
# Link with npcv library
TARGET_LINK_LIBRARIES(Demo_Erosion ${PROJECT_NAME})
add_dependencies(Demo_Erosion ${PROJECT_NAME})