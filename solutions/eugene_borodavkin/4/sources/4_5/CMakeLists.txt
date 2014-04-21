find_package( Boost 1.41 ${SEARCH_PARAMETERS} COMPONENTS
    system
    thread
    date_time
)

compile_project( ${module_name} "*.cpp" "*.h" STATIC libraries Boost)

