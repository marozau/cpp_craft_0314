#include <iostream>
#include <algorithm>
#include <cstdint>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <queue>
#include <list>
#include <boost/thread.hpp>


template <class T>
void readFromBinaryInput(std::ifstream &input, T &t, size_t len = sizeof(T)){
    input.read(reinterpret_cast< char * >( &t ), len);
}

template <class T>
void writeToBinaryOutput( std::ofstream &output, T &t, size_t len = sizeof(T)){
    output.write(reinterpret_cast< char* >( &t ), len);
}

class Message{
private:
    char stock_name[8];
    char date_time[8];
    double price;
    double vwap;
    boost::uint32_t volume;
    double f1;
    double t1;
    double f2;
    double f3;
    double f4;
public:
    Message(){}
    Message( std::ifstream &in){
        readFromBinaryInput(in, stock_name);
        readFromBinaryInput(in, date_time);
        readFromBinaryInput(in, price);
        readFromBinaryInput(in, vwap);
        readFromBinaryInput(in, volume);
        readFromBinaryInput(in, f1);
        readFromBinaryInput(in, t1);
        readFromBinaryInput(in, f2);
        readFromBinaryInput(in, f3);
        readFromBinaryInput(in, f4);
    }
    ~Message(){
    }

    void write( std::ofstream& out )
    {
        boost::uint32_t date = 0;
        int year,day,month;
        std::sscanf( date_time, "%4d%2d%2d", &year, &month, &day );
        date = ( year - 1 ) * 372 +  ( month  - 1 )* 31 + day;

        char stock[9];
        memcpy( stock, stock_name, sizeof( stock_name ) );
        writeToBinaryOutput( out, stock );
        writeToBinaryOutput( out, date );
        writeToBinaryOutput( out, vwap );
        writeToBinaryOutput( out, volume );
        writeToBinaryOutput( out, f2 );
    }

    char* name(){
        return stock_name;
    }
};

std::queue<Message> msgQueue;
boost::mutex queueMutex;
boost::thread_group threads;
const int THREADS_COUNT = 4;


class IO_Sync{
    mutable boost::mutex io_mut_;
    std::ofstream *out_;
public:
    IO_Sync(char * outFile){
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
public:
    SyncClass():working_(true){

    }

    void writeMessage(){
        bool doWork = true;
        while( doWork ){
            Message msg;
            queueMutex.lock();
            if(msgQueue.empty()) continue;
            msg = msgQueue.front();
            msgQueue.pop();
            doWork = working_ || !msgQueue.empty();
            queueMutex.unlock();
            IO_Sync *info;
            {
                boost::mutex::scoped_lock lock(map_mutex_);
                if(sync_map_.find(msg.name()) == sync_map_.end()){
                    char outFileName[256];
                    char *name = new char[8];
                    memcpy( name, msg.name(), sizeof( msg.name() ) );
                    std::sprintf(outFileName, BINARY_DIR"/output_%s.txt",msg.name());
                    sync_map_[name] = new IO_Sync(outFileName);
                }
                info = sync_map_[msg.name()];
            }
            info->write(msg);
        }
    }

    void stopWorking(){
        working_ = false;
    }

    ~SyncClass(){
        for(auto item : sync_map_){
            delete [] (item).first;
            delete (item).second;
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
        boost::mutex::scoped_lock lock(queueMutex);
        msgQueue.push(msg);
    }
    sc.stopWorking();
    threads.join_all();

    return 0;
}

