core_inc = include_directories('include')
core_private_inc = include_directories('src')

core_sources = files(
    'src/Events/EventAdapter.cpp',
    'src/UI/Color.cpp',
    'src/Application.cpp',
    'src/Font.cpp',
    'src/FontRegistry.cpp',
    'src/KeyCodeAdapter.cpp',
    'src/Layer.cpp',
    'src/Log.cpp',
    'src/MouseCodeAdapter.cpp',
    'src/Renderer.cpp',
    'src/SpriteLoader.cpp',
    'src/Texture.cpp',
    'src/Timer.cpp',
    'src/Window.cpp',
)

core_lib = static_library(
    'core',
    sources: core_sources,
    include_directories : [core_inc, core_private_inc],
    dependencies : [
        dependency('fmt', fallback : ['fmt', 'fmt_dep']),
        dependency('spdlog', fallback : ['spdlog', 'spdlog_dep'], default_options: ['std_format=disabled']),
        dependency('sdl2', version : '>=2.0.10', fallback : ['sdl2', 'sdl2_dep']),
        dependency('sdl2_image', version : '>=2.0.15', fallback : ['sdl2_image', 'sdl2_image_dep'], default_options: ['test=false']),
        dependency('sdl2_ttf', version : '>=2.0.15', fallback : ['sdl2_ttf', 'sdl2_ttf_dep'], default_options: ['test=false']),
        dependency('nlohmann_json', method: 'cmake')
    ],
    install : true,
    c_pch : 'include/pch.h'
)

core_dep = declare_dependency(
    link_with : core_lib,
    include_directories : core_inc
)