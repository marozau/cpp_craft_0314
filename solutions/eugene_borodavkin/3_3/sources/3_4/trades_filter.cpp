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

void inscreadeWorkingThreads(){
    boost::mutex::scoped_lock lock(workThrMutex);
    ++working_threads;
}

void decreaseWorkingThreads(){
    boost::mutex::scoped_lock lock(workThrMutex);
    --working_threads;
}

int handleFile(const int fileNum){
    char inFileName[256];
    char outFileName[256];
    std::sprintf(inFileName, "input_%d.txt",fileNum);
    std::sprintf(outFileName, "output_%d.txt",fileNum);
    std::ifstream input(inFileName, std::ios::binary);
    if ( !input.is_open() )
    {
        decreaseWorkingThreads();
        amount_cond.notify_one();
        return 0;
    }
    std::ofstream output(outFileName, std::ios::binary);
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
    for(it = list.begin(); it != list.end(); it++){
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
            while(working_threads >= THREADS_COUNT){
                amount_cond.wait(mut);
            }
        }
        if(working_threads < THREADS_COUNT){
            threads.create_thread( boost::bind(&handleFile, i));
            inscreadeWorkingThreads();
        }

    }
    threads.join_all();
    return 0;
}

