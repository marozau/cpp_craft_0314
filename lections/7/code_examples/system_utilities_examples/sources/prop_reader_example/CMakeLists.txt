find_package( Boost 1.41 ${SEARCH_PARAMETERS} COMPONENTS
	filesystem
	regex
	system
)

find_package( system_utilities ${SEARCH_PARAMETERS} COMPONENTS
	property_reader
) 

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries system_utilities Boost ) 