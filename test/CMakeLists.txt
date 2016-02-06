
SET (testapp_srcs 
	${CMAKE_SOURCE_DIR}/test/Main.cpp)

#SET (project_LIBS ${Boost_LIBRARIES} ${QT_LIBRARIES} ${Log4Cxx_LIBRARIES})
SET (testapp_BIN "npcvTestApp")

add_executable(${testapp_BIN} ${testapp_srcs})
TARGET_LINK_LIBRARIES(${testapp_BIN} ${PROJECT_NAME})
include_directories(${testapp_BIN} ${CMAKE_SOURCE_DIR}/include)
add_dependencies(${testapp_BIN} ${PROJECT_NAME})