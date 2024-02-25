# SPDX-FileCopyrightText: Copyright 2024 Vitaliy Zarubin <keygenqt@gmail.com>
# SPDX-License-Identifier: MIT
import os


def is_active():
    return True


def get_name():
    return "Aurora OS"


def can_build():
    if os.name != "auroraos":
        return False
    return True


def get_opts():
    from SCons.Variables import PathVariable
    return [
        PathVariable(
            'psdk',
            help='Where Aurora Platform SDK installed',
            default=os.environ['PSDK_DIR'],
            validator=PathVariable.PathIsDir(),
        )
    ]


def get_flags():
    return [

    ]


def configure(env):
    supported_arches = ["x86_64", "arm32", "arm64"]
