project "Heavy OpenGL"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin/obj/%{cfg.buildcfg}"

    pchheader "hvpch.h"
    pchsource "pch/hvpch.cpp"

    files {
        "pch/*.h",
        "pch/*.cpp",
        "**.cpp",
        "**.hpp",
        "**.h",
        "*.lua",
        "*.dll"
    }

    includedirs {
        "../include",
        "include",
        "pch",
    }

    libdirs {
        "../libs/GLEW",
        "../libs/GLFW",
    }

    links {
        "glfw3_mt.lib",
        "glew32s.lib",
        "opengl32.lib",
    }

    linkoptions { 
        "/NODEFAULTLIB:library" 
    }

    defines {
        "GLEW_STATIC",
    }

    filter "configurations:Debug"
        defines {
            "DEBUG"
        }
        symbols "On"

    filter "configurations:Release"
        defines {
            "NDEBUG"
        }
        symbols "On"