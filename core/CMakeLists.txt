include_directories(.)

create_project(
  CORE SHARED
        engine.hpp
        data_types.hpp
        object.hpp
        object.cpp
        string.hpp
        string.cpp
)
