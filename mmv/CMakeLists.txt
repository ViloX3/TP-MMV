cmake_minimum_required(VERSION 3.14)

project(mmv LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)


add_executable(mmv
  main.cpp
  vec2.h
  vec2.cpp
  vec3.h
  vec3.cpp
  box2.h
  box2.cpp
  grille.h
  grille.cpp
  scalarfield.h
  scalarfield.cpp
  heightfield.h
  heightfield.cpp
)
target_link_libraries(mmv Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)
install(TARGETS mmv
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
