core_inc = include_directories('include')

core_sources = files(
    'src/Application.cpp',
    'src/Font.cpp',
    'src/Log.cpp',
    'src/Layer.cpp',
    'src/Renderer.cpp',
    'src/SpriteLoader.cpp',
    'src/Timer.cpp',
    'src/Texture.cpp',
    'src/Window.cpp',
)

core_lib = static_library(
    'core',
    sources: core_sources,
    include_directories : core_inc,
    dependencies : [
        dependency('fmt', fallback : ['fmt', 'fmt_dep']),
        dependency('spdlog', fallback : ['spdlog', 'spdlog_dep'], default_options: ['std_format=disabled']),
        dependency('sdl2', version : '>=2.0.10', fallback : ['sdl2', 'sdl2_dep']),
        dependency('sdl2_image', version : '>=2.0.15', fallback : ['sdl2_image', 'sdl2_image_dep'], default_options: ['test=false']),
        dependency('sdl2_ttf', version : '>=2.0.15', fallback : ['sdl2_ttf', 'sdl2_ttf_dep'], default_options: ['test=false']),
        dependency('nlohmann_json', method: 'cmake')
    ],
    install : true,
)

core_dep = declare_dependency(
    link_with : core_lib,
    include_directories : core_inc
)