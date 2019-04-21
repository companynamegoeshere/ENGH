create_project(
        CORE SHARED

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
