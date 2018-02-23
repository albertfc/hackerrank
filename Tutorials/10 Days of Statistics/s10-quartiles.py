#!/usr/bin/env python3

""" Calculates quartiles

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
	values_len = len( values )

	values.sort()
	log.dbg( ' '.join(str(v) for v in values) )

	q2_idx = int( values_len / 2 )
	log.dbg( q2_idx )
	q2, q3_ini = (values[q2_idx], q2_idx + 1) if values_len % 2 == 1 else ((values[q2_idx - 1] + values[q2_idx]) / 2, q2_idx)

	q1_len = len( values[0:q2_idx] )
	q1_idx = int( q1_len / 2 )
	q1 = values[q1_idx] if q1_len % 2 == 1 else (values[q1_idx - 1] + values[q1_idx]) / 2

	q3_len = len( values[q3_ini:] )
	q3_idx = q3_ini + int( q3_len / 2 )
	q3 = values[q3_idx] if q3_len % 2 == 1 else (values[q3_idx - 1] + values[q3_idx]) / 2

	log.msg( int( q1 ) )
	log.msg( int( q2 ) )
	log.msg( int( q3 ) )


def get_args( ):
	parser = argparse.ArgumentParser( description="Calculates quartiles" )
	parser.add_argument( "-i", "--in-file", help="Input file. Default stdin", type=argparse.FileType( 'r' ), default=sys.stdin )
	parser.add_argument( "-o", "--out-file", help="Output file. Default stdout.", type=argparse.FileType( 'w' ), default=sys.stdout )
	parser.add_argument(  "--debug", action="store_true" )
	return parser.parse_args( )


if __name__ == '__main__':
	args = get_args( )
	log.debug = args.debug
	log.dbg( args )

	main( args )
