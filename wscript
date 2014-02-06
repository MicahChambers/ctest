#!/bin/env python3
from waflib.Utils import subprocess
import os
from waflib import Options, Node, Build, Configure
import re

out = 'build'

def configure(conf):
	join = os.path.join
	isabs = os.path.isabs
	abspath = os.path.abspath
	
	opts = vars(conf.options)
	conf.load('compiler_c compiler_cxx python')
	env = conf.env

	############################### 
	# Basic Compiler Configuration
	############################### 
	conf.env.RPATH = []
	if opts['enable_rpath'] or opts['enable_install_rpath']:
		conf.env.RPATH.append(abspath(join(conf.env.PREFIX, 'lib')))
	
	conf.env.DEFINES = ['AE_CPU=AE_INTEL', 'VCL_CAN_STATIC_CONST_INIT_FLOAT=0', 'VCL_CAN_STATIC_CONST_INIT_INT=0']
	conf.env.CXXFLAGS = ['-std=c++11']
	if opts['profile']:
		conf.env.DEFINES.append('DEBUG=1')
		conf.env.CXXFLAGS.extend(['-Wall', '-Wextra','-g', '-pg'])
		conf.env.LINKFLAGS = ['-pg']
	elif opts['debug']:
		conf.env.DEFINES.append('DEBUG=1')
		conf.env.CXXFLAGS.extend(['-Wall', '-Wextra','-g'])
	else:
		conf.env.DEFINES.append('NDEBUG=1')
		conf.env.CXXFLAGS.extend(['-O3', 'Wall'])
	
	conf.check(header_name='stdio.h', features='cxx cxxprogram', mandatory=True)
	conf.check_cfg(package='zlib', mandatory=True)

def options(ctx):
	ctx.load('compiler_c compiler_cxx')

	gr = ctx.get_option_group('configure options')
	
	gr.add_option('--enable-rpath', action='store_true', default = False, help = 'Set RPATH to build/install dirs')
	gr.add_option('--enable-install-rpath', action='store_true', default = False, help = 'Set RPATH to install dir only')
	
	gr.add_option('--debug', action='store_true', default = False, help = 'Build with debug flags')
	gr.add_option('--profile', action='store_true', default = False, help = 'Build with debug and profiler flags')
	gr.add_option('--release', action='store_true', default = False, help = 'Build with compiler optimizations')
	
def gitversion():
	if not os.path.isdir(".git"):
		print("This does not appear to be a Git repository.")
		return
	try:
		p = subprocess.Popen(["git", "describe", "--tags", "--dirty", "--always"],
					stdout=subprocess.PIPE)
	except EnvironmentError:
		print("unable to run git")
		return "unknown"
	stdout = p.communicate()[0]
	if p.returncode != 0:
		print("unable to run gitalone")
		return "unknown"
	# we use tags like "python-ecdsa-0.5", so strip the prefix
	return stdout.decode('utf-8').strip()

def build(bld):
	for f in 'array copy zero bspline graph sinc linesearch goldensearch'.split(' '):
		bld.program(source=f+'.cpp', target=f)

	bld.shlib(target='plot', source='plot.cpp tga.cpp')
	bld.program(target='bspline_regularize', source='bspline_regularize.cpp plot.cpp tga.cpp')
	bld.program(target='plottest', source='plottest.cpp', use='plot')
	bld.program(target='gradtest', source='gradtest.cpp', use='plot')
	bld.program(target='lanczos', source='lanczos.cpp')
	bld.program(target='hash', source='hash.cpp')
	bld.program(target='sort', source='sort.cpp')
	bld.program(target='iter', source='iter.cpp')
	bld.program(target='round_factor', source='round_factor.cpp')
	bld.program(target='math', source='math.cpp mathparse.cpp')
	bld.program(target='bind', source='bind.cpp')
#	bld.shlib(target='template', source='template_shared_object.cpp')
#	bld.program(target='template_user', source=' template_user.cpp', use='template')

