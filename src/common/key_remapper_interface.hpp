#pragma once

class KeyRemapperInterface {
public:
    virtual ~KeyRemapperInterface() = default;
    virtual void initialize() = 0;
    virtual void run() = 0;
    virtual void cleanup() = 0;
};
