cmake_minimum_required(VERSION 3.13)
project(ComputacaoGrafica)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(ComputacaoGrafica Utils/Utils.cpp Utils/Utils.hpp
        Utils/Cone.cpp Utils/Cone.hpp Utils/Cylinder.cpp Utils/Cylinder.hpp Utils/Sphere.cpp
        Utils/Sphere.hpp Utils/Plane.cpp Utils/Plane.hpp Utils/Object_.cpp Utils/Object_.hpp
        Utils/Cube.hpp Utils/Cube.cpp Bitmap/Bitmap.cpp Bitmap/Bitmap.hpp
        Bitmap/BitmapHeaderInfo.h Bitmap/BitmapHeaderFile.h Utils/Camera.hpp Utils/Camera.cpp
        Utils/Scene.cpp Utils/Scene.hpp Main.cpp Utils/IntersectionPoint.cpp
        Utils/IntersectionPoint.hpp Utils/Light.cpp Utils/Light.hpp Utils/PontualLight.cpp Utils/PontualLight.hpp
        Utils/Material.cpp Utils/Material.hpp Utils/SpotLight.cpp Utils/SpotLight.hpp
        Utils/AmbientLight.cpp Utils/AmbientLight.hpp Utils/LuzRemota.cpp Utils/LuzRemota.hpp
        Utils/Vector.cpp Utils/Vector.hpp Utils/Triangle.cpp Utils/Triangle.hpp Utils/Matrix.cpp
        Utils/Matrix.hpp CenarioOpenGL.cpp Utils/Cluster.cpp Utils/Cluster.h)

target_link_libraries(ComputacaoGrafica -lOpenGL32 -lfreeGLUT -lglu32)

