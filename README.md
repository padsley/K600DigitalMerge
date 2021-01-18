# K600DigitalMerge
Updated and proper version for merging the K600 VME and digital DAQs for coincidence data with the K600

To compile, you must have ROOT installed and working - but not the version from Macports (if you're on a Mac) but properly.

To check, do "echo $ROOTSYS" and see what the output is. If you see nothing, then you don't have a working ROOT installation.

To compile: ```g++ K600DigitalMerge.cpp -o K600DigitalMerge `root-config --cflags --libs` ```

To run: ```./K600DigitalMerge <filename for VME DAQ> <filename for digital DAQ> <verbosity setting - 1 is verbose 2 is very verbose, anything else is false> <max number of skips>```

In theory you shouldn't need to look at any verbosity option except 0. Hopefully.

For the max number of skips: I suggest that you start with 5 and if you either (a) see the code exit ungracefully complaining about memory errors or (b) the gSkips graph in the output file looks strange* then increase the number of skips by one and try again - repeat this until things look OK. For example, for run 272, skips = 5 is bad but skips = 6 works nicely.

(*I know that that's vague but the theory is that the number of skips should be relatively small and slowly drift during the run and when it loses alignment it tends to suddenly sweep everything off to one side so it's probably best to look for changes in the slope.) 

So, for example, you run command may look like: ./K600DigitalMerge sorted00365.root runBaGeL_365-tree.root 1 6

If you try to run the code with the wrong number of arguments then it won't run but it should print an error message saying "these are the arguments that you should have".

Now, I've tested this with a couple of files and it seems to work fairly well if not perfectly. However, it's possible that some things may need to change in the code. For example, the limit for the TAC differences.

You can change this parameters along with the TAC rescaling parameters in the header file. If you do change them, you need to recompile the code before running it again. The number of skips is read at runtime so you can change that without recompiling.
