cmake_minimum_required(VERSION 3.26)
project(correccion_examen2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

find_package(SFML)


find_package(fmt)

add_executable(correccion_examen2 main.cpp)
target_link_libraries(correccion_examen2 fmt::fmt)
target_link_libraries(correccion_examen2 sfml::sfml)

add_executable(suma suma.cpp)
target_link_libraries(suma fmt::fmt)
target_link_libraries(suma sfml::sfml)

add_executable(espejo espejo.cpp)
target_link_libraries(espejo fmt::fmt)
target_link_libraries(espejo sfml::sfml)


add_executable(rotacion rotacion.cpp)
target_link_libraries(rotacion fmt::fmt)
target_link_libraries(rotacion sfml::sfml)

add_executable(sobel sobel.cpp)
target_link_libraries(sobel fmt::fmt)
target_link_libraries(sobel sfml::sfml)


add_executable(mediana mediana.cpp)
target_link_libraries(mediana fmt::fmt)
target_link_libraries(mediana sfml::sfml)

add_executable(edge edge.cpp)
target_link_libraries(edge fmt::fmt)
target_link_libraries(edge sfml::sfml)