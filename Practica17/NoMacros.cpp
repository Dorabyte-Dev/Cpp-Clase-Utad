#include <cstring>
struct Animal_NoMacros
{
	enum Enum
	{
		Invalid = -1,
		Perro,
		Gato,
		Caballo,
		Conejo,
		COUNT
	};

	static const char* AsStr(Enum _eEnum)
	{
		switch(_eEnum)
		{
			case Perro:
				return "Perro";
				break;
			case Gato:
				return "Gato";
				break;
			case Caballo:
				return "Caballo";
				break;
			case Conejo:
				return "Conejo";
				break;
			default:
				return "Invalid";
				break;
		}
	}

	static Enum AsEnum(const char* _sEnum)
	{
		if(strcmp(_sEnum, "Perro") == 0)
		{
			return Perro;
		}
		else if(strcmp(_sEnum, "Gato") == 0)
		{
			return Gato;
		}
		else if(strcmp(_sEnum, "Caballo") == 0)
		{
			return Caballo;
		}
		else if(strcmp(_sEnum, "Conejo") == 0)
		{
			return Conejo;
		}
		return Invalid;
	}

};