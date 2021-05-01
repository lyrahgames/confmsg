#include <lyrahgames/confmsg/configuration.hpp>
//
#include <array>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
//
#ifdef __linux__
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#endif

using namespace std;

namespace lyrahgames::confmsg {

std::filesystem::path user_home_path() {
#ifdef __linux__
  auto result = getenv("HOME");
  if (!result) result = getpwuid(getuid())->pw_dir;
  return result;
#endif
  return "";
}

void configuration::parse(const path& p) {
  if (!filesystem::is_regular_file(p))
    throw runtime_error("Configuration file '" + string(p) +
                        "' does not exist!");

  fstream file{p, ios::in};
  if (!file.is_open())
    throw runtime_error("Failed to open configuration file '" + string(p) +
                        "'!");

  getline(file, message);
  location = p;
}

void configuration::load() {
  array<path, 3> message_files = {local_path() / message_file_name,
                                  user_path() / message_file_name,
                                  system_path() / message_file_name};

  for (const auto& file : message_files) {
    try {
      parse(file);
    } catch (runtime_error& e) {
      cerr << "WARNING: " << e.what() << '\n';
      continue;
    }
    return;
  }

  cerr << "WARNING: Failed to find or parse configuration files. "
          "Fallback to default configuration.\n";
}

configuration configuration::system() {
  configuration config{};
  config.parse(system_path() / message_file_name);
  return config;
}

configuration configuration::user() {
  configuration config{};
  config.parse(user_path() / message_file_name);
  return config;
}

configuration configuration::local() {
  configuration config{};
  config.parse(local_path() / message_file_name);
  return config;
}

configuration configuration::global() {
  configuration config{};
  config.load();
  return config;
}

}  // namespace lyrahgames::confmsg