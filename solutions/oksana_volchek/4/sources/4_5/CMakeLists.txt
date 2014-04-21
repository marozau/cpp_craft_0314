find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	system
	thread
)

link_directories(${Boost_LIBRARY_DIRS})

compile_project( ${module_name} "*.cpp" "*.h" STATIC libraries Boost)

