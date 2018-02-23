#!/usr/bin/env python3

""" Calculates mean, median and mode.

Given an array of integers, calculate and print the respective mean, median,
and mode on separate lines. If your array contains more than one modal value,
choose the numerically smallest one.  """

import sys
import argparse
from inspect import currentframe, getframeinfo

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
	log.msg( "{:.1f}".format( mean ) )

	# median
	values.sort()
	median_idx = int( values_len / 2 ) - 1
	log.dbg( median_idx )
	median = values[median_idx] if values_len % 2 == 1 else (values[median_idx] + values[median_idx + 1]) / 2
	log.msg( "{:.1f}".format( median ) )

	# mode
	log.dbg( ' '.join(str(v) for v in values) )
	histogram = {}
	for v in values:
		try:
			histogram[v] += 1
		except KeyError:
			histogram[v] = 1
	maxv = 0
	mode = 0
	for k, v in histogram.items():
		if v > maxv:
			maxv, mode = (v, k)
		elif v == maxv and k < mode:
			mode = k
	log.dbg( "{} -- {}".format( v, k ) )
	log.msg( mode )


def get_args( ):
	parser = argparse.ArgumentParser( description="Calculates mean, median and mode" )
	parser.add_argument( "-i", "--in-file", help="Input file. Default stdin", type=argparse.FileType( 'r' ), default=sys.stdin )
	parser.add_argument( "-o", "--out-file", help="Output file. Default stdout.", type=argparse.FileType( 'w' ), default=sys.stdout )
	parser.add_argument(  "--debug", action="store_true" )
	return parser.parse_args( )


if __name__ == '__main__':
	args = get_args( )
	log.debug = args.debug
	log.dbg( args )

	main( args )
