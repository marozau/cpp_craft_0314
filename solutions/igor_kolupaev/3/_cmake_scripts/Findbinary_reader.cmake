include( utils )

if (binary_reader_ROOT)
	set(binary_reader_root ${binary_reader_ROOT} )
elseif(NOT "$ENV{BINARY_READER_ROOT}" STREQUAL "")
	set(binary_reader_root $ENV{BINARY_READER_ROOT} )
else()
	message(FATAL_ERROR "[ERROR]: No BINARY_READER_ROOT environment variable found")
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
	set(CMAKE_BUILD_TYPE Debug)
	if (!binary_reader_FIND_QUIETLY)
		message(STATUS "CMAKE_BUILD_TYPE was not tuned, so we install there 'Debug'")
	endif()
else()
endif()

if (binary_reader_DEBUG)
	message(STATUS "We going to look into '${binary_reader_root}' (BINARY_READER_ROOT environment variable) folder.")
	create_string_from_list( component_list ${binary_reader_FIND_COMPONENTS} )
	message(STATUS "We are looking for: '" ${component_list} "' components.")
endif(binary_reader_DEBUG)

set(binary_reader_FOUND FALSE)
set(binary_reader_INCLUDE_DIRS "")
set(binary_reader_LIBRARIES "")

if (UNIX)
	set(binary_search_folder ${binary_reader_root}/_build_${CMAKE_BUILD_TYPE}_${CMAKE_ADDRESS_MODEL}/bin_${CMAKE_ADDRESS_MODEL}/${CMAKE_BUILD_TYPE})
else(UNIX)
	set(binary_search_folder ${binary_reader_root}/_build_${CMAKE_BUILD_TYPE}_${CMAKE_ADDRESS_MODEL}/bin_${CMAKE_ADDRESS_MODEL}/${CMAKE_BUILD_TYPE})
endif(UNIX)
if (NOT binary_reader_FIND_QUIETLY)
	message(STATUS "Looking for libraries at " ${binary_search_folder})
endif()

if (binary_reader_DEBUG)
	message(STATUS "Binary search folder: " ${binary_search_folder} )
endif(binary_reader_DEBUG)

set(components binary_reader)

foreach(component ${binary_reader_FIND_COMPONENTS})

list_contains(we_should_find_${component} ${component} ${components})
if(we_should_find_${component})

	if (binary_reader_DEBUG)
		message(STATUS "Searching for ${component} library. ")
	endif()
	set(binary_reader_${component}_FOUND FALSE)
	set(binary_reader_${component}_INCLUDE_DIRS NOTFOUND)
	set(binary_reader_${component}_LIBRARIES NOTFOUND)

	find_path( binary_reader_${component}_INCLUDE_DIR
			NAMES "CMakeLists.txt"
			HINTS "${binary_reader_root}/sources/${component}/")
	set(binary_reader_${component}_INCLUDE_DIRS ${binary_reader_${component}_INCLUDE_DIR})

	find_library( binary_reader_${component}_LIBRARY
		NAMES "${component}" 
		HINTS ${binary_search_folder} )
	set(binary_reader_${component}_LIBRARIES ${binary_reader_${component}_LIBRARY})

	if(NOT binary_reader_FIND_QUIETLY)
		message(STATUS "binary_reader ${component} component: ")
		create_string_from_list(headers ${binary_reader_${component}_INCLUDE_DIRS})
		message(STATUS "   headers  :  " ${headers})
		create_string_from_list(libraries ${binary_reader_${component}_LIBRARIES})
		message(STATUS "   libraries:  " ${libraries})
	endif()	

	if(NOT binary_reader_${component}_INCLUDE_DIR OR NOT binary_reader_${component}_LIBRARY)
		message(FATAL_ERROR " We can't find binary_reader ${component} component")
	else()
		set(binary_reader_INCLUDE_DIRS ${binary_reader_INCLUDE_DIRS} ${binary_reader_${component}_INCLUDE_DIRS})
		set(binary_reader_LIBRARIES ${binary_reader_LIBRARIES} ${binary_reader_${component}_LIBRARIES})
	endif()
else()
	message(FATAL_ERROR "Unknown component: ${component}")
endif(we_should_find_${component})

endforeach( component )


if (binary_reader_DEBUG)
	create_string_from_list(headers ${binary_reader_INCLUDE_DIRS})
	message(STATUS "binary_reader_INCLUDE_DIRS: " ${headers})
	create_string_from_list(libraries ${binary_reader_LIBRARIES})
	message(STATUS "binary_reader_LIBRARIES: " ${libraries})
endif(binary_reader_DEBUG)

