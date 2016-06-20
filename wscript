#! /usr/bin/env python
# encoding: utf-8

import waflib.extras.wurf_options

APPNAME = 'type-storage'
VERSION = '2.1.0'


def options(opt):

    opt.load('wurf_common_tools')


def resolve(ctx):

    import waflib.extras.wurf_dependency_resolve as resolve

    ctx.load('wurf_common_tools')

    ctx.add_dependency(resolve.ResolveVersion(
        name='waf-tools',
        git_repository='github.com/steinwurf/waf-tools.git',
        major=3))

    if ctx.is_toplevel():

        ctx.add_dependency(resolve.ResolveVersion(
            name='gtest',
            git_repository='github.com/steinwurf/gtest.git',
            major=3))


def configure(conf):

    # conf.load('python')
    conf.load("wurf_common_tools")


def build(bld):

    bld.load("wurf_common_tools")

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
