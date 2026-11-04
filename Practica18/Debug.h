#pragma once

#ifdef _DEBUG
#define LOG(...) \
do { \
        printf("[%s:%d] ", __FUNCDNAME__, __LINE__); \
        printf(__VA_ARGS__); \
        printf("\n"); \
    } while(0)

#define ASSERT(cond) \
do { \
        if (!(cond)) { \
            LOG("Aborted operation because %s was false\n", #cond); \
            abort(); \
        } \
    } while(0)
	
#else
	#define LOG(...) do { }while(0)
	#define ASSERT(cond) do { }while(0)
#endif
