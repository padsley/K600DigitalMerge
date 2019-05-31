# K600DigitalMerge
Updated and proper version for merging the K600 VME and digital DAQs for coincidence data with the K600

To compile, you must have ROOT installed and working - but not the version from Macports (if you're on a Mac) but properly.

To check, do "echo $ROOTSYS" and see what the output is. If you see nothing, then you don't have a working ROOT installation.

To compile: g++ K600DigitalMerge.cpp -o K600DigitalMerge -I/path/to/k600analyser `root-config --cflags --libs`

To run: ./K600DigitalMerge <filename for VME DAQ> <filename for digital DAQ> <verbosity setting - 1 is verbose, anything else is false>
  
So, for example, you run command may look like: ./K600DigitalMerge sorted00365.root runBaGeL_365-tree.root 1

If you try to run the code with the wrong number of arguments then it won't run.
