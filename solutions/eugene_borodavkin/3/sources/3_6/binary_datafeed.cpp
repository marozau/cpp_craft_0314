#include <iostream>
#include <algorithm>
#include <cstdint>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <queue>
#include <list>
#include <boost/thread.hpp>
#include "short_message.h"
#include <boost/lexical_cast.hpp>



std::queue<Message> msgQueue;
boost::mutex queueMutex;
boost::thread_group threads;
const int THREADS_COUNT = 2;


class IO_Sync{
    mutable boost::mutex io_mut_;
    std::ofstream *out_;
public:
    IO_Sync(std::string &outFile){
        out_ = new std::ofstream(outFile, std::ios::binary);
    }

    void write(Message &msg)  {
        boost::mutex::scoped_lock lock(io_mut_);
        msg.write(*out_);
    }
    ~IO_Sync(){
        out_->flush();
        out_->close();
        delete out_;
    }
};

struct cmp_str
{
   bool operator()(char const *a, char const *b)
   {
      return std::strcmp(a, b) < 0;
   }
};


class SyncClass{
    std::map<const char*, IO_Sync*, cmp_str> sync_map_ ;
    bool working_;
    boost::mutex map_mutex_;
    boost::condition_variable wait_condition_;
public:
    SyncClass():working_(true){

    }

    void writeMessage(){
        while( working_ ){
            Message msg;
            queueMutex.lock();
            if( msgQueue.empty( ) ){
                queueMutex.unlock();
                wait_condition_.notify_one();

                continue;

            }
            msg = msgQueue.front();
            msgQueue.pop();
            queueMutex.unlock();
            IO_Sync *info;
            {
                boost::mutex::scoped_lock lock(map_mutex_);
                if(sync_map_.find( msg.name() ) == sync_map_.end() ){
                    std::string outFileName;
                    char *name = new char[ 8]();

                    strncpy( name,msg.name(),sizeof(msg.name() ) );
                   // memcpy( name, msg.name(), sizeof( msg.name() ) );
                    outFileName = BINARY_DIR"/output_" + boost::lexical_cast< std::string >( name ) + ".txt";
                    sync_map_[name] = new IO_Sync(outFileName);
                }
                info = sync_map_[msg.name()];
            }

            info->write(msg);
        }
    }

    void stopWorking(){
        wait( );
        working_ = false;
    }

    ~SyncClass(){
        for(auto item : sync_map_){
            delete [] (item).first;
            delete (item).second;
        }
        wait();
    }
private:
    void wait( ) {
        boost::mutex::scoped_lock lock ( queueMutex );
        while( !msgQueue.empty( ) ){
            wait_condition_.wait( lock );
        }
    }
};




int main()
{
    std::ifstream input(BINARY_DIR"/input.txt", std::ios::binary);
    SyncClass sc;
    for(int i = 0;i < THREADS_COUNT; i++)
        threads.create_thread(boost::bind(&SyncClass::writeMessage, &sc) );

    while(!input.eof()){
        Message msg(input);
        if(input.eof())
            break;
        boost::mutex::scoped_lock lock(queueMutex);
        msgQueue.push(msg);
    }
    sc.stopWorking();
    threads.join_all();

    return 0;
}

