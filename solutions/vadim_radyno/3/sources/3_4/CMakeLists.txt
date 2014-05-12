find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	system
	unit_test_framework
	filesystem
	thread
	chrono
	date_time
)
compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries binary_reader Boost )

