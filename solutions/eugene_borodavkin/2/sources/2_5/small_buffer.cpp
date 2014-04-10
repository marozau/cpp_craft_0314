#include "message.h"
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <list>
#include <unordered_map>
#include <unordered_set>

const static std::uint32_t MAX_BUFFER_SIZE = 2048;
typedef std::unordered_map<std::uint32_t, std::uint32_t> map;
typedef std::unordered_set<std::uint32_t> set;
void increaseTimesMessageUsed(map& times, const set& curTime){
    for(auto msgType: curTime){
        times[ msgType ] ++;
    }
}

int main()
{
    std::ifstream input(BINARY_DIR"/input.txt", std::ios::binary);
    std::uint32_t curTime=0;

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
            return 1;
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
    std::ofstream output(BINARY_DIR"/output.txt",std::ios::binary);

    for(auto msgType : allMsgType){
        output.write(reinterpret_cast< const char* >( &msgType.first ), sizeof(msgType.first));
        const double result = static_cast<double> (msgType.second) / timesMsgType[msgType.first];
        output.write(reinterpret_cast< const char* >( &result ),sizeof(result));
    }


    return 0;
}


