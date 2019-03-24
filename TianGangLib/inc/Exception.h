#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include "Object.h"

namespace TianGangLib {

#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

class Exception : public Object
{
protected:
    char* m_message;
    char* m_location;

    void Init(const char *message, const char* file, int line);

public:
    Exception(const char* message);
    Exception(const char* file, int line);
    Exception(const char *message, const char* file, int line);

    Exception(const Exception& e);
    Exception& operator= (const Exception& e);

    virtual const char* message() const;
    virtual const char* location() const;
    virtual ~Exception() = 0;
};

class ArithmeticException : public Exception
{
public:
    ArithmeticException(const char* message = 0) : Exception(message) {}
    ArithmeticException(const char* file, int line) : Exception(file, line) {}
    ArithmeticException(const char* message, const char* file, int line) : Exception(message, file, line) {}

    ArithmeticException(const ArithmeticException& e) : Exception(e) {}
    ArithmeticException& operator= (const ArithmeticException& e)
    {
        Exception::operator =(e);
        return *this;
    }
};

class NullPointerException : public Exception
{
public:
    NullPointerException(const char* message = 0) : Exception(message) {}
    NullPointerException(const char* file, int line) : Exception(file, line) {}
    NullPointerException(const char *message, const char* file, int line) : Exception(message, file, line) {}

    NullPointerException(const NullPointerException& e) : Exception(e) {}
    NullPointerException& operator= (const NullPointerException& e)
    {
        Exception::operator =(e);
        return *this;
    }
};

class IndexOutOfBoundsException : public Exception
{
public:
     IndexOutOfBoundsException(const char* message = 0) : Exception(message) {}
     IndexOutOfBoundsException(const char* file, int line) : Exception(file, line) {}
     IndexOutOfBoundsException(const char *message, const char* file, int line) : Exception(message, file, line) {}

     IndexOutOfBoundsException(const  IndexOutOfBoundsException& e) : Exception(e) {}
     IndexOutOfBoundsException& operator= (const  IndexOutOfBoundsException& e)
     {
         Exception::operator =(e);
         return *this;
     }
};

class NoEnoughMemoryException : public Exception
{
public:
      NoEnoughMemoryException(const char* message = 0) : Exception(message) {}
      NoEnoughMemoryException(const char* file, int line) : Exception(file, line) {}
      NoEnoughMemoryException(const char *message, const char* file, int line) : Exception(message, file, line) {}

      NoEnoughMemoryException(const   NoEnoughMemoryException& e) : Exception(e) {}
      NoEnoughMemoryException& operator= (const   NoEnoughMemoryException& e)
      {
          Exception::operator =(e);
          return *this;
      }
};

class InvalidParameterException : public Exception
{
public:
      InvalidParameterException(const char* message = 0) : Exception(message) {}
      InvalidParameterException(const char* file, int line) : Exception(file, line) {}
      InvalidParameterException(const char *message, const char* file, int line) : Exception(message, file, line) {}

      InvalidParameterException(const   InvalidParameterException& e) : Exception(e) {}
      InvalidParameterException& operator= (const   InvalidParameterException& e)
      {
          Exception::operator =(e);
          return *this;
      }
};

class InvalidOperatorException : public Exception
{
public:
    InvalidOperatorException(const char* message = 0) : Exception(message) { }
    InvalidOperatorException(const char* file, int line) : Exception(file, line) { }
    InvalidOperatorException(const char* message, const char* file, int line) : Exception(message, file, line) { }

    InvalidOperatorException(const InvalidOperatorException& e) : Exception(e) { }
    InvalidOperatorException& operator= (const InvalidOperatorException& e)
    {
        Exception::operator =(e);
        return *this;
    }
};

}


#endif // __EXCEPTION_H__
