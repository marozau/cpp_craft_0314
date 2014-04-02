find_package( Boost 1.55 ${SEARCH_PARAMETERS} COMPONENTS

		system

		)


compile_project( ${module_name} "*.cpp" "*.h" STATIC libraries Boost)

