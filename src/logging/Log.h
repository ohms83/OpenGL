#pragma once

#include <string>
#include <format>

#define DECLARE_LOG_EXTERN(LogCategory) extern const std::string Log##LogCategory
#define DEFINE_LOG(LogCategory) const std::string Log##LogCategory = #LogCategory

#define LOG_INFO(Category, Message) Log::Info(Category, Message)
#define LOG_WARNING(Category, Message) Log::Warning(Category, Message)
#define LOG_ERROR(Category, Message) \
    do { \
        const auto formatted = std::format("({}:{}) {}", __FILE__, __LINE__, Message); \
        Log::Error(Category, formatted); \
    } while(0);
#define LOG_FATAL(Category, Message) \
    do { \
        const auto formatted = std::format("({}:{}) {}", __FILE__, __LINE__, Message); \
        Log::Fatal(Category, formatted); \
    } while(0);


class Log
{
public:
    static void Info(const std::string& tag, const std::string& message);
    static void Warning(const std::string& tag, const std::string& message);
    static void Error(const std::string& tag, const std::string& message);
    static void Fatal(const std::string& tag, const std::string& message);
};