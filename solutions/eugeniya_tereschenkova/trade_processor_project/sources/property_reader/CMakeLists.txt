find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
    system
    thread
    date_time
    regex
    chrono
)

compile_project( ${module_name} "*.cpp" "*.h" STATIC libraries Boost )

