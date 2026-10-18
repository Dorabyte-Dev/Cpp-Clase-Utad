#include <iostream>

const char* s_tTablaDeCadenas[] =
{
    "Hola",
    "Adios",
    "Otra cadena",
    "Wahahahahahah"
};

unsigned int uSizeArray = sizeof(s_tTablaDeCadenas) / sizeof(const char*);

const char* GetString(unsigned int _uIndex)
{
    if (_uIndex < uSizeArray)
    {
        const char** psArrayPointer = s_tTablaDeCadenas;

        psArrayPointer += _uIndex;
        return *psArrayPointer;
    }
    else
    {
        printf("Index was out of bounds, returning null...\n");
        return nullptr;
    }
}

bool GetStringReversed(unsigned int _uIndex, char* _sBuffer, unsigned int _uBufferSize)
{
    if (_uIndex < uSizeArray)
    {        
        unsigned int uSizeString = strlen(s_tTablaDeCadenas[_uIndex]);

        if (_uBufferSize > uSizeString) 
        {
            for (unsigned int i = 0; i < uSizeString; ++i)
            {
                _sBuffer[i] = s_tTablaDeCadenas[_uIndex][uSizeString - 1 - i];
            }
            _sBuffer[uSizeString] = '\0';
            return true;
        }
        else 
        {
            printf("_sBuffer was too small, risk of overflow.\n");
            return false;
        }
    }
    else
    {
        printf("Index was out of bounds, couldn't perform the reverse string operation.\n");
        return false;
    }
}

int main()
{
    printf("MyString is %s\n", GetString(3));


    char sTmp[256];
    bool reverseString = GetStringReversed(3, sTmp, 256);
    printf("MyString reversed is %s\n", sTmp);
}

