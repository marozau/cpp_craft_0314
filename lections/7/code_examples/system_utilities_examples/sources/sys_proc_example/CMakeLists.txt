find_package( Boost 1.41 ${SEARCH_PARAMETERS} COMPONENTS
	filesystem
	regex
	program_options
	system
	date_time
	thread
	chrono
)

find_package( system_utilities ${SEARCH_PARAMETERS} COMPONENTS
	logger
	file_logger
	system_processor
	property_reader
) 

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries system_utilities Boost ) 