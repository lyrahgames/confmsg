#include <iomanip>
#include <iostream>
//
#include <lyrahgames/confmsg/configuration.hpp>

using namespace std;
using namespace lyrahgames;

int main() {
  const auto config = confmsg::configuration::global();
  cout << setw(15) << "message = " << config.message << '\n'
       << setw(15) << "location = " << config.location << '\n';
}