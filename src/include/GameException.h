#ifndef _DEF_GAME_EXCEPTION_H_
#define _DEF_GAME_EXCEPTION_H_

#include <exception>
#include <string>

class GameException : public std::exception
{
public :
	GameException(const std::string& s) : m_msg(s) {}
    const char* what() const noexcept {return m_msg.c_str();}
private :
	std::string m_msg;
};

// I find inheritance here just a duplication of code
// because all classes are similar, eventhough i kept
// the code like this.
class GameInitExeception : public GameException
{
public :
    using GameException::GameException;
    //GameInitExeception(const std::string& s) : GameException(s) {}
};

class GameGraphicsException : public GameException
{
public :
    using GameException::GameException;
    //GameInitExeception(const std::string& s) : GameException(s) {}
};

#endif // _DEF_GAME_EXCEPTION_H_
