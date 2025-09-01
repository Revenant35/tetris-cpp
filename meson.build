project('Tetris', 'cpp',
        version : '1.0.0',
        default_options : ['warning_level=3', 'cpp_std=c++20'])

public_inc = include_directories('include')

lib_sources = files(
    'src/Log.cpp',
)

test_sources = files(
    'tests/ExampleTests.cpp',
)

exec_sources = files(
    'src/main.cpp',
)

lib_dependencies = [
    dependency('fmt', fallback : ['fmt', 'fmt_dep']),
    dependency('spdlog', fallback : ['spdlog', 'spdlog_dep'], default_options: ['std_format=disabled']),
    dependency('sdl2', version : '>=2.0.10', fallback : ['sdl2', 'sdl2_dep']),
    dependency('sdl2_ttf', version : '>=2.0.15', fallback : ['sdl2_ttf', 'sdl2_ttf_dep'])
]

test_dependencies = [
    dependency('gtest', fallback : ['gtest', 'gtest_dep']),
    dependency('gtest_main', fallback : ['gtest', 'gtest_main_dep'])
]

libs = static_library('TetrisLib',
                      lib_sources,
                      include_directories : public_inc,
                      dependencies : lib_dependencies,
)

tests = executable(
    'Tests',
    test_sources,
    dependencies : test_dependencies,
    include_directories : public_inc,
    link_with : libs,
)

executable('Tetris',
           [
               lib_sources,
               exec_sources,
           ],
           install : true,
           include_directories : public_inc,
           dependencies : lib_dependencies,
           link_with : libs,
)

test('Tests', tests)
