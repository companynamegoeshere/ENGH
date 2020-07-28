#include <eobject/render/sphere.hpp>
#include <core/math.hpp>

#include <map>

namespace ENGH::EObject::Render {

static std::map<std::pair<uint32, uint32>, std::weak_ptr<Sphere>> instances;

std::shared_ptr<Sphere> Sphere::Get(uint32 latCount, uint32 longCount) {
  auto key = std::make_pair(latCount, longCount);
  auto first = instances.find(key);
  if(first == instances.end() || first->second.expired()) {
    auto p = std::shared_ptr<Sphere>(RenderableObject::Instantiate<Sphere>(latCount, longCount));
    instances[key] = p;
    return p;
  }
  return first->second.lock();
}

Sphere::Sphere(uint32 latCount, uint32 longCount) : latCount(latCount), longCount(longCount) {}

void Sphere::SetupRender(Platform::Render::RenderContext &context) {
  TArray<float>  dataList;
  TArray<uint32> indexList;

  uint32 lats      = latCount;
  uint32 longs     = longCount;
  uint32 indicator = 0;

  for (uint32 i = 0; i <= lats; i++) {
    float lat0 = static_cast<float>(Math::PI * (-0.5 + (double) (i - 1) / lats));
    float z0   = sin(lat0);
    float zr0  = cos(lat0);

    float lat1 = static_cast<float>(Math::PI * (-0.5 + (double) i / lats));
    float z1   = sin(lat1);
    float zr1  = cos(lat1);

    for (uint32 j = 0; j <= longs; j++) {
      float lng = static_cast<float>(2 * Math::PI * (double) (j - 1) / longs);
      float x   = cos(lng);
      float y   = sin(lng);

      dataList.push_back(x * zr0);
      dataList.push_back(y * zr0);
      dataList.push_back(z0);
      indexList.push_back(indicator++);

      if (j > 1) {
        indexList.push_back(indicator - 2);
        indexList.push_back(indicator - 3);
      }

      dataList.push_back(x * zr1);
      dataList.push_back(y * zr1);
      dataList.push_back(z1);
      indexList.push_back(indicator++);

      if (j > 0) {
        indexList.push_back(indicator - 2);
        indexList.push_back(indicator - 3);
      }
    }
  }

  auto vertex = context.CreateVertexBuffer();
  vertex->SetData(dataList);
  vertex->SetLayout(
      {
          {"a_Position", Platform::Render::BufferDataTypes::FLOAT3}
      }
  );

  array = context.CreateVertexArray();
  array->AddVertexBuffer(vertex);

  indexBuffer = context.CreateIndexBuffer();
  indexBuffer->SetData(indexList);
}

void Sphere::ShutdownRender(ENGH::Platform::Render::RenderContext &context) {

}

}
