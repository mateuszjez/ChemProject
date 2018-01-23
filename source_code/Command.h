#ifndef COMMAND_H
#define COMMAND_H
#include <string>

struct Command
{
    public:
        Command(std::string command_in) : command(command_in) {}
        Command() {}
        ~Command() {}
    std::string command;
    bool is_last = true;

    void    operator=(const std::string& str) {command = str;}
    bool    compare(const std::string& str) const {return command==str;}



};
inline bool operator==(const Command& cmd,const std::string& str) {return cmd.compare(str);}
inline bool operator==(const std::string& str,const Command& cmd) {return cmd.compare(str);}
inline bool operator!=(const Command& cmd,const std::string& str) {return !cmd.compare(str);}
inline bool operator!=(const std::string& str,const Command& cmd) {return !cmd.compare(str);}

#endif // COMMAND_H
