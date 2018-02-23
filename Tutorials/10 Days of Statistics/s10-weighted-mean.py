#!/usr/bin/env python3

""" Calculates weighted mean.

"""

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
	values  = list(map( int, args.in_file.readline().split() ))
	weigths = list(map( int, args.in_file.readline().split() ))
	log.dbg( ' '.join(str(v) for v in values) )
	log.dbg( ' '.join(str(v) for v in weigths) )

	total_weights = 0
	weighted_mean = 0
	for v, w in zip( values, weigths ):
		log.dbg( "{} {}".format( v, w) )
		weighted_mean += v * w
		total_weights += w
	weighted_mean /= total_weights

	log.msg( "{:.1f}".format( weighted_mean ) )


def get_args( ):
	parser = argparse.ArgumentParser( description="Calculates weighted mean" )
	parser.add_argument( "-i", "--in-file", help="Input file. Default stdin", type=argparse.FileType( 'r' ), default=sys.stdin )
	parser.add_argument( "-o", "--out-file", help="Output file. Default stdout.", type=argparse.FileType( 'w' ), default=sys.stdout )
	parser.add_argument(  "--debug", action="store_true" )
	return parser.parse_args( )


if __name__ == '__main__':
	args = get_args( )
	log.debug = args.debug
	log.dbg( args )

	main( args )
