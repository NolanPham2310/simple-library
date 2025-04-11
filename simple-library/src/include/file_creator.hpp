#include <iostream>
#include <nlohmann/json.hpp>

namespace seneca::example {

class file_creator {
public:
    file_creator(std::string& file_path);
    file_creator() = delete;
    ~file_creator();

    file_creator(const file_creator&) = delete;
    file_creator(file_creator&&) = delete;
    file_creator& operator=(const file_creator&) = delete;
    file_creator& operator=(file_creator&&) = delete;

    void create_file(nlohmann::json& json_object, std::string& file_name);
    nlohmann::json read_file(std::string& file_name);

private:
    std::string m_file_path;
    // Remove m_fd as it’s unused in this context
    static const nlohmann::json schema; // Add schema as a static member
};

} // namespace seneca::example
