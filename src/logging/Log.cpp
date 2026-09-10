#include "Log.h"

#include <iostream>
#include <format>
#include <assert.h>

void Log::Info(const std::string &tag, const std::string &message)
{
    std::cout << std::format("[INFO][{}] {}", tag, message) << std::endl;
}

void Log::Warning(const std::string &tag, const std::string &message)
{
    std::cout << std::format("[WARNING][{}] {}", tag, message) << std::endl;
}

void Log::Error(const std::string &tag, const std::string &message)
{
    std::cout << std::format("[ERROR][{}] {}", tag, message) << std::endl;
}

void Log::Fatal(const std::string &tag, const std::string &message)
{
    std::cout << std::format("[FATAL][{}] {}", tag, message) << std::endl;
    assert(false);
}
