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

    if not os.environ['PSDK_DIR']:
        print("Not found Aurora Platform SDK environment variable.")

    pkgconf_error = os.system("pkg-config --version > /dev/null")
    if pkgconf_error:
        print("Error: pkg-config not found. Aborting.")
        return False

    return True


def get_opts():
    return [

    ]


def get_flags():
    return [

    ]


def configure(env):
    supported_arches = ["x86_64", "arm32", "arm64"]
