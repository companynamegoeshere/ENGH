#pragma once

#include <string>
#include <optional>

namespace ENGH::Util::File {

std::optional<std::string> readFile(const std::string_view& fileName);

}
