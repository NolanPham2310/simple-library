#include "file_creator.hpp"
#include <nlohmann/json-schema.hpp>
#include <fstream>
#include <stdexcept>

namespace seneca::example {

const nlohmann::json file_creator::schema = {
    {"type", "object"},
    {"properties", {
        {"students", {
            {"type", "array"},
            {"items", {
                {"type", "object"},
                {"properties", {
                    {"id", {"type", "integer"}},
                    {"name", {"type", "string"}}
                }},
                {"required", {"id", "name"}},
                {"additionalProperties", false}
            }}
        }}
    }},
    {"required", {"students"}},
    {"additionalProperties", false}
};

file_creator::file_creator(std::string& file_path) : m_file_path(file_path) {
    std::cout << "Files will be created in " << m_file_path << std::endl;
}

file_creator::~file_creator() {
    std::cout << "Destructor" << std::endl;
}

void file_creator::create_file(nlohmann::json& json_object, std::string& file_name) {
    // Validate JSON against schema
    try {
        nlohmann::json_schema::json_validator validator;
        validator.set_root_schema(schema);
        validator.validate(json_object);
    } catch (const std::exception& e) {
        throw std::invalid_argument("JSON does not match the required schema: " + std::string(e.what()));
    }

    // Write to file
    std::string full_path = m_file_path + "/" + file_name;
    std::ofstream file(full_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + full_path);
    }
    file << json_object.dump(4);
    file.close();
}

nlohmann::json file_creator::read_file(std::string& file_name) {
    std::string full_path = m_file_path + "/" + file_name;
    std::ifstream file(full_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for reading: " + full_path);
    }

    nlohmann::json json_object;
    file >> json_object;
    file.close();

    // Validate JSON against schema
    try {
        nlohmann::json_schema::json_validator validator;
        validator.set_root_schema(schema);
        validator.validate(json_object);
    } catch (const std::exception& e) {
        throw std::invalid_argument("JSON does not match the required schema: " + std::string(e.what()));
    }

    return json_object;
}

} // namespace seneca::example
