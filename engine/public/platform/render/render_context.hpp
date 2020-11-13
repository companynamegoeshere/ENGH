#pragma once

#include <core/engine.hpp>
#include <platform/render/frame_buffer.hpp>
#include <platform/render/index_buffer.hpp>
#include <platform/render/program_shader.hpp>
#include <platform/render/renderer.hpp>
#include <platform/render/vertex_array.hpp>
#include <platform/render/vertex_buffer.hpp>

namespace ENGH::Platform::Render {

enum class RenderLibrary {
    NONE,
    OPENGL
};

class RenderContext {
public:

  virtual void Setup() = 0;

  virtual void SwapBuffers() = 0;

  virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer() = 0;

  virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer() = 0;

  virtual std::shared_ptr<VertexArray> CreateVertexArray() = 0;

  virtual std::shared_ptr<ProgramShader> CreateShader(const std::string &vertex, const std::string &fragment) = 0;

  virtual void ReloadShader(std::shared_ptr<ProgramShader>&, const std::string &vertex, const std::string &fragment) = 0;

  virtual std::shared_ptr<FrameBuffer> CreateFrameBuffer(FrameBuffer::BufferType type, uint32 width, uint32 height) = 0;

  virtual std::shared_ptr<FrameBuffer> GetScreenFrameBuffer() = 0;

  virtual std::shared_ptr<Renderer> GetRenderer() = 0;

  virtual ~RenderContext() = 0;

};

}
