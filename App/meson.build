app_sources = files(
    'src/AppLayer.cpp',
    'src/MenuLayer.cpp',
    'src/Game.cpp',
    'src/Main.cpp',
)

app_exe = executable(
    'app',
    sources : app_sources,
    dependencies : [
        core_dep,
        dependency('spdlog', fallback : ['spdlog', 'spdlog_dep'], default_options: ['std_format=disabled']),
        dependency('sdl2', version : '>=2.0.10', fallback : ['sdl2', 'sdl2_dep']),
        dependency('sdl2_image', version : '>=2.0.15', fallback : ['sdl2_image', 'sdl2_image_dep'], default_options: ['test=false']),
        dependency('nlohmann_json', method: 'cmake')
    ],
    install : true
)

