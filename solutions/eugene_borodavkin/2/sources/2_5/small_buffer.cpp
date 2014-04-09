#include <iostream>
#include <algorithm>
#include <stdint.h>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <list>
#include <unordered_map>
#include <unordered_set>


const std::uint32_t MAX_BUFFER_SIZE = 2048;

class Message{
private:
    std::uint32_t time;
    std::uint32_t type;
    std::uint32_t len;
    char * msg;
public:
    enum ErrorList{
        OK,
        READ_ERROR,
        INVALID_MESSAGE
    };


    Message(): time(0), type(0), len(0), msg(NULL) {}
    Message(const Message& msg):time(msg.time), type(msg.type), len(msg.len),msg(NULL){
        if(this->len != 0){
            this->msg = new char[this->len +1];
            strcpy(this->msg, msg.msg);
        }
    }
    Message& operator=(const Message &other){
        if(this != &other){
            Message(other).swap(*this);

        }
        return *this;

    }

    void swap(Message &msg) throw(){
        std::swap(this->len, msg.len);
        std::swap(this->msg, msg.msg);
        std::swap(this->time, msg.time);
        std::swap(this->type, msg.type);
    }

    ~Message(){
        if(msg != NULL){
            delete [] msg;
            msg = NULL;
        }
    }

    ErrorList read(std::ifstream &input){
        if( !input.read((char*)&type, sizeof(type))) return READ_ERROR;
        if( !input.read((char*)&time, sizeof(time))) return READ_ERROR;
        if( !input.read((char*)&len, sizeof(len))) return READ_ERROR;
        msg = new char[len + 1];
        if( !input.read(msg,len)) return READ_ERROR;
        msg[len] = '\0';
        return OK;
    }
    std::uint32_t get_time() const{
        return time;
    }

    std::uint32_t getType() const{
        return type;
    }

    std::uint32_t getSize() const{
        return sizeof(type) + sizeof(time) + sizeof(len) + len;
    }

    void write(std::ofstream & output) const{
        output.write((char*)&type, sizeof(type));
        output.write((char*)&time, sizeof(time));
        output.write((char*)&len, sizeof(len));
        output.write(msg, len);
    }

};


int main()
{
    std::ifstream input(BINARY_DIR"/input.txt", std::ios::binary);
    std::uint32_t curTime=0;

    std::unordered_map< std::uint32_t, std::uint32_t> sizeForMsgType;//msg type , size
    std::unordered_map< std::uint32_t, std::uint32_t> allMsgType;//msg type, count of this type msg
    std::unordered_map< std::uint32_t, std::uint32_t> timesMsgType;//msg type, how many was msg in diff time?
    std::unordered_set< std::uint32_t > msgTypeInCurTime;



    while(!input.eof()){
        Message msg;
        if(msg.read(input) == Message::READ_ERROR){
            if(input.eof()){
                for(auto msgType : msgTypeInCurTime){
                    timesMsgType[msgType]++;
                }
                break;
            }
            return 1;
        }

        if(curTime < msg.get_time()){
            curTime = msg.get_time();
            for(auto msgType : msgTypeInCurTime){
                timesMsgType[msgType]++;
            }
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
    std::ofstream output(BINARY_DIR"/output.txt",std::ios::binary);

    for(auto msgType : allMsgType){
        output.write((char*)&msgType.first, sizeof(msgType.first));
        double result = static_cast<double> (msgType.second) / timesMsgType[msgType.first];
        output.write((char*)&result,sizeof(result));
    }


    return 0;
}


