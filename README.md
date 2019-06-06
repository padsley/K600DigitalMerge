# K600DigitalMerge
Updated and proper version for merging the K600 VME and digital DAQs for coincidence data with the K600

To compile, you must have ROOT installed and working - but not the version from Macports (if you're on a Mac) but properly.

To check, do "echo $ROOTSYS" and see what the output is. If you see nothing, then you don't have a working ROOT installation.

To compile: `g++ K600DigitalMerge.cpp -o K600DigitalMerge \`root-config --cflags --libs\``

To run: `./K600DigitalMerge <filename for VME DAQ> <filename for digital DAQ> <verbosity setting - 1 is verbose 2 is very verbose, anything else is false>`

In theory you shouldn't need to look at any verbosity option except 0. Hopefully.

So, for example, you run command may look like: ./K600DigitalMerge sorted00365.root runBaGeL_365-tree.root 1

If you try to run the code with the wrong number of arguments then it won't run.

Now, I've tested this with a couple of files and it seems to work fairly well if not perfectly. However, it's possible that some things may need to change in the code. For example, the limit for the TAC differences or the number of skips in either direction to look over for good events.

You can change both of these parameters along with the TAC rescaling parameters in the header file. If you do change them, you need to recompile the code before running it again.
