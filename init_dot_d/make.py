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
        'system.cpp',
        'terminal.cpp'
    ],
    'include_dirs': [
        'include',
    ]
})

link = p.LinkToExePhase({
    'name': 'init_dot_d',
}, compile)

p.get_main_phase().depend_on(link)

