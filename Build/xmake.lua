--[[
< Novl Engine > xmake.lua
Author: DeckardZ46
Date: 2024/07/10
Note: This is xmake build file for Novl Engine
Codebase: https://github.com/DeckardZ46/NovlEngine
--]]

---------- BASIC SETTINGS ----------
set_project("Novl Engine")
set_version("0.0.1")
set_xmakever("2.9.3")

-- build mode
set_allowedmodes("debug","release")
add_rules("mode.debug", "mode.release")
if is_mode("debug") then 
    add_defines("NOVL_DEBUG")
    add_defines("NOVL_ENABLE_ASSERT")
elseif is_mode("release") then 
    add_defines("NOVL_RELEASE")
end

set_targetdir("$(builddir)/$(mode)/$(plat)_$(arch)")
set_objectdir("$(builddir)/$(mode)/$(plat)_$(arch)/obj")

---------- PLATFORM ----------
-- supported platform
set_allowedplats("windows")
set_allowedarchs("windows|x64")

-- platform specified settings
if is_plat("windows") then 
    add_defines("NOVL_PLAT_WINDOWS")
    set_languages("cxx20")
    set_runtimes("MD")
end

---------- NOVL RUNTIME -------------
target("Novl")
    set_kind("static")
    add_defines("NOVL_RT")

    -- add file to target
    set_pcxxheader("../Novl/src/pch.h")
    add_files("../Novl/**.cpp")

    -- add includes
    add_includedirs("../Novl/src",{public = true})
    
    -- link to target
    -- header only
    libs = {"spdlog"}

    for _, lib in ipairs(libs) do
        add_includedirs(string.format("../Libs/%s/include",lib))
    end

    -- static
    libs = {"glad","glfw3","Jolt","ImGui","freetype"}

    for _, lib in ipairs(libs) do
        add_includedirs(string.format("../Libs/%s/include",lib))
        add_linkdirs(string.format("../Libs/%s/bin/$(plat)/$(arch)",lib))
        add_links(lib)
    end
    
    -- shared
    libs = {"fmod"}


    for _, lib in ipairs(libs) do
        add_includedirs(string.format("../Libs/%s/include",lib))
        add_linkdirs(string.format("../Libs/%s/bin/$(plat)/$(arch)",lib))
        add_links(string.format("%sdll",lib))

        after_build(function(target)
            os.cp(string.format("../Libs/%s/bin/$(plat)/$(arch)/%s.dll",lib,lib),"$(builddir)/$(mode)/$(plat)_$(arch)")
        end)
    end

    -- platform related
    if is_plat("windows") then 
        add_syslinks("opengl32","user32","Gdi32","Shell32")
    end 

    -- Third party related defines
    add_defines("JPH_OBJECT_STREAM")

target_end()

---------- NOVL EDITOR --------------
target("Novl Editor")
    add_deps("Novl")
    set_kind("binary")
    add_defines("NOVL_EDT")

    -- add file to target
    set_pcxxheader("../Novl/src/pch.h")
    add_files("../NovlEditor/**.cpp")

    -- add includes
    add_includedirs("../NovlEditor/src")
    
    -- link to target
    -- header only
    libs = {"spdlog"}

    for _, lib in ipairs(libs) do
        add_includedirs(string.format("../Libs/%s/include",lib))
    end

    -- static
    libs = {"glfw3","ImGui","freetype"}

    for _, lib in ipairs(libs) do
        add_includedirs(string.format("../Libs/%s/include",lib))
        add_linkdirs(string.format("../Libs/%s/bin/$(plat)/$(arch)",lib))
        add_links(lib)
    end
    
    -- shared
    libs = {}

    for _, lib in ipairs(libs) do
        add_includedirs(string.format("../Libs/%s/include",lib))
        add_linkdirs(string.format("../Libs/%s/bin/$(plat)/$(arch)",lib))
        add_links(string.format("%sdll",lib))

        after_build(function(target)
            os.cp(string.format("../Libs/%s/bin/$(plat)/$(arch)/%s.dll",lib,lib),"$(builddir)/$(mode)/$(plat)_$(arch)")
        end)
    end

    -- platform related
    if is_plat("windows") then 
        add_syslinks("opengl32","user32","Gdi32","Shell32")
    end 
    
target_end()