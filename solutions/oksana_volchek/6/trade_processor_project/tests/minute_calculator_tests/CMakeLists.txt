find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	system
	unit_test_framework
	filesystem
)

link_directories(${Boost_LIBRARY_DIRS})

compile_project( ${tests_name} "*.cpp" "*.h" BINARY tests ${module_name} Boost )
register_test( ${tests_name} 5 4 )

