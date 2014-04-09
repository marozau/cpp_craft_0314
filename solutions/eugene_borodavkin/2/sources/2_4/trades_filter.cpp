#include <iostream>
#include <algorithm>
#include <stdint.h>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <list>


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
            delete  [] msg;
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

    ErrorList check_correct(std::uint32_t time) const{
        if(this->time + 2 <= time ) return INVALID_MESSAGE;
        if(type < 1 || type > 4) return INVALID_MESSAGE;
        return OK;
    }

    void write(std::ofstream & output) const{
        output.write((char*)&type, sizeof(type));
        output.write((char*)&time, sizeof(time));
        output.write((char*)&len, sizeof(len));
        output.write(msg, len);
    }

};

bool message_compare(const Message &msg1, const Message &msg2)
{
    return msg1.get_time() < msg2.get_time();
}

int main()
{
    std::ifstream input(BINARY_DIR"/input.txt", std::ios::binary);
    std::ofstream output(BINARY_DIR"/output.txt",std::ios::binary);
    std::list<Message> list;
    std::uint32_t max_time=0;
    while(!input.eof()){
        Message msg;
        if(msg.read(input) == Message::READ_ERROR){
            if(input.eof())
                break;
            return 1;
        }
        if(max_time < msg.get_time()){
            max_time = msg.get_time();
        }
        if(msg.check_correct(max_time) == Message::OK)
            list.push_back(msg);
    }
    list.sort(message_compare);
    std::list<Message>::iterator it;
    for(it = list.begin(); it != list.end(); it++){
        (*it).write(output);
    }


    return 0;
}

