#ifndef _MESSAGE_MESSAGE_H_
#define _MESSAGE_MESSAGE_H_
#include <cstdint>
#include <fstream>
#include <cstring>

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
    const static std::uint32_t MIN_TYPE_ELEMENT = 1;
    const static std::uint32_t MAX_TYPE_ELEMENT = 4;
    const static std::uint32_t MAX_TIME_DELAY = 2;

    Message();
    Message(const Message& );
    Message& operator=(const Message &);


    void swap(Message &) throw();

    ~Message();
    ErrorList read(std::ifstream &);
    std::uint32_t get_time() const;
    std::uint32_t getSize() const;
    std::uint32_t getType() const;
    ErrorList check_correct(const std::uint32_t time) const;
    void write(std::ofstream & output) const;
};

#endif // _MESSAGE_MESSAGE_H_
