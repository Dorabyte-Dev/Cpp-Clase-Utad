#include <iostream>

void SeparateIntToBytes(int iValue)
{

    unsigned char* pChar = reinterpret_cast<unsigned char*>(&iValue);
    printf("First byte is: %02X\n", *pChar);
    printf("Second byte is: %02X\n", *(pChar + 1));
    printf("Third byte is: %02X\n", *(pChar + 2));
    printf("Fourth byte is: %02X\n", *(pChar + 3));
}

void GetHighestFromTable()
{
    int tabla[] = { 1, 3, 2, 5, 3, static_cast<int>(0xFFFFFFFF), 0x00FF0002, 2 };

    int* piTabla = tabla;

    int iCurrentHighest = *piTabla;

    for (int i = 0; i < sizeof(tabla) / sizeof(int); ++i)
    {
        if (*(piTabla + i) > iCurrentHighest)
        {
            iCurrentHighest = *(piTabla + i);
        }
    }

    printf("El entero mayor es %i\n", iCurrentHighest);
}

void GetHighestAddressFromTable()
{
    int tabla[] = { 1, 3, 2, 5, 3, static_cast<int>(0xFFFFFFFF), 0x00FF0002, 2 };

    int* piTabla = tabla;

    unsigned char* pcTabla = reinterpret_cast<unsigned char*>(piTabla);

    unsigned char* pcCurrentHighest = pcTabla;

    for (int i = 0; i < sizeof(tabla) / sizeof(unsigned char); i++)
    {
        if (*(pcTabla + i) > *pcCurrentHighest)
        {
            *pcCurrentHighest = *(pcTabla + i);
            pcCurrentHighest = pcTabla + i;
        }
    }

    printf("El byte mayor es %02X\n", *pcCurrentHighest);
    printf("La direccion en memoria del byte mayor es %02X\n", pcCurrentHighest);
}

void FlipString(char* myString)
{

    unsigned int uSizeString = strlen(myString);

    char* pcMyStringA = myString;
    char* pcMyStringB = pcMyStringA + (uSizeString - 1);
    char cPassValue = 0;

    printf("Original String was %s\n", myString);

    for (int i = 0; i < uSizeString / 2; ++i)
    {
        cPassValue = *pcMyStringA;
        *pcMyStringA = *pcMyStringB;
        *pcMyStringB = cPassValue;

        pcMyStringA++;
        pcMyStringB--;
    }

    printf("Result String was %s\n", myString);
}

int main()
{
    int iValue = 0x00FF0002;

    SeparateIntToBytes(iValue);

    GetHighestFromTable();

    GetHighestAddressFromTable();

    char sString[] = "Hello";
    FlipString(sString);

}


