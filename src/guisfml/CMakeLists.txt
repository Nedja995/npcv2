FILE (GLOB_RECURSE npcvgui_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)


SET (NPCVGUI_DIR "${CMAKE_SOURCE_DIR}/src/npcvgui")

#
########################
# 	NPCV GUI HEADERS
#
# npcv gui
SET (npcvGui_headers
	${NPCVGUI_DIR}/include/NpcvGUI.h
)
# widgets
SET (widgets_headers
		${NPCVGUI_DIR}/include/widgets/IImageGUI.h
		${NPCVGUI_DIR}/include/widgets/ImageBox.h
		${NPCVGUI_DIR}/include/widgets/ImageInspectorBox.h
		${NPCVGUI_DIR}/include/widgets/ResizableImage.h
		${NPCVGUI_DIR}/include/widgets/WinMatrixFilter.h
)

SOURCE_GROUP("Header Files\\widgets" FILES ${widgets_headers})

#
########################
# 	NPCV GUI SOURCES
#
# npcv gui
SET (npcvGui_src
	${NPCVGUI_DIR}/src/NpcvGUI.cpp
	${NPCVGUI_DIR}/MainGUI.cpp
	${NPCVGUI_DIR}/guiMain.cpp
)
# widgets
SET (widgets_src
		${NPCVGUI_DIR}/src/widgets/ImageBox.cpp
		${NPCVGUI_DIR}/src/widgets/ImageInspectorBox.cpp
		${NPCVGUI_DIR}/src/widgets/WinMatrixFilter.cpp
)

SOURCE_GROUP("Source Files\\widgets" FILES ${widgets_src})

SET (npcvGui_srcs
	${npcvGui_headers}
	${widgets_headers}
	${npcvGui_src}
	${widgets_src}
)

#
# Add gui executable
#
add_executable(npcvGui ${npcvGui_srcs})


#include npcvGui
include_directories(npcvGui ${NPCVGUI_DIR}/include)

#
# add SFML
#
target_link_libraries(npcvGui ${SFML_DIR}/lib/sfml-graphics-d.lib)
target_link_libraries(npcvGui ${SFML_DIR}/lib/sfml-window-d.lib)
target_link_libraries(npcvGui ${SFML_DIR}/lib/sfml-system-d.lib)
include_directories(npcvGui ${SFML_DIR}/include)

#
# add SFGUI
#
include_directories(npcvGui ${SFGUI_DIR}/include)
target_link_libraries(npcvGui ${SFGUI_DIR}/lib/sfgui-d.lib)

#
# add NPCV
#
include_directories(npcvGui ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(npcvGui ${PROJECT_NAME})

