#ifndef __TGSTRING_H__
#define __TGSTRING_H__

#include "Object.h"
#include "Exception.h"
#include <cstring>
#include <cstdlib>

namespace TianGangLib
{

class String : public Object
{
    char* m_str;
    int m_length;

protected:
    void init(const char* str);
    bool equal(const char* one, const char* other, int begin, int end) const;
    static size_t* createPMT(const char* str, size_t len);
    static int kmp(const char* str1, const char* str2);

public:
    String(char c);
    String(const char* str = "");
    String(const String& other);
    const char* str() const;
    int length() const;

    String& remove(int pos, int len);
    String& remove(const String& str);
    String& insert(int pos, const String& obj);
    String& replace(const String& str, const String& obj);

    bool startWith(const String& obj) const;
    bool endWith(const String& obj) const;
    int indexOf(const String& obj) const;

    String& operator = (const char* other);
    String& operator = (const String& other);

    bool operator == (const char* other) const;
    bool operator == (const String& other) const;
    bool operator != (const char* other) const;
    bool operator != (const String& other) const;
    bool operator > (const char* other) const;
    bool operator > (const String& other) const;
    bool operator < (const char* other) const;
    bool operator < (const String& other) const;
    bool operator >= (const char* other) const;
    bool operator >= (const String& other) const;
    bool operator <= (const char* other) const;
    bool operator <= (const String& other) const;

    char operator [] (int index) const;
    char& operator [] (int index);

    String operator + (const char* other) const;
    String operator + (const String& other) const;
    String& operator += (const char* other);
    String& operator += (const String& other);

    String substr(int begin) const;
    String substr(int begin, int end) const;

    ~String();
};

}


#endif // __TGSTRING_H__
