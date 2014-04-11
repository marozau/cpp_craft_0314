find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	system
)

compile_project( ${module_name} "*.cpp" "*.h" STATIC libraries Boost binary_reader trade_filter )

