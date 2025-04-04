#ifndef SIMPLE_LIBRARY_H
#define SIMPLE_LIBRARY_H

#include <nlohmann/json.hpp>

void create_file(const nlohmann::json& obj, const std::string& path);

#endif
