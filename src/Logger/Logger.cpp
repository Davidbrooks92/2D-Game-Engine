#include "Logger.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <curses.h>

std::vector<LogEntry> Logger::messages;

void Logger::Log(const std::string& message){
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    LogEntry logEntry;
    logEntry.type = LOG_INFO;
    logEntry.message = "LOG: [" + message + "] at: " + std::ctime(&end_time);

    std::cout << "\033[32m"  << logEntry.message << "\033[0m";

    messages.push_back(logEntry);
}

void Logger::Err(const std::string& message){
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    LogEntry logEntry;
    logEntry.type = LOG_INFO;
    logEntry.message = "ERR: [" + message + "] at: " + std::ctime(&end_time);
    std::cout << "\033[31m"  << logEntry.message <<"\033[0m";
}