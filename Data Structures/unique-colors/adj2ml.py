#!/usr/bin/env python

""" Adjancecy list to GraphML converter

Long Description
"""

import sys
import argparse
import networkx as nx

__author__ = "Albert Farres"
__copyright__ = "Copyright 2018, Albert Farres"
#__credits__ = [""]
__license__ = "MIT"
__version__ = "0.0.1"
__maintainer__ = "Albert Farres"
__email__ = "albertfc@gmail.com"
__status__ = "Development"

debug = False

def get_args( ):
	parser = argparse.ArgumentParser( description="Adjancecy list to GraphML converter." )
	parser.add_argument( "-i", "--in-file", help="Input file.", type=argparse.FileType( 'r' ), default=sys.stdin )
	parser.add_argument( "-o", "--out-file", help="Output file. Default stdout.", type=argparse.FileType( 'w' ), default=sys.stdout )
	parser.add_argument(  "--debug", action="store_true" )
	return parser.parse_args( )

def main( args ):
	args.in_file.readline()
	#colors = map( int, args.in_file.readline().split() )
	colors = args.in_file.readline().split()

	G = nx.read_adjlist( args.in_file )

	colors_dict = {}
	idx = 1
	for c in colors:
		colors_dict[str(idx)] = {'calor': c}
		idx += 1
	nx.set_node_attributes( G, colors_dict )

	nx.write_graphml( G, args.out_file )

if __name__=='__main__':
	args = get_args( )
	debug = args.debug
	if debug:
		print args
	main( args )

