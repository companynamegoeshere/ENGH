#include <render/render_dispatcher_impl.hpp>

ENGH::Render::RenderDispatcherImpl::RenderDispatcherImpl(
    std::shared_ptr<Platform::Render::RenderContext> context,
    std::function<Math::Mat4(Math::Mat4)> transformer) :
    context(context) {
  this->transformer = transformer;
}

void ENGH::Render::RenderDispatcherImpl::Dispatch(RenderCommand command) {
  queue += command;
}

void ENGH::Render::RenderDispatcherImpl::Render() {
  auto &context = *this->context;
  auto &renderer = *context.GetRenderer();
  for (const auto &cmd : queue) {
    cmd.shader->Bind();
    cmd.setupUniforms(cmd.shader);
    renderer.DrawVertexArray(cmd.data, cmd.index);
  }
  queue.Clear();
}
