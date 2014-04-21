find_package( Boost 1.54 ${SEARCH_PARAMETERS} COMPONENTS
	thread
	date_time
	system
	chrono
)

find_package( system_utilities ${SEARCH_PARAMETERS} COMPONENTS
	ts_queue
)

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries system_utilities Boost )
