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