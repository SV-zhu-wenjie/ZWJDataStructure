#include "Exception.h"
#include <cstring>
#include <cstdlib>

using namespace std;
namespace ZWJ {

void Exception::init(const char *message, const char *file, int line)
{
    _message = strdup(message);
    if (file != NULL) {
        char sl[16]= {0};
        itoa(line, sl, 10);
        _location = static_cast<char*>(malloc(strlen(file) + strlen(sl) + 2));
        if (_location != NULL) {
            _location = strcpy(_location, file);
            _location = strcat(_location, ":");
            _location = strcat(_location, sl);
            }
    } else
        _location = NULL;
}

Exception::Exception(const char *message)
{
    init(message, NULL, 0);
}

Exception::Exception(const char *file, int line)
{
    init(NULL, file, line);
}

Exception::Exception(const char *message, const char *file, int line)
{
    init(message, file, line);
}

Exception::Exception(const Exception &e)
{
    _message = strdup(e._message);
    _location = strdup(e._location);
}

Exception &Exception::operator=(const Exception &e)
{
    if(this != &e) {
        free(_message);
        free(_location);
        _message = strdup(e._message);
        _location = strdup(e._location);
    }
    return *this;
}

const char *Exception::message() const
{
    return _message;
}

const char *Exception::location() const
{
    return _location;
}

Exception::~Exception()
{
    free(_message);
    free(_message);
}


}
