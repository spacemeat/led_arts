''' Build the desktop version of this sketch.'''

import pyke as p

compile = p.CompilePhase({
    'language': 'c++',
    'language_version': '20',
    'src_dir': '.',
    'sources': [
        'animator.cpp',
        'display.cpp',
        'rocket.cpp',
        'splash.cpp',
        'terminal.cpp',
        'track.cpp',
        'system.cpp'
    ],
    'include_dirs': [
        '.',
    ]
})

link = p.LinkToExePhase({
    'name': 'mistress',
}, compile)

p.get_main_phase().depend_on(link)
