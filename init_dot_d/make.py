''' Build the desktop version of this sketch.'''

import pyke as p

compile = p.CompilePhase({
    'language': 'c++',
    'language_version': '20',
    'src_dir': 'src',
    'sources': [
        'animator.cpp',
        'bitmaps_8x16.cpp',
        'colors.cpp',
        'display.cpp',
        'system-linux_terminal.cpp',
        'system.cpp'
    ],
    'include_dirs': [
        'include',
    ]
})

link = p.LinkToExePhase({
    'name': 'init_dot_d-term',
}, compile)

#link = p.LinkToExePhase({
#    'name': 'init_dot_d-arduino',
#}, compile)

p.get_main_phase().depend_on(link)

