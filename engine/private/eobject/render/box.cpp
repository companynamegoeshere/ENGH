#include <eobject/render/box.hpp>

namespace ENGH::EObject::Render {

//Box *Box::instance = RenderableObject::Instantiate<Box>();

void Box::SetupRender(Platform::Render::RenderContext &context) {
  auto vertex = context.CreateVertexBuffer();
  vertex->SetData(
      {
          -1.0f, -1.0f, -1.0f, // 0
          +1.0f, -1.0f, -1.0f, // 1
          -1.0f, -1.0f, +1.0f, // 2
          +1.0f, -1.0f, +1.0f, // 3

          -1.0f, +1.0f, -1.0f, // 4
          +1.0f, +1.0f, -1.0f, // 5
          -1.0f, +1.0f, +1.0f, // 6
          +1.0f, +1.0f, +1.0f  // 7
      }
  );
  vertex->SetLayout(
      {
          {"a_Position", Platform::Render::BufferDataTypes::FLOAT3}
      }
  );
  this->array = context.CreateVertexArray();
  this->array->AddVertexBuffer(vertex);

  indexBuffer = context.CreateIndexBuffer();
  indexBuffer->SetData(
      {
          0, 1, 3, // bottom
          0, 3, 2,

          0, 2, 6, // left
          0, 6, 4,

          0, 4, 5, // back
          0, 5, 1,

          1, 5, 7, // right
          1, 7, 3,

          2, 6, 7, // front
          2, 7, 3,

          4, 5, 7, // top
          4, 7, 6
      }
  );
}

void Box::ShutdownRender(ENGH::Platform::Render::RenderContext &context) {

}

}
