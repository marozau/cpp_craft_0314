find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	system
	thread
)

compile_project( ${module_name} "*.cpp" "*.h" STATIC libraries Boost )