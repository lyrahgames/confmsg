#pragma once
#include <filesystem>
#include <string>

namespace lyrahgames::confmsg {

std::filesystem::path user_home_path();

struct configuration {
  using cztring = const char*;
  using string = std::string;
  using path = std::filesystem::path;

  static constexpr cztring message_file_name = "message.conf";

  static path system_path();
  static path user_path();
  static path local_path();

  void parse(const path& file_path);
  void load();

  static configuration system();
  static configuration user();
  static configuration local();
  static configuration global();

  // State
  path location{};
  string message{};
};

}  // namespace lyrahgames::confmsg