#include <gtest/gtest.h>
#include "simple-library.h"
#include <fstream>

TEST(CreateFileTest, ValidJson) {
    nlohmann::json obj = {{"students", {{{"id", 1}, {"name", "Alice"}}}}};
    EXPECT_NO_THROW(create_file(obj, "test.json"));
    std::ifstream file("test.json");
    ASSERT_TRUE(file.is_open());
    file.close();
}

TEST(CreateFileTest, MissingStudents) {
    nlohmann::json obj = {{"data", "invalid"}};
    EXPECT_THROW(create_file(obj, "test.json"), std::runtime_error);
}

TEST(CreateFileTest, ExtraField) {
    nlohmann::json obj = {{"students", {{{"id", 1}, {"name", "Alice"}, {"extra", "field"}}}}};
    EXPECT_THROW(create_file(obj, "test.json"), std::runtime_error);
}

TEST(ReadFileTest, ValidJson) {
    nlohmann::json obj = {{"students", {{{"id", 1}, {"name", "Alice"}}}}};
    create_file(obj, "test.json");
    EXPECT_NO_THROW({
        auto result = read_file("test.json");
        EXPECT_EQ(result, obj);
    });
}

TEST(ReadFileTest, InvalidJson) {
    std::ofstream file("invalid.json");
    file << "{invalid}";
    file.close();
    EXPECT_THROW(read_file("invalid.json"), std::runtime_error);
}

TEST(ReadFileTest, SchemaMismatch) {
    nlohmann::json obj = {{"data", "invalid"}};
    create_file(obj, "valid.json"); // Temporarily bypass validation for test
    std::ofstream file("valid.json");
    file << obj.dump();
    file.close();
    EXPECT_THROW(read_file("valid.json"), std::runtime_error);
}
