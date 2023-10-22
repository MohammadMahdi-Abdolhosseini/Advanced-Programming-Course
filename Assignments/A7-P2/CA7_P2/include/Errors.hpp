#ifndef ERRORS_H_
#define ERRORS_H_ "ERRORS_H_"

#include <exception>


class Permission_Error : public std::exception {
public:
	const char* what() const noexcept;
};
class Bad_Request_Error : public std::exception {
public:
	const char* what() const noexcept;
};
class Not_Found_Error : public std::exception {
public:
	const char* what() const noexcept;
};
class Empty_Error : public std::exception {
public:
	const char* what() const noexcept;
};

#endif