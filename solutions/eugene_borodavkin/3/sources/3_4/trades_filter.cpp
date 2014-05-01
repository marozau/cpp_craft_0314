#include <iostream>
#include <algorithm>
#include <cstdint>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <list>
#include <stdio.h>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include "message.h"
const int MAX_FILE_NUMBER_SIZE = 4;
const int THREADS_COUNT = 4;
const int FILES_NUM = 1000;
volatile int working_threads = 0;
boost::condition amount_cond;
boost::mutex workThrMutex;

typedef std::list< Message > msgList;

bool message_compare(const Message &msg1, const Message &msg2)
{
    return msg1.get_time() < msg2.get_time();
}

void increaseWorkingThreads(){
    boost::mutex::scoped_lock lock(workThrMutex);
    ++working_threads;
}

void decreaseWorkingThreads(){
    boost::mutex::scoped_lock lock(workThrMutex);
    --working_threads;
}

int getWorkingThreads() {
    boost::mutex::scoped_lock lock(workThrMutex);
    return working_threads;
}

int handleFile(const int fileNum){
    char file_number[ MAX_FILE_NUMBER_SIZE ];
    std::sprintf( file_number, "%03d", fileNum );
    std::string fileNumberString( file_number );
    std::ifstream input(BINARY_DIR"/input_" + fileNumberString + ".txt", std::ios::binary );
    if ( !input.is_open() )
    {
        decreaseWorkingThreads();
        amount_cond.notify_one();
        return 0;
    }
    std::ofstream output(BINARY_DIR"/output_" + fileNumberString + ".txt", std::ios::binary);
    msgList list;
    boost::uint32_t max_time=0;
    while(!input.eof()){
        Message msg;
        if(msg.read(input) == Message::READ_ERROR){
            if(input.eof())
                break;
            amount_cond.notify_one();
            return 1;
        }
        if(max_time < msg.get_time()){
            max_time = msg.get_time();
        }
        if(msg.check_correct(max_time) == Message::OK)
            list.push_back(msg);
    }
    list.sort(message_compare);
    msgList::const_iterator it;
    for(it = list.begin(); it != list.end(); ++it){
        it->write(output);
    }
    decreaseWorkingThreads();
    amount_cond.notify_one();
    return 0;
}

int main()
{
    boost::thread_group threads;
    boost::mutex mut;
    for(int i = 1; i < FILES_NUM; ++i){
        {
            boost::mutex::scoped_lock lock(mut);
            while(getWorkingThreads() >= THREADS_COUNT){
                amount_cond.wait( lock );
            }
        }

        if(getWorkingThreads() < THREADS_COUNT){
            threads.create_thread( boost::bind(&handleFile, i));
            increaseWorkingThreads();
        }

    }
    threads.join_all();
    return 0;
}

