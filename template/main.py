#!/usr/bin/env python3

"""Skeleton for hackerrank

Long Description
"""
__author__ = "Albert Farres"
__copyright__ = "Copyright 2022"
#__credits__ = [""]
__license__ = "MIT"
__version__ = "0.0.1"
__maintainer__ = "Albert Farres"
__email__ = "albertfc@gmail.com"
__status__ = "Development"

import argparse
import sys
from inspect import currentframe, getframeinfo


class log:
	debug = False

	@staticmethod
	def dbg( msg ):
		if log.debug:
			frame = currentframe().f_back
			filename = getframeinfo(frame).filename
			print( "DEBUG %s:%03d -- %s" % (filename, frame.f_lineno, msg), flush=True )

	@staticmethod
	def msg( msg ):
		print( msg, flush=True )

	@staticmethod
	def msg_noendl( msg ):
		print( msg, end='', flush=True )


def get_args( ):
	parser = argparse.ArgumentParser( description="Skeleton for hackerrank." )
	parser.add_argument( "-i", "--in-file", help="Input file. Default stdin.", type=argparse.FileType( 'r' ), default=sys.stdin )
	parser.add_argument( "-o", "--out-file", help="Output file. Default stdout.", type=argparse.FileType( 'w' ), default=sys.stdout )
	parser.add_argument(  "--debug", action="store_true" )
	return parser.parse_args( )


def run( args ):
	"""
	Run application.

	args -- arguments
	"""


if __name__ == '__main__':
	args = get_args( )
	log.debug = args.debug
	log.dbg( args )
	run( args )
