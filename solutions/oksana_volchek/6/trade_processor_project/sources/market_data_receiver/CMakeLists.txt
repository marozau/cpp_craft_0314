
find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	system
	thread
	date_time
	chrono
)

link_directories(${Boost_LIBRARY_DIRS})

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries multicast_communication minute_calculator Boost )

