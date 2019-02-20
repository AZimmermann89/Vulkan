#pragma once

#ifndef VulkCheck
#ifdef NDEBUG
#define VulkCheck(expression) expression
#else
#define VulkCheck(expression)		\
if(!(expression) == VK_SUCCESS) {	\
	__debugbreak();					\
}	
#endif
#endif //VulkCheck

#ifndef Check
#ifdef NDEBUG
#define Check(expression) expression
#else
#define Check(expression)			\
if(!(expression)){					\
	__debugbreak();					\
}
#endif
#endif //Check
