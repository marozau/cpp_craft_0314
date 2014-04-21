find_package( Boost ${SEARCH_PARAMETERS} REQUIRED COMPONENTS
	system
)

compile_project( ${module_name} "*.cpp" "*.h" STATIC libraries Boost)