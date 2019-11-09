project(ENGH_ENGINE CXX)
add_library(
        engh_engine STATIC

        public/core/data_types.hpp
        public/core/debug.hpp
        public/core/engine.hpp
        public/core/log.hpp

        public/math/vec2.hpp

        public/eobject/object.hpp
        public/eobject/actor.hpp
        public/eobject/component/sub_component.hpp

        public/platform/window.hpp

        public/platform/opengl/glfw_window.hpp

        public/platform/opengl/render/base_shader.hpp
        public/platform/opengl/render/fragment_shader.hpp
        public/platform/opengl/render/index_buffer.hpp
        public/platform/opengl/render/program_shader.hpp
        public/platform/opengl/render/renderer.hpp
        public/platform/opengl/render/render_context.hpp
        public/platform/opengl/render/vertex_array.hpp
        public/platform/opengl/render/vertex_buffer.hpp
        public/platform/opengl/render/vertex_shader.hpp

        public/platform/render/buffer_layout.hpp
        public/platform/render/index_buffer.hpp
        public/platform/render/program_shader.hpp
        public/platform/render/renderer.hpp
        public/platform/render/render_device.hpp
        public/platform/render/render_context.hpp
        public/platform/render/vertex_array.hpp
        public/platform/render/vertex_buffer.hpp

        public/util/array.hpp
        public/util/memory.hpp


        private/core/debug.cpp
        private/core/log.cpp

        private/eobject/object.cpp
        private/eobject/actor.cpp
        private/eobject/component/sub_component.cpp

        private/platform/window.cpp

        private/platform/opengl/glfw_window.cpp

        private/platform/opengl/render/base_shader.cpp
        private/platform/opengl/render/fragment_shader.cpp
        private/platform/opengl/render/index_buffer.cpp
        private/platform/opengl/render/program_shader.cpp
        private/platform/opengl/render/renderer.cpp
        private/platform/opengl/render/render_context.cpp
        private/platform/opengl/render/vertex_array.cpp
        private/platform/opengl/render/vertex_buffer.cpp
        private/platform/opengl/render/vertex_shader.cpp

        private/platform/render/buffer_layout.cpp
        private/platform/render/renderer.cpp
        private/platform/render/render_device.cpp
        private/platform/render/render_context.cpp

        private/util/array.cpp
)

set_target_properties(engh_engine
        PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(engh_engine PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>"
        "$<INSTALL_INTERFACE:include>")

target_link_libraries(engh_engine)
target_link_libraries(engh_engine glfw)
target_link_libraries(engh_engine glad)
set_target_properties(engh_engine PROPERTIES COTIRE_PREFIX_HEADER_IGNORE_PATH "/usr/include/GL/")
cotire(engh_engine)
