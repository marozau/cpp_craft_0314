
find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	system
	thread
#	date_time
#	chrono
)

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries Boost binary_reader small_buffer th_small_buffer )

