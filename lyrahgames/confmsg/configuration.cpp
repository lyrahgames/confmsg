#include <lyrahgames/confmsg/configuration.hpp>
//
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

const char* configuration::user_home_dir() {
#ifdef __linux__
  auto result = getenv("HOME");
  if (!result) result = getpwuid(getuid())->pw_dir;
  return result;
#endif
  return "";
}

string configuration::system_location() {
  return string(system_config_dir) + "/" + config_subdir + "/" + config_file;
}

string configuration::user_location() {
  return string(user_home_dir()) + "/" + user_config_dir + "/" + config_subdir +
         "/" + config_file;
}

string configuration::hidden_directory_location() {
  return string(".") + config_subdir + "/" + config_file;
}

string configuration::hidden_file_location() {
  return string(".") + config_file;
}

string configuration::local_file_location() { return string(config_file); }

vector<string> configuration::ordered_locations() {
  vector<string> result = {
      local_file_location(),        //
      hidden_file_location(),       //
      hidden_directory_location(),  //
      user_location(),              //
      system_location()             //
  };
  return result;
}

void configuration::parse(const string& file_path) {
  fstream file{file_path, ios::in};
  if (!file.is_open())
    throw runtime_error("Failed to open configuration file '" + file_path +
                        "'!");
  getline(file, message);
}

void configuration::load() {
  auto locations = ordered_locations();
  for (const auto& file_path : locations) {
    if (!filesystem::is_regular_file(file_path)) continue;
    try {
      parse(file_path);
    } catch (runtime_error& e) {
      cerr << "Warning Configuration: " << e.what() << '\n';
      continue;
    }
    location = file_path;
    return;
  }
  cerr << "Warning Configuration: Failed to find configuration files. Fallback "
          "to default configuration.\n";
}

configuration configuration::system() {
  configuration config{};
  config.parse(system_location());
  return config;
}

configuration configuration::user() {
  configuration config{};
  config.parse(user_location());
  return config;
}

configuration configuration::local() {
  configuration config{};
  config.parse(local_file_location());
  return config;
}

configuration configuration::global() {
  configuration config{};
  config.load();
  return config;
}

}  // namespace lyrahgames::confmsg