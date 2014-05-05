find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	system
	thread
	chrono
	date_time
	filesystem
)   

compile_project( ${module_name} "*.cpp" "*.h" STATIC libraries Boost )

