#include <render/render_dispatcher_impl.hpp>

ENGH::Render::RenderDispatcherImpl::RenderDispatcherImpl(std::shared_ptr<Platform::Render::RenderContext> context) : context(context) {}

void ENGH::Render::RenderDispatcherImpl::Dispatch(RenderCommand *command) {
  queue += command;
}

void ENGH::Render::RenderDispatcherImpl::Render() {
  auto &context = *this->context;
  auto &renderer = *context.GetRenderer();
  for (const auto &cmd : queue) {
    cmd->shader->Bind();
    renderer.DrawVertexArray(cmd->data);
  }
  queue.Clear();
}
