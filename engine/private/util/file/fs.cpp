#include <util/file/fs.hpp>

#include <fstream>

namespace ENGH::Util::File {

std::optional<std::string> readFile(const std::string_view& fileName) {
  std::ifstream in(fileName.data(), std::ios::in | std::ios::ate | std::ios::binary);
  if (!in) {
    return {};
  }
  std::string data;
  data.resize(in.tellg());
  in.seekg(0, std::ios::beg);
  in.read(&data[0], data.size());
  in.close();
  return data;
}

}
