#include "file_creator.hpp"

#include <gtest/gtest.h>
// #include <spdlog/spdlog.h>
#include <filesystem>

namespace
{

class file_creator_test : public ::testing::Test
{
protected:

    file_creator_test()
    {

    };

    void SetUp()
    {

    }

    void TearDown()
    {

    }
};

TEST_F(file_creator_test, write_data_to_non_existing_file)
{
    std::cout<<" This is the test!"<<std::endl;
    EXPECT_TRUE(true);
}

}
