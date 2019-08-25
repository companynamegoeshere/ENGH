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
            {"a_Position", ENGH::Platform::Render::BufferDataTypes::FLOAT3},
//            {"a_Color", ENGH::Platform::Render::BufferDataTypes::FLOAT3},
        }
    );

    auto index = context->CreateIndexBuffer();
    index->SetData({0, 1, 2});

    auto array = context->CreateVertexArray();
    array->AddVertexBuffer(vertex);
    array->SetIndexBuffer(index);

    std::string vertexSrc = R"(
			#version 440
            precision mediump float;

			layout(location = 0) in vec2 a_Position;
            out vec2 pos;
			void main() {
                pos = a_Position;
                gl_Position = vec4(a_Position, 0.0, 1.0);
			}
		)";

    std::string fragmentSrc = R"(
			#version 440
            precision mediump float;

			layout(location = 0) out vec4 color;
            in vec2 pos;
            uniform float time;
			void main() {
                color = vec4(pos * sin(time) + 0.5, 0.0, 0.0);
			}
		)";
    GLuint      vertex_shader, fragment_shader, program;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *vSrc = vertexSrc.c_str();
    glShaderSource(vertex_shader, 1, &vSrc, nullptr);
    glCompileShader(vertex_shader);
    GLint result = GL_FALSE;
    int   logLength;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &result);
    if (! result) {
        ENGH_CORE_ERROR("COULD NOT COMPILE VERTEX SHADER");
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            std::string msg;
            msg.resize(logLength + 1);
            glGetShaderInfoLog(vertex_shader, logLength, nullptr, msg.data());
            std::cout << msg << std::endl;
        }
        return 0;
    }
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *fSrc = fragmentSrc.c_str();
    glShaderSource(fragment_shader, 1, &fSrc, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &logLength);
    if (! result) {
        ENGH_CORE_ERROR("COULD NOT COMPILE FRAG SHADER");
        if (logLength > 0) {
            std::string msg;
            msg.reserve(logLength + 1);
            msg.resize(logLength + 1);
            glGetShaderInfoLog(fragment_shader, logLength, nullptr, msg.data());
            std::cout << msg << std::endl;
        }
        return 0;
    }
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    GLint location = glGetAttribLocation(program, "a_Position");
    GLint time     = glGetUniformLocation(program, "time");
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    int width, height;
    glfwGetFramebufferSize(window.nativeWindow, &width, &height);
    glViewport(0, 0, width, height);
    glfwSwapInterval(1);

    window.Loop([&](float delta) {
        context->Clear(0.2f, 0.2f, 0.2f, 1.0f);
        glUseProgram(program);
        array->Bind();
        glUniform1f(time, delta);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, index->GetCount(), GL_UNSIGNED_INT, nullptr);
        context->SwapBuffers();
    });
}