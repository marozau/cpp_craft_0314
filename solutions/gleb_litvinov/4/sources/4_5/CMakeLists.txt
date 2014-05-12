find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
 system
 unit_test_framework
 filesystem
 thread
 date_time
)


compile_project( ${module_name} "*.cpp" "*.h" STATIC libraries Boost)

