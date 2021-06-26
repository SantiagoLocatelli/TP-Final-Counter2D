#ifndef _FORMATTED_EXCEPTION_H_
#define _FORMATTED_EXCEPTION_H_

#include <exception>
#include <string>

class GeneralException: public std::exception {
    private:
        std::string msg_error;

    public:
        explicit GeneralException(const std::string &msg) noexcept;
        const char *what() const noexcept override;
};

#endif
