cmake_minimum_required(VERSION 3.20)

project(GabrPch LANGUAGES CXX)

add_library(GabrPch INTERFACE)

target_precompile_headers(GabrPch INTERFACE "gabrPch.h")

target_compile_features(GabrPch INTERFACE cxx_std_17)