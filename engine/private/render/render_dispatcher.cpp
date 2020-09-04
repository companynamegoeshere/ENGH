#include <render/render_dispatcher.hpp>

#include <core/debug.hpp>

ENGH::Render::RenderDispatcher::RenderDispatcher(
    std::shared_ptr<Platform::Render::RenderContext> context,
    smallfun::SmallFun<Math::Mat4(Math::Mat4), sizeof(void *) * 2> transformer) :
    context(context),
    transformer(transformer) {}

void ENGH::Render::RenderDispatcher::Render() {
  auto            &context  = *this->context;
  auto            &renderer = *context.GetRenderer();
  for (const auto &cmd : queue) {
    cmd.shader->Bind();
    cmd.setupUniforms(cmd.shader);
    renderer.DrawVertexArray(cmd.data, cmd.index);
  }
  queue.Clear();
}

ENGH::Render::RenderDispatcherProxy ENGH::Render::RenderDispatcher::GetProxy() {
  return ENGH::Render::RenderDispatcherProxy{
      transformer,
      [this](RenderCommand t) { this->queue += t; }
  };
}
