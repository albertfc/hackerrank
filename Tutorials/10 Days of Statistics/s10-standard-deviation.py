#!/usr/bin/env python3

""" s10-standard-deviation

"""
import sys
import argparse
from inspect import currentframe, getframeinfo
import math

__author__ = "Albert Farres"
__copyright__ = "Copyright 2018, Albert Farres"
# __credits__ = [""]
__license__ = "MIT"
__version__ = "0.0.1"
__maintainer__ = "Albert Farres"
__email__ = "albertfc@gmail.com"
__status__ = "Development"


class log:
	debug = False

	@staticmethod
	def dbg( msg ):
		if log.debug:
			cf = currentframe()
			filename = getframeinfo(cf).filename
			print( "DEBUG %s:%03d -- %s" % (filename, cf.f_back.f_lineno, msg) )

			sys.stdout.flush()

	@staticmethod
	def msg( msg ):
		print( msg, flush=True )

	@staticmethod
	def msg_noendl( msg ):
		print( msg, end='', flush=True )


def main( args ):
	args.in_file.readline()
	values = list(map( int, args.in_file.readline().split() ))
	log.dbg( ' '.join(str(v) for v in values) )

	values_len = len( values )

	# mean
	mean = 0
	for v in values:
		mean += v
	mean /= values_len

	stdev = 0
	for v in values:
		stdev += ( v - mean )**2
	stdev /= values_len
	stdev  = math.sqrt( stdev )

	log.msg( "{:.1f}".format( stdev ) )


def get_args( ):
	parser = argparse.ArgumentParser( description="Calculates standard deviation" )
	parser.add_argument( "-i", "--in-file", help="Input file. Default stdin", type=argparse.FileType( 'r' ), default=sys.stdin )
	parser.add_argument( "-o", "--out-file", help="Output file. Default stdout.", type=argparse.FileType( 'w' ), default=sys.stdout )
	parser.add_argument(  "--debug", action="store_true" )
	return parser.parse_args( )


if __name__ == '__main__':
	args = get_args( )
	log.debug = args.debug
	log.dbg( args )

	main( args )
