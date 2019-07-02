/*
Alexander Zimmermann 2019
*/
#include "Assert.h"

#include <stdio.h>
#include <Windows.h>

char * format_message(const char * message, const char* expression, const char* file, const int line)
{
	char text_start[] = "Error occured in %s line %d: (%s) %s\n";
	char text[1024];
	sprintf_s(text, text_start, file, line , expression, message);
	return text;
}

void ReportAssert(const char* expression,
	const char* file,
	const int line,
	const char* message, ...)
{
	if (expression && file && line && message)
	{
		char * formatted_text = format_message(message, expression, file, line);

		// print to the command line
		printf(formatted_text);

		// print to the debug output
		OutputDebugString(formatted_text);
	}
}
