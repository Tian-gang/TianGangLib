#include "TGString.h"

namespace TianGangLib
{

void String::init(const char *str)
{
    m_length = strlen(str);
    m_str = strdup(str);

    if( m_str == NULL )
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create String object...");
    }
}

String::String(char c)
{
    char s[] = {c, '\0'};

    m_length = 1;
    m_str = reinterpret_cast<char*>(malloc(2));

    if( m_str != NULL )
    {
        strcpy(m_str, s);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create String object...");
    }
}

String::String(const char* str)
{
    init(str ? str : "");
}

String::String(const String& other)
{
    init(other.str());
}

String& String::operator = (const char* other)
{
    if( other != NULL )
    {
        char* toDel = m_str;
        m_length = strlen(other);
        m_str = strdup(other);
        free(toDel);
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "the other string ptr is NULL");
    }

    return *this;
}

size_t* String::createPMT(const char* str, size_t len)
{
    size_t* PMT = NULL;

    if( str!= NULL )
    {
        PMT = reinterpret_cast<size_t*>(calloc(len, sizeof(size_t)));

        if( PMT != NULL )
        {
            size_t ll = 0;

            for(size_t i = 1; i < len; ++i)
            {
                while( ll > 0 && str[ll] != str[i] )
                {
                    ll = PMT[ll - 1];
                }

                if( str[ll] == str[i] )
                {
                    ++ll;
                }

                PMT[i] = ll;
            }
        }
        else THROW_EXCEPTION(NoEnoughMemoryException,  "No Enough to create PMT object...");
    }

    return PMT;
}

int String::kmp(const char* str1, const char* str2)
{
    int ret = - 1;
    size_t len1 = str1 != NULL ? strlen(str1) : 0;
    size_t len2 = str1 != NULL ? strlen(str2) : 0;

    if( len1 != 0 && len2 != 0 && len1 >= len2 )
    {
        size_t* PMT = createPMT(str2, len2);

        if( PMT != NULL )
        {
            for(size_t i = 0, j = 0; i < len1; ++i)
            {
                while( j > 0 && str1[i] != str2[j] )
                {
                    j = PMT[j - 1];
                }

                if( str1[i] == str2[j] && ++j == len2 )
                {
                    ret = i - j + 1;
                    break;
                }
            }

            free(PMT);
        }
    }

    return ret;
}

int String::indexOf(const String& obj) const
{
    return kmp(m_str, obj.m_str);
}

String& String::remove(int pos, int len)
{
    int begin = pos < 0 ? 0 : pos;
    int end = begin + len > m_length ? m_length : begin + len;

    if( begin < end && len > 0 )
    {
        len = m_length - (end - begin);
        char* new_str = reinterpret_cast<char*>(malloc( len + 1 ));

        if( new_str != NULL )
        {
            strncpy(new_str, m_str, begin);
            strncpy(new_str + begin, m_str + end , m_length - end);
            new_str[len] = '\0';

            char* toDel = m_str;

            m_str = new_str;
            m_length = len;

            free(toDel);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "NoEnoughMemroy to remove the string");
        }
    }


    return *this;
}

String& String::remove(const String& str)
{
    int index = indexOf(str);

    if( index >= 0 )
    {
        remove(index, str.length());
    }

    return *this;
}

String& String::replace(const String& str, const String& obj)
{
    while(1)
    {
        int index = indexOf(str);

        if( index < 0 ) break;

        remove(index, str.m_length);
        insert(index, obj);
    }

    return *this;
}

String& String::insert(int pos, const String& obj)
{
    if( 0 <= pos && pos <= m_length )
    {
        const char* str = obj.str();
        int len = strlen(str);
        char* __str = m_str;

        m_str = reinterpret_cast<char*>(malloc(len + m_length + 1));

        if( m_str != NULL )
        {
            strncpy(m_str, __str, pos);
            strncpy(m_str + pos, str, len);
            strncpy(m_str + pos + len, __str + pos, m_length - pos + 1);
            m_length += len;
            free(__str);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "the other string ptr is NULL");
        }
    }

    return *this;
}

bool String::equal(const char* one, const char* other, int begin, int end) const
{
    bool ret = true;

    for(int i = begin; i <= end; ++i)
    {
        if( one[i] != *other++ )
        {
            ret = false;
            break;
        }
    }

    return ret;
}

bool String::startWith(const String &obj) const
{
    return m_length > obj.length() && equal(m_str, obj.str(), 0, obj.length() - 1);
}

bool String::endWith(const String &obj) const
{
    return m_length > obj.length() && equal(m_str, obj.str(),m_length - obj.length(), m_length - 1);
}

int String::length() const
{
    return m_length;
}

String& String::operator = (const String& other)
{
    if( this != &other )
    {
        *this = other.str();
    }

    return *this;
}

const char* String::str() const
{
    return m_str;
}

bool String::operator == (const char* other) const
{
    return strcmp(m_str, other ? other : "") == 0;
}

bool String::operator == (const String& other) const
{
    return strcmp(m_str, other.str()) == 0;
}

bool String::operator != (const char* other) const
{
    return !(*this == other);
}

bool String::operator != (const String& other) const
{
    return !(*this == other);
}

bool String::operator > (const char* other) const
{
    return strcmp(m_str, other ? other : "") > 0;
}

bool String::operator > (const String& other) const
{
    return strcmp(m_str, other.str()) > 0;
}

bool String::operator < (const char* other) const
{
    return strcmp(m_str, other ? other : "") < 0;
}

bool String::operator < (const String& other) const
{
    return strcmp(m_str, other.str()) < 0;
}

bool String::operator >= (const char* other) const
{
    return strcmp(m_str, other ? other : "") >= 0;
}

bool String::operator >= (const String& other) const
{
    return strcmp(m_str, other.str()) >= 0;
}

bool String::operator <= (const char* other) const
{
    return strcmp(m_str, other ? other : "") <= 0;
}

bool String::operator <= (const String& other) const
{
    return strcmp(m_str, other.str()) <= 0;
}

String String::operator + (const char* other) const
{
    if( other != NULL )
    {
        char* ret = (char*)malloc( strlen(m_str) + strlen(other) + 1);

        if( ret != NULL )
        {
            strcpy(ret, m_str);
            strcat(ret, other);

            return ret;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create String object...");
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "the other string ptr is NULL");
    }
}

String String::operator + (const String& other) const
{
    return (*this + other.str());
}

String& String::operator += (const char* other)
{
    return *this = *this + other;
}

String& String::operator += (const String& other)
{
    return *this += other.str();
}

String::~String()
{
    free(m_str);
}

char String::operator [] (int index) const
{
    return const_cast<String&>(*this)[index];
}

char& String::operator [] (int index)
{
    if( 0 <= index && index < m_length )
    {
        return m_str[index];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "the string is out of bounds...");
    }
}

String String::substr(int begin, int end) const
{
    String ret = "";

    if( begin <= end )
    {
        begin = begin < 0 ? 0 : begin;
        end = end >= m_length ? m_length - 1 : end;

        int len = end - begin + 1;

        char* temp = (char*)malloc(sizeof(char) * (len + 1));

        if( temp != NULL )
        {
            strncpy(temp, m_str + begin, len);
            temp[len] = '\0';
            ret = temp;
            free(temp);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create String object...");
        }

    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "the begin cannot greater than end...");
    }

    return ret;
}

String String::substr(int begin) const
{
    return substr(begin, m_length - 1);
}

}
