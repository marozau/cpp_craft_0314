find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	system
	date_time
	chrono
	thread
)
compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries  binary_reader Boost)
