Andy Chase  
Project #4

## Machine ran on

2015 MacBook
Processor Name:	Intel Core M  
Processor Speed:	1.1 GHz  
Number of Processors:	1  
Total Number of Cores:	2  
(Hyper-threaded cores):	4

# Show the table and graph

![](chart.png)


# What patterns are you seeing in the speedups?

The speed up starts high but drops to below 4.0.

# Are they consistent across a variety of array sizes?

Nope, the speed up drops in paces as the array size increases.

# Why or why not do you think?

They are not, but the speed up does cap out at just under 4.0. This is possibly because the standard multiplication code is slow.

# Would you get a speed-up of < 4.0 or > 4.0?

I'd expect a speed-up below 4.0. 4.0 would be the absolute maximum, but if any reason the SIMD instruction set was slower, the total performance might be lower then 4.0.