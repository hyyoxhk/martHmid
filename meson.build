project('smartHmid',
	'c',
	version: '0.1',
	meson_version: '>= 0.52.1',
	license : 'Commercial',
)

cc = meson.get_compiler('c')

global_args = []
global_args_maybe = [
	'-Wmissing-prototypes',
	'-Wno-unused-parameter',
	'-Wno-shift-negative-value', # required due to Pixman
	'-Wno-missing-field-initializers',
	'-Wno-pedantic',
	'-Wundef',
	'-fvisibility=hidden',
]
foreach a : global_args_maybe
	if cc.has_argument(a)
		global_args += a
	endif
endforeach
add_global_arguments(global_args, language: 'c')

pkgconfig = import('pkgconfig')

dep_libmosquitto = dependency('libmosquitto', version: '>= 2.0.11')
dep_sqlite3 = dependency('sqlite3', version: '>= 3.37.2')

deps = [
	dep_libmosquitto,
	dep_sqlite3,
]

inc = include_directories('.')

srcs = [
	'mosq.c',
	'main.c',
	'pctl.c'
]

executable(
	'smartHmid',
	sources: srcs,
	#version: meson.project_version(),
	dependencies: deps, 
	include_directories : inc,
	install: true
)
