cmake_minimum_required(VERSION 2.8)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set( CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "Configurations" FORCE )
project( ${SOLUTION_NAME} )
include( environment.cmake required )

modules( trade_message quote_message udp_listener market_data_processor multicast_communication minute_calculator minute_market_data )
binaries( multicast_communication_application minute_market_data_application )

compile()
