#ifndef  __EXCEPTION__H__
#define __EXCEPTION__H__

#include <exception>
#include <string>

class BaseException : std::exception
{
public:
	BaseException(int line, const char* file) noexcept;
	~BaseException()  = default;
	virtual const char* what() const noexcept override;
	virtual const char* getType() const noexcept;
	const std::string getOriginString() const noexcept;

private:
	int line;
	std::string file;

protected:
	mutable std::string	 whatBuffer;
};

#endif // ! __EXCEPTION__H__




