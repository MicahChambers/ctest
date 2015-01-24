#!/bin/env python3
from waflib.Utils import subprocess
import os
from waflib import Options, Node, Build, Configure
import re

out = 'build'

def build(bld):
	for f in 'array copy zero bspline graph sinc linesearch goldensearch'.split(' '):
		bld.program(source=f+'.cpp', target=f)

	bld.stlib(target='plot', source='plot.cpp tga.cpp')
	bld.program(target='function_macro', source='function_macro.cpp')
	bld.program(target='timer', source='timer.cpp', use='PTHREAD')
	bld.program(target='gz_test', source='gz_test.cpp', use='ZLIB')
	bld.program(target='atof_test', source='atof_test.cpp')
	bld.program(target='compare_string', source='compare_string.cpp')
	bld.program(target='cast_pointers', source='cast_pointers.cpp')
	bld.program(target='pi', source='pi.cpp')
	bld.program(target='prime_factor', source='prime_factor.cpp')
	bld.program(target='fract_order_test', source='fract_order_test.cpp')
	bld.program(target='bspline_regularize', source='bspline_regularize.cpp plot.cpp tga.cpp')
	bld.program(target='plottest', source='plottest.cpp', use='plot')
	bld.program(target='gradtest', source='gradtest.cpp', use='plot')
	bld.program(target='kerntest', source='kerntest.cpp', use='plot')
	bld.program(target='stack_pass', source='stack_pass.cpp')
	bld.program(target='pair', source='pair.cpp')
	bld.program(target='init_list', source='init_list.cpp')
	bld.program(target='ostream', source='ostream.cpp')
	bld.program(target='matrix', source='matrix.cpp')
	bld.program(target='combinations', source='combinations.cpp')
	bld.program(target='function_pointer', source='function_pointer.cpp')
	bld.program(target='lanczos', source='lanczos.cpp')
	bld.program(target='hash', source='hash.cpp')
	bld.program(target='inherit', source='inherit.cpp')
	bld.program(target='sort', source='sort.cpp')
	bld.program(target='round_factor', source='round_factor.cpp')
	bld.program(target='math', source='math.cpp mathparse.cpp')
	bld.program(target='modulus', source='modulus.cpp')
	bld.program(target='bind', source='bind.cpp')
	#bld.program(target='case2', source='case2.cpp')
	bld.program(target='rotate', source='rotate.cpp')
	bld.program(target='shears', source='shears.cpp')
	bld.program(target='fmod', source='fmod.cpp')
	bld.program(target='lambda', source='lambda.cpp')
	bld.shlib(target='template2', source='template2.cpp')
#	bld.shlib(target='template', source='template_shared_object.cpp')
#	bld.program(target='template_user', source=' template_user.cpp', use='template')
	bld.program(target='iter', source='iter.cpp')
	bld.program(target='vector_expand', source='vector_expand.cpp')
	bld.program(target='kernel_iterator', source='kernel_iterator.cpp kernel_iterator_test.cpp')
	bld.program(target='slicer', source='slicer.cpp')
	bld.program(target='slicer_template', source='slicer_template.cpp')
	bld.program(target='gzip', source='gzip.cpp', use='ZLIB')
	bld.program(target='typetest', source='typetest.cpp')
	bld.program(target='complex_test', source='complex_test.cpp')
	bld.program(target='nan', source='nan.cpp')
	bld.program(target='istringstream', source='istringstream.cpp')
	bld.program(target='regex_test', source='regex.cpp')

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
		conf.env.CXXFLAGS.extend(['-Wall', '-Wextra', '-Wno-sign-compare', '-g', '-pg'])
		conf.env.LINKFLAGS = ['-pg']
	elif opts['debug']:
		conf.env.DEFINES.append('DEBUG=1')
		conf.env.CXXFLAGS.extend(['-Wall', '-Wextra', '-Wno-sign-compare', '-g'])
	else:
		conf.env.DEFINES.append('NDEBUG=1')
		conf.env.CXXFLAGS.extend(['-O3', '-Wall', '-Wno-sign-compare'])
	
	conf.check(header_name='stdio.h', features='cxx cxxprogram', mandatory=True)
	conf.check(header_name='thread', features='cxx cxxprogram', mandatory=True, lib=['pthread'], uselib_store='PTHREAD')
	conf.check_cfg(package='zlib', userlib_store='ZLIB', mandatory=True, args=['--cflags', '--libs'])

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

