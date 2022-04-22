#!/usr/bin/env python3
import pandas, sys
import matplotlib.pyplot as plt
import argparse
import copy

def main():
	parser = argparse.ArgumentParser(description='Visualize trj planer output')
	parser.add_argument('-f','--files', metavar='files', nargs='+',
	                    help='Files for plotting')
	parser.add_argument('-d','--delimeter',default = ',',
						help='Delimeter for spliting line')

	args = parser.parse_args()
	files = args.files
	delimeter = args.delimeter




if __name__ == '__main__':
    main()
