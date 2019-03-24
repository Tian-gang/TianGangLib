#include "Exception.h"
#include <cstdlib>
#include <cstring>

namespace TianGangLib {

void Exception::Init(const char *message, const char* file, int line)
{
    m_message = message == NULL ? NULL : strdup(message);

    if(file != NULL)
    {
        char sl[16] = "";

        itoa(line, sl, 10);
        m_location = static_cast<char*>(malloc(strlen(file) + strlen(sl) + 2));

        if(m_location != NULL)
        {
            m_location = strcpy(m_location, file);
            m_location = strcat(m_location, ":");
            m_location = strcat(m_location, sl);
        }
    }
    else
    {
        m_location = NULL;
    }
}

Exception::Exception(const char* message)
{
    Init(message, NULL, 0);
}

Exception::Exception(const char* file, int line)
{
    Init(NULL, file, line);
}

Exception::Exception(const char *message, const char* file, int line)
{
    Init(message, file, line);
}

Exception::Exception(const Exception& e)
{
    m_message = strdup(e.m_message);
    m_location = strdup(e.m_location);
}

Exception& Exception::operator= (const Exception& e)
{
    if(this != &e)
    {
        free(m_message);
        free(m_location);
        m_message = strdup(e.m_message);
        m_location = strdup(e.m_location);
    }

    return *this;
}

const char* Exception::message() const
{
    return m_message;
}

const char* Exception::location() const
{
    return m_location;
}

Exception::~Exception()
{
    free(m_message);
    free(m_location);
}

}
