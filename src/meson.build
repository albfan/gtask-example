gtask_example_sources = [
  'main.c',
  'gtask-example-window.c',
]

gtask_example_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
]

gnome = import('gnome')

gtask_example_sources += gnome.compile_resources('gtask-example-resources',
  'gtask-example.gresource.xml',
  c_name: 'gtask_example'
)

executable('gtask-example', gtask_example_sources,

  dependencies: gtask_example_deps,
  install: true,
)
