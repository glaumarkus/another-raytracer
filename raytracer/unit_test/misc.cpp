#include <gtest/gtest.h>
#include "utility/logger.hpp"
#include <iostream>
#include "utility/world_parser.hpp"

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

TEST(misc, load_world_file)
{
    WorldParser parser;
    auto world = parser.ParseWorldFile("parsing_example.yaml");
    EXPECT_NE(world, nullptr);
    EXPECT_EQ(world->GetLights().size(), 1);
    EXPECT_EQ(world->GetObjects().size(), 2);
}