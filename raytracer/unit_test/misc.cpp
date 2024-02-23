#include <gtest/gtest.h>
#include "utility/logger.hpp"
#include <iostream>

TEST(misc, logger) {

    Logger l;
    l.SetLogLevel(LogLevel::Error);
    l.LogVerbose("Test");
    EXPECT_TRUE(l.GetLog().empty());
    l.SetLogLevel(LogLevel::Debug);
    l.LogVerbose("Test");
    EXPECT_TRUE(l.GetLog().empty());
    l.SetLogLevel(LogLevel::Verbose);
    l.LogDebug("Test");
    l.LogDebug("Test");
    l.LogDebug("Test");
    l.LogDebug("Test");
    l.LogDebug("Test");
    EXPECT_FALSE(l.GetLog().empty());
    std::cout << l.GetLog();
}