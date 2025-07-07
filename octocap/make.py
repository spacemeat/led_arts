''' Build the desktop version of this sketch.'''

import pyke as p

compile = p.CompilePhase({
    'language': 'c++',
    'language_version': '20',
    'src_dir': '.',
    'sources': [
        'animator.cpp',
        'display.cpp',
        'octopus.cpp',
        'system.cpp',
        'terminal.cpp',
        'effects/crawling_stripe.cpp',
        'effects/effect.cpp',
        'effects/effect_controller.cpp',
        'effects/octopus_effect.cpp'
    ],
    'include_dirs': [
        '.',
    ]
})

link = p.LinkToExePhase({
    'name': 'octocap',
}, compile)

p.get_main_phase().depend_on(link)

