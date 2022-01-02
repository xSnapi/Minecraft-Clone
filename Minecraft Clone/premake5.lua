project "Minecraft Clone"
    kind "consoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin/obj/%{cfg.buildcfg}"

    pchheader "mcpch.h"
    pchsource "pch/mcpch.cpp"

    files {
        "pch/*.h",
        "pch/*.cpp",
        "**.cpp",
        "**.hpp",
        "**.h",
        "*.lua",
    }

    includedirs {
        "../include"
    }

    libdirs {
        "../libs/GLEW",
        "../libs/GLFW",
        "../libs/SOIL2",
    }

    links {
        "glfw3.lib",
        "glfw3_mt.lib",
        "glfw3dll.lib",
        "glew32.lib",
        "glew32s.lib",
        "opengl32.lib",
    }

    filter "configurations:Debug"
        defines {
            "DEBUG"
        }
        symbols "On"

        links {
            "soil2-debug.lib",
        }

    filter "configurations:Debug"
        defines {
            "NDEBUG"
        }
        symbols "On"

        links {
            "soil2.lib",
        }