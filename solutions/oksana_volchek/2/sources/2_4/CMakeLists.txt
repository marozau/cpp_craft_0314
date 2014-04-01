find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	system
)

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries binary_reader Boost )

