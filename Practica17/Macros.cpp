#include <cstring>

#define DECLARE_ENUM_TYPE(_COLOR) _COLOR,

#define DECLARE_ENUM_TO_STRING(_ANIMAL) \
	case _ANIMAL: \
			return #_ANIMAL; \
			break;

#define DECLARE_STRING_TO_ENUM(_ANIMAL) \
	if(strcmp(_sEnum, #_ANIMAL) == 0) \
			{ \
				return _ANIMAL; \
			}

#define DECLARE_ENUM(_NAME, _LIST) \
struct _NAME \
{ \
	enum Enum \
	{ \
		Invalid = -1, \
		_LIST(DECLARE_ENUM_TYPE) \
		COUNT \
	}; \
	static const char* AsStr(Enum _eEnum) \
	{ \
		switch(_eEnum) \
		{ \
	_LIST(DECLARE_ENUM_TO_STRING) \
		default: \
			return "Invalid"; \
			break; \
		} \
	} \
	static Enum AsEnum(const char* _sEnum) \
	{ \
		_LIST(DECLARE_STRING_TO_ENUM)	\
		return Invalid; \
	} \
}; \

#define ANIMAL_ENUM(_CALL) \
	_CALL(Perro) \
	_CALL(Gato) \
	_CALL(Caballo) \
	_CALL(Conejo) 

#define KITCHEN_ENUM(_CALL) \
	_CALL(Taza) \
	_CALL(Sarten) \
	_CALL(Cuchara) \
	_CALL(Plato)

DECLARE_ENUM(Animal_Macros, ANIMAL_ENUM);
DECLARE_ENUM(Cocina_Macros, KITCHEN_ENUM);


