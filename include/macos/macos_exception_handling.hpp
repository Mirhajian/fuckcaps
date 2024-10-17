#pragma once

#include <iostream>
#include <string>

class MacOSExceptionHandling {
public:
    
    static const bool checkNullopt(const int& action, const int& alpha,
                            const int& left, const int& down, 
                            const int& up, const int& right);

    const std::string* what() const;
};
