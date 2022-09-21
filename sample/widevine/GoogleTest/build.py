#!/usr/bin/python2
# Copyright 2013 Google Inc. All Rights Reserved.
"""Generates build files and builds the CDM source release."""

import argparse
import imp
import os
import subprocess
import sys

cdm_top = os.path.abspath(os.path.dirname(__file__))

# If gyp has been installed locally in third_party, this will find it.
# Irrelevant if gyp has been installed globally.
sys.path.insert(1, os.path.join(cdm_top, 'third_party'))
import gyp

def IsNinjaInstalled():
  """Determine if ninja is installed."""
  try:
    bit_bucket = open(os.devnull, 'w')
    subprocess.check_call(['ninja', '--version'], stdout=bit_bucket,
                          stderr=bit_bucket)
    return True
  except subprocess.CalledProcessError:
    # Error code returned, probably not the ninja we're looking for.
    return False
  except OSError:
    # No such command found.
    return False


def VerboseSubprocess(args):
  print ' Running: %s' % args
  return subprocess.call(args)


def RunMake(unused_output_path, build_config):
  os.environ['BUILDTYPE'] = build_config
  return VerboseSubprocess(['make', '-C', cdm_top])


def RunNinja(output_path, build_config):
  build_path = os.path.join(output_path, build_config)
  return VerboseSubprocess(['ninja', '-C', build_path])


def RunUnknown(unused_output_path, unused_build_config):
  print 'Cannot automatically build with this generator.'
  print 'Please start the build manually.'
  return 0


def GetBuilder(generator):
  return {
      'make': RunMake,
      'ninja': RunNinja,
  }.get(generator, RunUnknown)


def ImportPlatform(name, shared, static, toolchain, gyp_args):
  """Handles platform-specific setup for the named platform.

  Computes platform-specific paths, sets gyp arguments for platform-specific
  gypis and output paths, imports a platform-specific module, and exports
  platform-specific environment variables.

  Args:
    name: The name of the platform.
    gyp_args: An array of gyp arguments to which this function will append.

  Returns:
    The path to the root of the build output.
  """

  print ' Target Platform: %s' % name

  platforms_path = os.path.join(cdm_top, 'platforms')
  target_path = os.path.join(platforms_path, name)
  platform_gypi_path = os.path.join(target_path, 'settings.gypi')
  output_path = os.path.join(cdm_top, 'out', name)

  gyp_args.append('--include=%s' % platform_gypi_path)
  gyp_args.append('-Goutput_dir=%s' % output_path)

  platform_environment_path = os.path.join(target_path, 'environment.py')
  target = imp.load_source('environment', platform_environment_path)

  if hasattr(target, 'export_variables'):
    for k, v in target.export_variables.iteritems():
      if not os.environ.get(k):
        os.environ[k] = v
        if 'LDFLAGS'==k:
          os.environ[k] += ' -L'
          os.environ[k] += shared
          os.environ[k] += ' -L'
          os.environ[k] += static
        if 'CC'==k:
          os.environ[k] = toolchain + os.environ[k]
        if 'CXX'==k:
          os.environ[k] = toolchain + os.environ[k]
        if 'AR'==k:
          os.environ[k] = toolchain + os.environ[k]
        if 'LD'==k:
          os.environ[k] = toolchain + os.environ[k]
        print ' set %s to %s' % (k, os.environ[k])

  return output_path


def main(args):
  if IsNinjaInstalled():
    default_generator = 'ninja'
  else:
    default_generator = 'make'

  parser = argparse.ArgumentParser()
  parser.add_argument('platform',
                      help='The platform configuration to use (x86-64, ...). '
                      'Should be one of the folder names inside platforms/')
  parser.add_argument('sharedlib',
                      help='the platform of shared lib dir '
                      'should be configure')
  parser.add_argument('staticlib',
                      help='The platform of static lib dir. '
                      'Should be configure')
  parser.add_argument('toolchain',
                      help='The platform of static lib dir. '
                      'Should be configure')
  parser.add_argument('-r', '--release',
                      dest='build_config', default='Debug',
                      action='store_const', const='Release',
                      help='Builds a release build (equivalent to -c Release)')
  parser.add_argument('-c', '--config',
                      dest='build_config', default='Debug',
                      help='Select a build config (Debug, Release). '
                      'Defaults to Debug.')
  parser.add_argument('-g', '--generator', default=default_generator,
                      help='Which build system to use (make, ninja, ...). '
                      'Defaults to ninja when available, make otherwise.')

  options = parser.parse_args(args)

  gyp_args = [
      '--format=%s' % options.generator,
      '--depth=%s' % cdm_top,
      '%s/cdm_unittests.gyp' % cdm_top,
      #'%s/cdm/cdm_unittests_L3.gyp' % cdm_top,
  ]

  output_path = ImportPlatform(options.platform, options.sharedlib, options.staticlib, options.toolchain, gyp_args)

  print ' Running: %s' % (['gyp'] + gyp_args)
  retval = gyp.main(gyp_args)
  if retval != 0:
    return retval

  # The gyp argument --build=xyz only works on newer versions of gyp and
  # ignores the generator flag output_dir (as of 2014-05-28 with ninja).
  # So instead of using --build, we simply invoke the build system ourselves.
  builder = GetBuilder(options.generator)
  return builder(output_path, options.build_config)


if __name__ == '__main__':
  sys.exit(main(sys.argv[1:]))
