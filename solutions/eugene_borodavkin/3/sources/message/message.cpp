#include "message.h"

Message::Message(): time(0), type(0), len(0), msg(NULL) {}

Message::Message(const Message& msg):time(msg.time), type(msg.type), len(msg.len),msg(NULL){
    if(this->len != 0){
        this->msg = new char[this->len +1];
        strcpy(this->msg, msg.msg);
    }
}
Message& Message::operator=(const Message &other){
    if(this != &other){
        Message(other).swap(*this);

    }
    return *this;

}

void Message::swap(Message &msg) throw(){
    std::swap(this->len, msg.len);
    std::swap(this->msg, msg.msg);
    std::swap(this->time, msg.time);
    std::swap(this->type, msg.type);
}

Message::~Message(){
    if(msg != NULL){
        delete  [] msg;
        msg = NULL;
    }
}

Message::ErrorList Message::read(std::ifstream &input){
    if( !input.read(reinterpret_cast< char* >( &type ), sizeof(type))) return READ_ERROR;
    if( !input.read(reinterpret_cast< char* >( &time ), sizeof(time))) return READ_ERROR;
    if( !input.read(reinterpret_cast< char*>( &len ), sizeof(len))) return READ_ERROR;
    if(msg != NULL )
        delete [] msg;
    msg = new char[len + 1];
    if( !input.read(msg,len)) return READ_ERROR;
    msg[len] = '\0';
    return OK;
}
std::uint32_t Message::get_time() const{
    return time;
}

Message::ErrorList Message::check_correct(const std::uint32_t time) const{
    if(this->time + MAX_TIME_DELAY <= time ) return INVALID_MESSAGE;
    if(type < MIN_TYPE_ELEMENT || type > MAX_TYPE_ELEMENT) return INVALID_MESSAGE;
    return OK;
}

void Message::write(std::ofstream & output) const{
    output.write(reinterpret_cast< const char* >( &type ), sizeof(type));
    output.write(reinterpret_cast< const char* >( &time ), sizeof(time));
    output.write(reinterpret_cast< const char*>( &len ), sizeof(len));
    output.write(msg, len);
}

std::uint32_t Message::getType() const{
    return type;
}

std::uint32_t Message::getSize() const{
    return sizeof(type) + sizeof(time) + sizeof(len) + len;
}
