workspace "Minecraft"
    startproject "Minecraft Clone"
    architecture "x64"
    configurations {
        "Debug",
        "Release"
    }

    filter {
        "platforms:Win64"
    }
    system "Windows"

include "Minecraft Clone"
include "Heavy OpenGL"