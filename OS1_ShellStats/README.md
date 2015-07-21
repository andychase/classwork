# OS1: Shell Stats

The goal of this assigment was to make a shell script that could generate basic
average and median out of tab-seperated-values files.

	% stats -rows test_file
	 Average Median
	 1       1
	 5       5
	 7       7
	 5       6
	 3       3
	 6       6

-

	% cat test_file | stats –c
	 Averages:
	 5       4       5       5       4
	 Medians:
	 6       4       4       7       5
