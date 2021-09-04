#!/usr/bin/env bash


cp vendor/imgui/imgui.h vendor/imgui/backends/imgui.h
cp vendor/imgui/imconfig.h vendor/imgui/backends/imconfig.h
cp -rf vendor/imgui/*.h src/include/imgui/
cp -rf vendor/imgui/backends/imgui_impl_glfw.h src/include/imgui/
cp -rf vendor/imgui/backends/imgui_impl_opengl3.h src/include/imgui/
