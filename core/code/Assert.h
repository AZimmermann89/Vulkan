#ifdef NDEBUG
#define VulkCheck(expression) expression
#else
#define VulkCheck(expression)		\
if(!(expression) == VK_SUCCESS) {	\
	__debugbreak();				\
}							
#endif