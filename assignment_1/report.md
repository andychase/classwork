Andy Chase  
Project #0  

## Machine ran on

2015 MacBook
Processor Name:	Intel Core M  
Processor Speed:	1.1 GHz  
Number of Processors:	1  
Total Number of Cores:	2  
(Hyper-threaded cores):	4

## Results

Paramaters:

	NUMT            4
	ARRAYSIZE       100000000
	NUMTRIES        20

Result:  

![](result.pdf)

## Behavior

Because my machine only has two phyical cores, the biggest speedup was from 1 to 2. The hyperthreading feature on the Intel processor may have helped from 2 to 3, but from 3 to 4 I think the context switches and other activity on the machine overwhelmed any possible performance benefit.