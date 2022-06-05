#include "gtest/gtest.h"
#include "kvs.h"

TEST(AbsoluteDateTestSuite, ExampleDate){ // 12/2/2020 -> 737761
    EXPECT_EQ(123,737761);
}


TEST(AbsoluteDateTestSuite, IncorrectDate){ // 12/0/2020 -> 0

}