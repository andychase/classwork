Andy Chase  
Project #1

## Machine ran on

2015 MacBook
Processor Name:	Intel Core M  
Processor Speed:	1.1 GHz  
Number of Processors:	1  
Total Number of Cores:	2  
(Hyper-threaded cores):	4

## Actual Volume

The actual volume appears to be 14.0625 units.

Here's the volume converging as NUMS increases:

![](sum_converging.pdf)

The actual difference between the NUMS is shown here:

![](sum_converging_difference.pdf)

As NUMS doubles, the difference between the reported volumes appears to be logrithmically more accurate.

## Performance

![](big_chart.pdf)

\pagebreak

The pattern I see in the speeds is a 2x speed up for 2 threads (my machine has two cores), and then a modest speedup for 4 threads (my machine has 4 virtual cores).

The only "constant" part of the problem would be the reduction of the sums; but that can be made parallel as well using the openmp reduction directive. This means that the problem is fully parallizable (except for the last few sums).

Ignoring the setup computation setups, the parallel fraction is 1/0 or infinate. There is no limit to the maximum speedup obtainable.