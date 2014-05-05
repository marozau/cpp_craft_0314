#ifndef _TASK4_4_MESSAGE_H_
#define _TASK4_4_MESSAGE_H_

#include <string>
#include <istream>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace task4_4
{
	class message;

	typedef boost::shared_ptr< message > message_ptr;

	class message : virtual protected boost::noncopyable
	{
	protected:
		explicit message();

	public:
		virtual ~message();
		virtual const char type() const = 0;
		virtual const std::string str() const = 0;
	};
}

#endif // _TASK4_4_MESSAGE_H_
