#include <platform/winnt/winnt_window.hpp>
#include <iostream>

int main() {
    ENGH::Logger::getCoreLogger() = ENGH::Logger(
        ENGH::Logger::Level::FINEST,
        {std::shared_ptr<std::ostream>(&std::cout, [](std::ostream *) {})},
        {std::shared_ptr<std::ostream>(&std::cerr, [](std::ostream *) {})}
    );
    ENGH::Platform::WinNT::WinNTWindow window({"ASD",
                                               800, 600,
                                               ENGH::Platform::Render::RenderLibrary::OPENGL});
    window.Init();
    auto context = window.GetContext();
    auto vertex  = context->CreateVertexBuffer();
    vertex->SetData({
                        - 0.8f, - 0.8f,
                        + 0.0f, + 0.8f,
                        + 0.8f, - 0.8f
                    });
    vertex->SetLayout(
        {
            {"a_Position", ENGH::Platform::Render::BufferDataTypes::FLOAT2},
//            {"a_Color", ENGH::Platform::Render::BufferDataTypes::FLOAT3},
        }
    );

    auto index = context->CreateIndexBuffer();
    index->SetData({0, 1, 2});

    auto array = context->CreateVertexArray();
    array->AddVertexBuffer(vertex);
    array->SetIndexBuffer(index);

    std::string vertexSrc =
                    "#version 440\nprecision mediump float;\n\nlayout(location = 0) in vec2 a_Position;\nout vec2 pos;\nvoid main() {\n    pos = a_Position;\n    gl_Position = vec4(a_Position, 0.0, 1.0);\n}\n";

    std::string fragmentSrc =
                    "#version 440\nprecision mediump float;\n\nlayout(location = 0) out vec4 color;\nin vec2 pos;\nuniform float time;\nvoid main() {\n    color = vec4(pos * sin(time) + 0.5, 0.0, 0.0);\n}";

    auto program = context->CreateShader(vertexSrc, fragmentSrc);

    int width, height;
    glfwGetFramebufferSize(window.nativeWindow, &width, &height);
    glViewport(0, 0, width, height);
    glfwSwapInterval(1);

    window.Loop([&](float delta) {
        context->Clear(0.2f, 0.2f, 0.2f, 1.0f);
        program->Bind();
        program->SetUniformFloat("time", delta);
        array->Bind();
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, index->GetCount(), GL_UNSIGNED_INT, nullptr);
        context->SwapBuffers();
    });
}