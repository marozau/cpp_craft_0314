#include <iostream>
#include <algorithm>
#include <cstdint>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <list>
#include "message.h"


bool message_compare(const Message &msg1, const Message &msg2)
{
    return msg1.get_time() < msg2.get_time();
}

int main()
{
    std::ifstream input(BINARY_DIR"/input.txt", std::ios::binary);
    std::ofstream output(BINARY_DIR"/output.txt",std::ios::binary);
    typedef std::list<Message> messageList;
    messageList list;

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
    messageList::const_iterator it;
    for(it = list.begin(); it != list.end(); it++){
        it->write(output);
    }


    return 0;
}

