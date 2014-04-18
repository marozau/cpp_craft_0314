#include <iostream>

#include <property_reader.h>

int main()
{
	system_utilities::common::property_reader pr(SOURCE_DIR "/configs/property_reader.ini");
	const std::string multicast_address = pr.get_value("multicast_addr");
	const unsigned int port = pr.get_value<unsigned int>("port", 1234);
	const std::string missing_string = pr.get_value("missing_string", "default value of missing string");

	//
	std::cout << "multicast_address: " << multicast_address << "\n";
	std::cout << "port: " << port << "\n";
	std::cout << "missing_string: " << missing_string << "\n";
}