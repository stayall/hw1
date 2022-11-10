#include "Exception.h"

#include <sstream>

BaseException::BaseException(int line, const char* file) noexcept
	:line(line),
	file(file)
{
}

const char* BaseException::what() const noexcept
{
	std::ostringstream ss;
	ss << getType() << std::endl
		<< getOriginString() << std::endl;
	
	whatBuffer = ss.str();
	return whatBuffer.c_str();;
}

const char* BaseException::getType() const noexcept
{
	return "User Base Exception";
}

const std::string BaseException::getOriginString() const noexcept
{
	std::ostringstream ss;
	ss << "File: " << file  << std::endl
		<< "Line: " << line << std::endl;

	return ss.str();
	
}
