#include <iostream>
#include <algorithm>
#include <stdint.h>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include "message.h"

const int THREADS_COUNT = 4;
const int FILES_NUM = 10;
volatile int working_threads = 0;
boost::condition amount_cond;
boost::mutex workThrMutex;
typedef std::unordered_map<std::uint32_t, std::uint32_t> map;
typedef std::unordered_set<std::uint32_t> set;

const boost::uint32_t MAX_BUFFER_SIZE = 2048;

void inscreadeWorkingThreads(){
    boost::mutex::scoped_lock lock(workThrMutex);
    ++working_threads;
}

void decreaseWorkingThreads(){
    boost::mutex::scoped_lock lock(workThrMutex);
    --working_threads;
}


void increaseTimesMessageUsed(map& times, const set& curTime){
    for(auto msgType: curTime){
        times[ msgType ] ++;
    }
}

void handleFile(int fileNum){

    char inFileName[256];
    char outFileName[256];
    std::sprintf(inFileName, BINARY_DIR"/input_%d.txt",fileNum);
    std::sprintf(outFileName, BINARY_DIR"/output_%d.txt",fileNum);

    std::ifstream input(inFileName, std::ios::binary);
    if( !input.is_open() ){
        decreaseWorkingThreads();
        amount_cond.notify_one();
        return;
    }
    boost::uint32_t curTime=0;

    map sizeForMsgType;//msg type , size
    map allMsgType;//msg type, count of this type msg
    map timesMsgType;//msg type, how many was msg in diff time?
    set msgTypeInCurTime;

    while(!input.eof()){
        Message msg;
        if(msg.read(input) == Message::READ_ERROR){
            if(input.eof()){
                increaseTimesMessageUsed(timesMsgType, msgTypeInCurTime);
                break;
            }
            decreaseWorkingThreads();
            amount_cond.notify_one();
            return ;
        }

        if(curTime < msg.get_time()){
            curTime = msg.get_time();
            increaseTimesMessageUsed(timesMsgType, msgTypeInCurTime);
            msgTypeInCurTime.clear();
            sizeForMsgType.clear();
        }
        msgTypeInCurTime.insert(msg.getType());
        if(sizeForMsgType[msg.getType()] + msg.getSize() <= MAX_BUFFER_SIZE){
            sizeForMsgType[msg.getType()] += msg.getSize();
            allMsgType[msg.getType()]++;
        }
    }
    input.close();

    std::ofstream output(outFileName, std::ios::binary);

    for(auto msgType : allMsgType){
        output.write((char*)&msgType.first, sizeof(msgType.first));
        const double result = static_cast<double> (msgType.second) / timesMsgType[msgType.first];
        output.write((char*)&result,sizeof(result));
    }
    decreaseWorkingThreads();
    amount_cond.notify_one();
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


