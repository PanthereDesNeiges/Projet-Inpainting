cmake_minimum_required(VERSION 3.4)
project(Projet)
list(APPEND CMAKE_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?

find_package(Imagine REQUIRED)

add_executable(Projet main.cpp image.cpp image.h pixel.cpp pixel.h frontiere.h)
ImagineUseModules(Projet Graphics)
