#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include <vector>
using namespace std;

namespace config
{ 
    class reader
    {
		typedef pair<string, unsigned short> addr_port_;
		typedef vector<addr_port_> cont_addr_port_;
	private:
		bool opened_;
		size_t trade_thread_size_;
		size_t quote_thread_size_;
		size_t trade_ports_amount_;
		size_t quote_ports_amount_; 
		cont_addr_port_ trades_;
		cont_addr_port_ quotes_; 

		void parse_(ifstream&, cont_addr_port_&, size_t&);
	public:
		explicit reader(const string&);
		const bool opened() const;
        const size_t trade_thread_size() const;
        const size_t quote_thread_size() const;
		const size_t trade_ports_amount() const;
		const size_t quote_ports_amount() const;
        const cont_addr_port_& trades() const;
        const cont_addr_port_& quotes() const;
    };
}
#endif // _PROPERTY_H_
