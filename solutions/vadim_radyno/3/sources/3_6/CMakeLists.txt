find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	system
	filesystem
	thread
	chrono
	date_time
)
compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries binary_reader Boost)


