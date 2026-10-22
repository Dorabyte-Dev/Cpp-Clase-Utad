#pragma once

#ifdef _DEBUG
#define LOG(...) \
	printf("[%s:%d] ", __FUNCDNAME__, __LINE__); \
	printf(__VA_ARGS__); \
	printf("\n");
#define ASSERT(cond) \
	if(!(cond)) \
	{ \
		LOG("Aborted operation because %s was false\n", #cond); \
		abort(); \
	}
#endif
