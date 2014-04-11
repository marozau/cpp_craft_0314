find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	thread
	regex
	date_time
	chrono
	system
)

compile_project( ${module_name} "*.cpp" "*.h" STATIC libraries Boost)

