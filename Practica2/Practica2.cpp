#include <iostream>

void SeparateIntToBytes(int _iValue)
{

    unsigned char* pChar = reinterpret_cast<unsigned char*>(&_iValue);
    printf("First byte is: %02X\n", *pChar);
    printf("Second byte is: %02X\n", *(pChar + 1));
    printf("Third byte is: %02X\n", *(pChar + 2));
    printf("Fourth byte is: %02X\n", *(pChar + 3));
}

void GetHighestFromTable(int* _piTabla, int _iSize)
{
    _iSize /= sizeof(int);

    int iCurrentHighest = *_piTabla;

    for (int i = 0; i < _iSize; ++i)
    {
        if (*(_piTabla + i) > iCurrentHighest)
        {
            iCurrentHighest = *(_piTabla + i);
        }
    }

    printf("El entero mayor es %i\n", iCurrentHighest);
}

void GetHighestAddressFromTable(int* _piTabla, int _iSize)
{
    _iSize /= sizeof(unsigned char);

    unsigned char* pcTabla = reinterpret_cast<unsigned char*>(_piTabla);

    unsigned char* pcCurrentHighest = pcTabla;

    for (int i = 0; i < _iSize; i++)
    {
        if (*(pcTabla + i) > *pcCurrentHighest)
        {
            pcCurrentHighest = pcTabla + i;
        }
    }

    printf("El byte mayor es %02X\n", *pcCurrentHighest);
    printf("La direccion en memoria del byte mayor es %p\n", pcCurrentHighest);
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
    //a.
    int iValue = 0x00FF0002;
    SeparateIntToBytes(iValue); //Se imprime en el orden inverso porque en Windows los bytes se ordenan mediante el método Little-Endian. 
                                //En Linux y otras arquitecturas Big-Endian, el orden sería el contrario.
    
    //b.
    int tabla[] = { 1, 3, 2, 5, 3, static_cast<int>(0xFFFFFFFF), 0x00FF0002, 2 };
    GetHighestFromTable(tabla, sizeof(tabla)); //0xFFFFFFFF, a pesar de ser el byte con el valor más alto, al interpretarse como
                                                             //un int, su valor se lee como -1, y por tanto el más alto es 0x00FF0002, o 16711682

    //c.
    GetHighestAddressFromTable(tabla, sizeof(tabla));

    //d.
    char sString[] = "Hello";
    FlipString(sString);

}