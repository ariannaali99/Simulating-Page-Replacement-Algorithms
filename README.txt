# ---------------------------------------------------------------------------- #
#                 AUTHORS: Arianna Ali & Jhun-Thomas Calahatian                #
# ---------------------------------------------------------------------------- #

COP 4600 Project 2 - Measuring the Performance of Page Replacement Algorithms on Real Traces

# ---------------------------------------------------------------------------- #
#                                HOW TO COMPILE                                #
# ---------------------------------------------------------------------------- #

To compile the program, there are two options:

1) Use the command "make" and it will compile all the files and create a memsim executable

Example 1: Open a terminal in the folder containing all the files and run: make

Example 2: If using MinGW, open a terminal in the folder contianing all the files and run: mingw32-make.exe
	Example 2 NOTE: Ensure your PATH to MinGW or other compiler is set up.

2) Open a terminal in the folder containing all the files and run the following below:

g++ memsim.cpp utility.hpp dataStructures.hpp policies.hpp policies.cpp

# ---------------------------------------------------------------------------- #
#                                  HOW TO RUN                                  #
# ---------------------------------------------------------------------------- #

To run the memsim executable program:

1) Open a terminal in the folder containing all the files

2) In the terminal, type and run the following:
	
	2a) Using the FIFO or LRU page replacement algorithms:
	
		./memsim <tracefile> <nframes> <lru|fifo|vms> <debug|quiet>
		
	2b) Using the VMS or Segmented-FIFO page replacement algorithm where percentage is required:
	
		./memsim <tracefile> <nframes> <lru|fifo|vms> <p> <debug|quiet>
		
	where <parameters> are
		
		<tracefile>: The .trace file to analyze
		
		<nframes>: The number of memory frames
		
		<lru|fifo|vms>: (Choose only one) Page replacement algorithm options
		
		<p>: (To be used with VMS page replacement algorithm) Percentage of total program memory in secondary buffer
		
		<debug|quiet>: (Choose only one) Option for program to output more debug related information. Typically run "quiet".

# ---------------------------------------------------------------------------- #
#                                   EXAMPLES                                   #
# ---------------------------------------------------------------------------- #

Example 1, FIFO utilizing quiet)

./memsim bzip.trace 64 fifo quiet

== Information ==
Total Memory Frames: 64
Events in Trace: 1000000

=== FIFO ===
Total Disk Reads: 1467
Total Disk Writes: 514
Time Elapsed = 2070 ms

Example 2, LRU utilizing quiet)

./memsim bzip.trace 64 lru quiet

== Information ==
Total Memory Frames: 64
Events in Trace: 1000000

=== LRU ===
Total Disk Reads: 1264
Total Disk Writes: 420
Time elapsed = 1375 ms

Example 3, VMS utilizing debug)

./memsim bzip.trace 64 vms 50 debug

== Information ==
Trace File: bzip.trace
Total Memory Frames: 64
Events in Trace: 1000000
Policy: vms
Percentage: 50
Debug/Quiet: debug

VMS Extra Information:
> Percentage (Decimal): 0.5
> Primary Buffer Size: 32
> Secondary Buffer Size: 32

=== VMS ===
Total Disk Reads: 1290
Total Disk Writes: 427
Total Hits: 998712
Time Elapsed = 454 ms