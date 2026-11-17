''' Build the desktop version of this sketch.'''

import pyke as p

compile = p.CompilePhase({
    'language': 'c++',
    'language_version': '20',
    'src_dir': 'src',
    'sources': [
        'system.cpp',
        'main.cpp',
    ],
    'include_dirs': [
        'src',
    ]
})

link = p.LinkToExePhase({
    'name': 'vein',
}, compile)

p.get_main_phase().depend_on(link)

