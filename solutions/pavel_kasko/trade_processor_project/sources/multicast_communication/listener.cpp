#include "listener.h"
#include <boost\bind.hpp>

namespace multicast_communication
{
	const size_t listener::default_buffer_size = 16ul;

	listener::listener(std::string ip, unsigned short port, message_type type) :
		ip(ip), port(port), type(type), socket_(io_service_), listen_endpoint_(boost::asio::ip::address::from_string("0.0.0.0"), port)
	{}

	void listener::Start()
	{
		socket_reload();
		register_listener();
		io_service_.run();
	}

	void listener::Stop()
	{
		io_service_.stop();
	}

	void listener::socket_reload()
	{
		using boost::asio::ip::udp;
		using boost::asio::ip::address;
		using boost::asio::ip::multicast::join_group;

		socket_.open(listen_endpoint_.protocol());
		socket_.set_option(udp::socket::reuse_address(true));
		socket_.bind(listen_endpoint_);
		socket_.set_option(join_group(address::from_string(ip)));
	}

	void listener::register_listener(buffer_type pre_buffer, const size_t previous_size)
	{
		buffer_type buffer;

		if (pre_buffer)
			buffer = pre_buffer;
		else
			buffer.reset(new std::string(default_buffer_size, '\0'));

		char* const buffer_start = &(*buffer->begin());

		using namespace boost::asio::placeholders;
		socket_.async_receive(boost::asio::buffer(buffer_start, previous_size + default_buffer_size),
			boost::bind(&listener::listen_handler_, this, buffer, error, bytes_transferred));
	}

	void listener::listen_handler_(buffer_type bt, const boost::system::error_code& error, const size_t bytes_received)
	{
		if (error)
		{
			static const int NO_ENOUGHT_BUFFER = 234;
			if (error.value() == NO_ENOUGHT_BUFFER)
			{
				enlarge_buffer_(bt);
				register_listener(bt, bytes_received);
			}
			return;
		}
		if (bytes_received == bt->size() && (*bt)[bytes_received - 1] != '\0')
		{
			enlarge_buffer_(bt);
			register_listener(bt, bytes_received);
		}
		else
		{
			register_listener();
		}

		Raise(*bt, type);

		//_aggregator.SaveOne(*bt, type);
		//std::cout << *bt << std::endl;
	}

	void listener::enlarge_buffer_(buffer_type& bt)
	{
		bt->resize(bt->size() + default_buffer_size);
	}

	void listener::AddHandler(boost::function<void(std::string, message_type)> handler)
	{
		Raise.connect(handler);
	}
}