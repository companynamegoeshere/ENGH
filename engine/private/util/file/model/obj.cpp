#include <util/file/model/obj.hpp>

#include <array>
#include <fstream>
#include <sstream>
#include <string>

namespace ENGH::Util::File::Model {

bool parseObj(
    std::istream& fInput,
    EObject::Data::Model3D &model
) {
  if (!fInput) {
    return false;
  }

  model.clearData();

  struct IndexData {
    int vertex{};
    int normal{};
    int uv{};
  };

  Util::TArray<float> uvList;
  Util::TArray<float> normalList;
  Util::TArray<IndexData> indexList;

  std::array<float, 3> fVal{};
  std::array<uint32, 3> iVal{};

  std::string line;
  while (std::getline(fInput, line)) {
    std::istringstream ss(line);
    std::string token;
    ss >> token;
    if (token == "#") {
      continue;
    } else if (token == "v") {
      ss >> fVal[0] >> fVal[1] >> fVal[2];
      model.vertex += {fVal[0], fVal[1], fVal[2]};
    } else if (token == "vt") {
      ss >> fVal[0] >> fVal[1];
      uvList += {fVal[0], fVal[1]};
    } else if (token == "vn") {
      ss >> fVal[0] >> fVal[1] >> fVal[2];
      normalList += {fVal[0], fVal[1], fVal[2]};
    } else if (token == "f") {
      int n;
      int count = 0;
      while (ss >> n) {
        if (count > 2) {
          if (count > 3) {
            indexList += {indexList[indexList.size() - 1], indexList[indexList.size() - 2]};
          } else {
            indexList += {indexList[indexList.size() - 3], indexList[indexList.size() - 1]};
          }
        }

        IndexData data{};
        data.vertex = n;
        ss.ignore();
        if (ss >> n) {
          data.uv = n;
        } else {
          ss.clear();
        }
        ss.ignore();
        if (ss >> n) {
          data.normal = n;
        } else {
          ss.clear();
        }
        indexList += data;
        count++;
      }
    }
  }

  model.uvCoords.resize(std::max(uvList.size(), model.vertex.size()));
  model.normals.resize(std::max(normalList.size(), model.vertex.size()));
  for (const auto &data : indexList) {
    uint32 v = data.vertex;
    if(data.vertex < 0) {
      v = model.vertex.size() - v;
    }
    model.index += v;

    uint32 n = data.normal;
    if(data.normal < 0) {
      n = normalList.size() - n;
    }
    if(n != 0) {
      model.normals[v] += normalList[n];
    }

    uint32 u = data.uv;
    if(data.normal < 0) {
      u = uvList.size() - u;
    }
    if(n != 0) {
      model.uvCoords[v] += uvList[u];
    }

  }

  return true;
}

}
