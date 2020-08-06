project(ENGH_ENGINE CXX)
add_library(
        engh_engine STATIC

        public/core/data_types.hpp
        public/core/debug.hpp
        public/core/engine.hpp
        public/core/log.hpp
        public/core/math.hpp

        public/eobject/actor.hpp
        public/eobject/object.hpp
        public/eobject/tick_target.hpp
        public/eobject/world.hpp

        public/eobject/component/box_component.hpp
        public/eobject/component/component.hpp
        public/eobject/component/primitive_component.hpp
        public/eobject/component/scene_component.hpp
        public/eobject/component/sphere_component.hpp

        public/eobject/data/transform.hpp

        public/eobject/render/box.hpp
        public/eobject/render/renderable_object.hpp
        public/eobject/render/sphere.hpp
        public/eobject/render/standard_shaders.hpp

        public/input/input_events.hpp
        public/input/input_handler.hpp
        public/input/input_provider.hpp
        public/input/input_registrar.hpp

        public/platform/window.hpp

        public/platform/opengl/glfw_input_provider.hpp
        public/platform/opengl/glfw_window.hpp

        public/platform/opengl/render/base_shader.hpp
        public/platform/opengl/render/fragment_shader.hpp
        public/platform/opengl/render/frame_buffer.hpp
        public/platform/opengl/render/index_buffer.hpp
        public/platform/opengl/render/program_shader.hpp
        public/platform/opengl/render/renderer.hpp
        public/platform/opengl/render/render_context.hpp
        public/platform/opengl/render/vertex_array.hpp
        public/platform/opengl/render/vertex_buffer.hpp
        public/platform/opengl/render/vertex_shader.hpp

        public/platform/render/buffer_layout.hpp
        public/platform/render/frame_buffer.hpp
        public/platform/render/index_buffer.hpp
        public/platform/render/program_shader.hpp
        public/platform/render/renderer.hpp
        public/platform/render/render_device.hpp
        public/platform/render/render_context.hpp
        public/platform/render/vertex_array.hpp
        public/platform/render/vertex_buffer.hpp

        public/render/render_command.hpp
        public/render/render_dispatcher.hpp
        public/render/render_dispatcher_impl.hpp
        public/render/world_renderer.hpp

        public/render/camera/camera.hpp
        public/render/camera/perspective_camera.hpp

        public/render/component/primitive_render_delegate.hpp

        public/util/array.hpp
        public/util/memory.hpp
        public/util/set.hpp


        private/core/debug.cpp
        private/core/log.cpp

        private/eobject/actor.cpp
        private/eobject/object.cpp
        private/eobject/world.cpp

        private/eobject/component/box_component.cpp
        private/eobject/component/component.cpp
        private/eobject/component/primitive_component.cpp
        private/eobject/component/scene_component.cpp
        private/eobject/component/sphere_component.cpp

        private/eobject/data/transform.cpp

        private/eobject/render/box.cpp
        private/eobject/render/renderable_object.cpp
        private/eobject/render/sphere.cpp
        private/eobject/render/standard_shaders.cpp

        private/input/input_events.cpp
        private/input/input_handler.cpp
        private/input/input_provider.cpp
        private/input/input_registrar.cpp

        private/platform/window.cpp

        private/platform/opengl/glfw_input_provider.cpp
        private/platform/opengl/glfw_window.cpp

        private/platform/opengl/render/base_shader.cpp
        private/platform/opengl/render/fragment_shader.cpp
        private/platform/opengl/render/frame_buffer.cpp
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

        private/render/render_command.cpp
        private/render/render_dispatcher.cpp
        private/render/render_dispatcher_impl.cpp
        private/render/world_renderer.cpp

        private/render/camera/camera.cpp
        private/render/camera/perspective_camera.cpp

        private/render/component/primitive_render_delegate.cpp

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
target_link_libraries(engh_engine mathfu)
SetupEngineFlags()
