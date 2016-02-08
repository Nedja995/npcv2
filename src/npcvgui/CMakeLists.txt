FILE (GLOB_RECURSE npcvgui_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)


add_executable(npcgui ${npcvgui_SRCS})

include_directories(npcgui ${CMAKE_SOURCE_DIR}/include)
include_directories(npcgui ${SFML_DIR}/include)
include_directories(npcgui ${SFGUI_DIR}/include)


target_link_libraries(npcgui ${SFML_DIR}/lib/sfml-graphics-d.lib)
target_link_libraries(npcgui ${SFML_DIR}/lib/sfml-window-d.lib)
target_link_libraries(npcgui ${SFML_DIR}/lib/sfml-system-d.lib)

target_link_libraries(npcgui ${SFGUI_DIR}/lib/sfgui-d.lib)

target_link_libraries(npcgui ${PROJECT_NAME})