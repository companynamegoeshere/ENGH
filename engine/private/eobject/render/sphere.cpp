#include <eobject/render/sphere.hpp>
#include <core/math.hpp>

namespace ENGH::EObject::Render {

Sphere *Sphere::instance = RenderableObject::Instantiate<Sphere>();

void Sphere::SetupRender(Platform::Render::RenderContext &context) {
  TArray<float>  dataList;
  TArray<uint32> indexList;

  int lats      = 40;
  int longs     = 40;
  int indicator = 0;

  for (int i = 0; i <= lats; i++) {
    double lat0 = Math::PI * (-0.5 + (double) (i - 1) / lats);
    double z0   = sin(lat0);
    double zr0  = cos(lat0);

    double lat1 = Math::PI * (-0.5 + (double) i / lats);
    double z1   = sin(lat1);
    double zr1  = cos(lat1);

    for (int j = 0; j <= longs; j++) {
      double lng = 2 * Math::PI * (double) (j - 1) / longs;
      double x   = cos(lng);
      double y   = sin(lng);

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
