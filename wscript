#! /usr/bin/env python
# encoding: utf-8

APPNAME = 'type-storage'
VERSION = '3.0.0'


def build(bld):

    bld.env.append_unique(
        'DEFINES_STEINWURF_VERSION',
        'STEINWURF_TYPE_STORAGE_VERSION="{}"'.format(VERSION))

    # Export own includes
    bld(name='type_storage_includes',
        includes='./src',
        export_includes='./src')

    if bld.is_toplevel():
        bld.recurse('test')

        bld.recurse('examples')
