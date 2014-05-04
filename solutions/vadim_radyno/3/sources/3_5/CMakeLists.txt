find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	filesystem
	system
	thread
	chrono
	date_time
)
compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries binary_reader Boost )

