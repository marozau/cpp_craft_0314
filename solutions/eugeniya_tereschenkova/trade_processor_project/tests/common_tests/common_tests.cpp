#include <vector>
#include <string>
#include <set>

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "test_registrator.h"

#include "trade_message.h"
#include "quote_message.h"

#include "thread_safe_queue.h"

namespace common
{
    namespace tests_
	{ 
		static const int queue_size = 10000;
        void push_thread(thread_safe_queue<long long int>& q, long long int j)
        {
            long long int start = queue_size * j;
            for(long long int i = start; i < start + queue_size; ++i)
            {
                q.push(i);
            }
        }
        void pop_thread(thread_safe_queue<long long int>& q)
        {
            for(int i = 0; i < queue_size; ++i)
            {
                long long int a;
                q.wait_and_pop(a);
            }
        }
        void common_tests()
        {
            {
                thread_safe_queue<long long int> q;
                q.push(1L);
                BOOST_CHECK_EQUAL(1, q.size());
            }

            {
                thread_safe_queue<long long int> q;
                q.push(1L);
                q.push(2L);
                q.push(3L);
                long long int a;
                q.pop(a);
                BOOST_CHECK_EQUAL(2, q.size());
            }
            {
                thread_safe_queue<long long int> q;
				boost::thread_group t_group;
				static const int thread_count = 100;
                for(long long int i = 0; i < thread_count; ++i)
                {
                    t_group.create_thread(boost::bind(&push_thread, boost::ref(q), i));
                    t_group.create_thread(boost::bind(&pop_thread, boost::ref(q)));
                }
                t_group.join_all();
                BOOST_CHECK_EQUAL(0, q.size());
            }
        }
    }
}
