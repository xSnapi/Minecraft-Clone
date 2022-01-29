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
        "*.dll"
    }

    includedirs {
        "../include",
        "../Heavy OpenGL/include",
        "pch",
    }

    links {
        "Heavy OpenGL",
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