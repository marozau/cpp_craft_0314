find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
    thread
	system
	unit_test_framework
	filesystem
    regex
	date_time
	chrono
)

compile_project( ${tests_name} "*.cpp" "*.h" BINARY tests ${module_name} Boost )
register_test( ${tests_name} 5 4 )

