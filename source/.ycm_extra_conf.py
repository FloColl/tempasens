import os
import ycm_core

flags = [
        '-Wall',
        '-Wextra',
        '-DUSE_CLANG_COMPLETER',
        '-std=c99',
        '-x',
        'c',
        '-isystem',
        '/usr/include/'
         ]

compilation_database_folder = '/home/flo/projects/tempSens/.ycm_extra_conf.py'

