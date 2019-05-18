project(ENGH_ENGINE CXX)
add_library(
        engh_engine STATIC

        public/core/data_types.hpp
        public/core/debug.hpp
        public/core/engine.hpp

        public/math/vec2.hpp

        public/eobject/object.hpp
        public/eobject/actor.hpp
        public/eobject/component/sub_component.hpp

        public/util/array.hpp
        public/util/single_pointer.hpp
        public/util/memory.hpp


        private/core/debug.cpp

        private/eobject/object.cpp
        private/eobject/actor.cpp
        private/eobject/component/sub_component.cpp

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

