project(
  'cppdict',
  'cpp',
  version : '0.0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'],
  license : 'GPL3'
)

cppdict_dep = declare_dependency(include_directories: include_directories('include'))
catch_dep = dependency('catch2-with-main', version:'>3.0.0', required : true)

install_headers(['./include/dict.hpp'], subdir : 'cppdict')

foreach test:['basic_dict_ops','stl_compatibility']
    exe = executable(test,'test/'+test+'.cpp',
                    dependencies:[cppdict_dep, catch_dep],
                    cpp_args : '-DCATCH_CONFIG_NO_POSIX_SIGNALS',
                    include_directories: include_directories('test'),
                    install: false
                    )
    test(test, exe)
endforeach

demo1 = executable('demo1','examples/demo1.cpp',
                dependencies:[cppdict_dep],
                install: false
                )

demo_visitor = executable('demo_visitor','examples/visitor.cpp',
                dependencies:[cppdict_dep],
                install: false
                )
