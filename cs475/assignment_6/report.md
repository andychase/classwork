Andy Chase  
Project #6

## Machine ran on

2015 MacBook
Processor Name:	Intel Core M  
Processor Speed:	1.1 GHz  
Number of Processors:	1  
Total Number of Cores:	2  
(Hyper-threaded cores):	4

# Part 1 -- Multiplication and Multiplication-Addition

## Graphs

![](chart_1.png)

![](chart_2.png)

![](chart_3.png)

![](chart_4.png)

## What patterns are you seeing in the performance curves?

The curves all go up and hit peaks at different points. For small local work sizes there is a peak
performance point before the performance begins to degrade. This doesn't seem to effect some of the other
local work sizes.

## Why do you think the patterns look this way?

I think for small work sizes the GPU spends a lot of time transferring data across memory layers. It's much faster
for the gpu to keep all of its compute units actively processing data as much time as possible and not waiting
on memory being transferred. For this reason its best to use the largest local work size that your machine supports.

For my machine this was 256 floats.

## What is the performance difference between doing a Multiply and doing a Multiply-Add?

There was slightly different values but overall the performance was the same. I actually got a higher maximum
for the Multiply-Add but I suspect that was just different values resulting from different runs.

Overall the graphs looked very similar.

## What does that mean for the proper use of GPU parallel computing?

GPU parallel computing works well for large global data sizes. Also the local work size has to be
configured well. Certain values don't work as well as others although they all seem to work pretty well.

# Part 2 -- Reduction

## Table and graph

![](chart_5.png)

## What pattern are you seeing in this performance curve?

In general the performance seems to go up as the input array increases, though it does seem to level out.

## Why do you think the pattern looks this way?

I'm not sure. Perhaps there's some setup or caching penalty that larger array sizes seem to overcome.

## What does that mean for the proper use of GPU parallel computing?

GPU Parallel computing is useful for large computations and not as useful for small data set sizes.
