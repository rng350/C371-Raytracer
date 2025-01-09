cmake_minimum_required(VERSION 3.30)
project(Raytracer)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/glm)

set(SOURCES
        main.cpp
        Camera.cpp
        Plane.cpp
        Sphere.cpp
        Light.cpp
        Triangle.cpp
        scene_loader.h
        Mesh.cpp
        MeshTriangle.cpp
        ShadeInfo.cpp
        BoundingBox.cpp
        GeometricObject.cpp
)

add_executable(Raytracer ${SOURCES})