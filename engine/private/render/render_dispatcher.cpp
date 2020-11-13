#include <render/render_dispatcher.hpp>

#include <utility>

namespace ENGH::Render {

RenderDispatcher::RenderDispatcher(
    std::shared_ptr<Platform::Render::RenderContext> context
) : context(std::move(context)) {}

void RenderDispatcher::Render() {
  auto &renderer = *context->GetRenderer();
  for (const auto &cmd : queue) {
    cmd.shader->Bind();
    cmd.setupUniforms(cmd.shader);
    renderer.DrawVertexArray(cmd.vao.get(), cmd.index.get());
  }
}

std::unique_ptr<RenderDispatcherProxy> RenderDispatcher::GetProxy(RenderData *renderData) {
  return std::make_unique<RenderDispatcherProxy>(RenderDispatcherProxy{
      renderData,
      [this](const RenderCommand &t) -> size_t {
        if (t.id == -1) {
          auto vbo = context->CreateVertexBuffer();
          vbo->SetLayout(t.layout);
          vbo->SetData(t.data);

          auto vao = context->CreateVertexArray();
          vao->AddVertexBuffer(vbo);

          auto index = context->CreateIndexBuffer();
          index->SetData(t.index);

          queue += {
              vao,
              index,
              t.shader,
              t.setupUniforms
          };
          return queue.size() - 1;
        } else {
          auto &data = queue[t.id];
          data.vao->GetVertexBuffers()[0]->SetData(t.data);
          data.index->SetData(t.index);
          data.shader = t.shader;
          data.setupUniforms = t.setupUniforms;
          return t.id;
        }
      },
      [this](size_t id, const TArray<float> &data) {
        queue[id].vao->GetVertexBuffers()[0]->SetData(data);
      },
      [this](size_t id, const TArray<uint32> &index) {
        queue[id].index->SetData(index);
      }
  });
}

}
