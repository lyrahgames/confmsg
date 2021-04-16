#pragma once
#include <string>
#include <vector>

namespace lyrahgames::confmsg {

struct configuration {
  using string = std::string;
  template <typename T>
  using vector = std::vector<T>;

#include <lyrahgames/confmsg/configuration.ipp>
  static constexpr const char* user_config_dir = ".config";
  static constexpr const char* system_config_dir = "/etc";

  static const char* user_home_dir();
  static string system_location();
  static string user_location();
  static string hidden_directory_location();
  static string hidden_file_location();
  static string local_file_location();
  static vector<string> ordered_locations();

  configuration() = default;
  ~configuration() = default;
  configuration(const configuration&) = default;
  configuration& operator=(const configuration&) = default;
  configuration(configuration&&) = default;
  configuration& operator=(configuration&&) = default;

  void parse(const string& file_path);
  void load();

  static configuration system();
  static configuration user();
  static configuration local();
  static configuration global();

  // State
  string location{};
  string message{};
};

}  // namespace lyrahgames::confmsg