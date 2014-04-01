find_package( Boost 1.41 ${SEARCH_PARAMETERS} COMPONENTS
	chrono
	date_time
	system
	thread
)

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries binary_reader binary_writer Boost )

