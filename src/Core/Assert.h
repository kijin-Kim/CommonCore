#pragma once

#if defined(_MSC_VER)
#define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__)
#define DEBUG_BREAK() __builtin_trap()
#endif

#ifdef NDEBUG
#define CC_ASSERT(expr) ((void)0)
#else
#define CC_ASSERT(expr)                                                                                                \
	do                                                                                                                 \
	{                                                                                                                  \
		if (!(expr))                                                                                                   \
		{                                                                                                              \
			DEBUG_BREAK();                                                                                             \
		}                                                                                                              \
	} while (0)
#endif
// statement 문제와 semicolon 문제를 피하기 위해 do while사용

