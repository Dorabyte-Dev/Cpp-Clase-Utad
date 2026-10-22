struct Animal
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

	const char* AsStr(Enum _eEnum)
	{
		switch(_eEnum)
		{
			case Perro:
				break;
			case Gato:
				break;
			case Caballo:
				break;
			case Conejo:
				break;
			default:

				break;
		}
	}

	Enum AsEnum(const char* _sEnum)
	{

	}

};