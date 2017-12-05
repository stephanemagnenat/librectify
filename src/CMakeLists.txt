set(SRCS librectify.cpp)
if (APPLE)
	add_library(rectify MODULE ${SRCS})
	set_target_properties(rectify PROPERTIES BUNDLE TRUE)
else ()
	add_library(rectify SHARED ${SRCS})
endif ()

if (LINUX)
	message(STATUS "Linux detected, performing link-time optimisation")
	set_target_properties(rectify PROPERTIES LINK_FLAGS "-Wl,--exclude-libs,ALL -Wl,--gc-sections -Wl")
endif()

target_link_libraries(rectify ${OpenCV_LIBS})

