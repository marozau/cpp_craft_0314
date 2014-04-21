find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	system
	unit_test_framework
)

compile_project( ${tests_name} "*.cpp" "*.h" BINARY tests ${module_name} Boost )
register_test( ${tests_name} 1 0.5 )

