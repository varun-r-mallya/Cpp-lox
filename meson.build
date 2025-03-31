project('cpplox', 'cpp',
        version : '1.0.0',
        default_options : ['warning_level=3', 'cpp_std=c++20', 'optimization=0'])

src_files = ['src/main.cpp', 'src/lox.cpp', 'src/scanner.cpp', 'src/token.cpp']

#inc_dirs = include_directories('src/include')

cpplox = executable('cpplox', src_files, install : false,
#                    include_directories : inc_dirs
)

test('test', cpplox)