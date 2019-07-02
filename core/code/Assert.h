/*
Verious assert macros
For breaking (i.e. on Debug  builds) define GM_ASSERT_ENABLED, macros will still evaluate when
it is not defined, but they wont break.

Alexander Zimmermann 2019
*/
#pragma once

#ifndef NDEBUG
	#define GM_HALT() __debugbreak()	
#else
	#define GM_HALT()	
#endif 

#define GM_ASSERT(expression)														\
	do {																			\
		if(!(expression)) {															\
			GM_HALT();																\
		}																			\
	} while (0)

#define GM_ASSERT_MSG(expression, message, ...)										\
	do {																			\
		if (!(expression)) {														\
			ReportAssert(#expression, __FILE__, __LINE__, (message), __VA_ARGS__);	\
			GM_HALT();																\
		}																			\
	} while (0)			

#define GM_VERIFY(expression, message, ...)											\
	do {																			\
		if (!(expression)) {														\
			ReportAssert(#expression, __FILE__, __LINE__, (message), __VA_ARGS__);	\
		}																			\
	} while (0)	


#define GM_ASSERT_VK(vk_expression)														\
	do {																			\
		if((vk_expression) != VK_SUCCESS) {														\
			GM_HALT();																\
		}																			\
	} while (0)

#define GM_ASSERT_VK_MSG(vk_expression, message, ...)										\
	do {																			\
		if((vk_expression)!= VK_SUCCESS) {														\
			ReportAssert(#vk_expression, __FILE__, __LINE__, (message), __VA_ARGS__);		\
			GM_HALT();																\
		}																			\
	} while (0)

#define GM_VERIFY_VK(vk_expression, message, ...)											\
	do {																			\
		if((vk_expression)!= VK_SUCCESS) {														\
			ReportAssert(#vk_expression, __FILE__, __LINE__, (message), __VA_ARGS__);		\
		}																			\
	} while (0)
 
		
void ReportAssert(const char* expression,
	const char* file,
	int line,
	const char* message, ...);
