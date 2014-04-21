find_package( Boost ${SEARCH_PARAMETERS} REQUIRED COMPONENTS
	system
	thread
	regex
	filesystem
)

link_directories(${Boost_LIBRARY_DIRS})

find_package( binary_reader ${SEARCH_PARAMETERS} COMPONENTS
	binary_reader
)

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries Boost binary_reader )
