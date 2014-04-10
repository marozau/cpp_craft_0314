
find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	system
	thread
#	date_time
#	chrono
)

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries Boost binary_reader trade_filter th_trade_filter )

