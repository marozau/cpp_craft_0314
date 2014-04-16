#include <iostream>

#include <system_processor.h>
#include <boost/thread.hpp>

class mediator
{
	static const size_t thread_count_ = 2;
	boost::thread_group tg;
public:
	explicit mediator()
	{
		for (size_t i = 0; i < thread_count_; ++i)
			tg.add_thread( new boost::thread( &mediator::do_some_job_, this ) );
	}
	void stop()
	{
		// correct stop

		tg.join_all();
	}
private:
	void do_some_job_()
	{
		// something doing
	}
};

int main(int argc, char* argv[])
{
	using namespace system_utilities::common;
	system_processor::sp sp_ptr = system_processor::init(argc, argv, SOURCE_DIR "/configs/system_processor.ini");
	//
	mediator m;
	sp_ptr->wait_for_stop();
	m.stop();

	return 0;
}