cmake_minimal_required(VERSION 3.10)

project(AbstractFactory)

add_executable(AbstractFactory
    concrete_factory.cpp
    factory.cpp
    main.cpp
)

target_include_directories(AbstractFactory PUBLIC
    "${PROJECT_BINARY_DIR}"
)