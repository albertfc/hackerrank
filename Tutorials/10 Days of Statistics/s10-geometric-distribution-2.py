#!/usr/bin/env python3

""" s10-geometric-distribution-2

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


try:
	import scipy.special

	def nCr( n, r ):
		return scipy.special.comb( n, r )

except ImportError:
	import math

	def nCr( n, r ):
		f = math.factorial
		return f(n) // f(r) // f(n - r)


def nbinom( x, n, p ):
	return nCr( n - 1, x - 1 ) * p**x * (1 - p)**(n - x)


def main( args ):
	p = 1. / 3.
	res = 0.
	for n in range(1, 6):
		tmp = nbinom( 1, n, p )
		res += tmp
		log.dbg( "{:.3f}".format( tmp ) )

	log.msg( "{:.3f}".format( res ) )


def get_args( ):
	parser = argparse.ArgumentParser( description="s10-geometric-distribution-2" )
	parser.add_argument(  "--debug", action="store_true" )
	return parser.parse_args( )


if __name__ == '__main__':
	args = get_args( )
	log.debug = args.debug
	log.dbg( args )

	main( args )