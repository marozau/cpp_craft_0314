find_package( Boost 1.41 ${SEARCH_PARAMETERS} COMPONENTS
	filesystem
	date_time
	thread
	date_time
	chrono
	system
)

find_package( system_utilities ${SEARCH_PARAMETERS} COMPONENTS
	logger
	ts_logger
	file_logger
	limited_file_logger
) 

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries system_utilities Boost ) 