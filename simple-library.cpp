#include "simple-library.h"
#include <nlohmann/json_schema.hpp>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;
using validator = nlohmann::json_schema::json_validator;

// Define the schema as a static constant
static const json schema = json::parse(R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
        "students": {
            "type": "array",
            "items": {
                "type": "object",
                "properties": {
                    "id": {"type": "integer"},
                    "name": {"type": "string"}
                },
                "required": ["id", "name"],
                "additionalProperties": false
            }
        }
    },
    "required": ["students"],
    "additionalProperties": false
}
)");

void create_file(const json& obj, const std::string& path) {
    // Validate the JSON against the schema
    validator val;
    val.set_root_schema(schema);
    try {
        val.validate(obj);
    } catch (const std::exception& e) {
        throw std::runtime_error("JSON validation failed: " + std::string(e.what()));
    }

    // Write the JSON to the file
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + path);
    }
    file << obj.dump(4); // Pretty-print with 4-space indentation
    file.close();
}
