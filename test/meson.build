test_sources = [
  'test_main.cpp',
  'stack_fixed_rt_test.cpp'
]

catch_dep = dependency('catch')

testexe = executable(
  'testexe',
  test_sources,
  include_directories : kx_container_includes,
  dependencies        : catch_dep
)

test('kx-container-test', testexe)
