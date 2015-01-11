losm
====

A library to manage OSM Files. First, a python converter is included, which converts an OSM file to a collection of files in a very simple format. Also, C++ code is provided which loads the files as a weighted graph.

How To Use With Lexicographic (PO)MDP Code
------------------------------------------

1. Go to http://www.openstreetmap.org and center the desired location in the window.
2. Click the "Export" button on the top left, then the "Export" button on the far left (once it appears).
3. Save the "\<name of file\>.osm" file.
4. Run the command "python losm_converter.py \<name of file\>.osm \<output prefix\>"
5. Copy all "\<output prefix\>*.dat" files to a "resources" directory and backup the "\<name of file\>.osm" file.
6. Write a script to run the LOSM visualizer in the form below. Then run the script.
7. In the visualizer, you can determine the pair of nodes which form a LOSMState in the (PO)MDP by right clicking. The command line will display the UID of the node, which can be used in the design of (PO)MDPs. This structure is defined in my LMDP and LPOMDP papers.
```
#!/bin/bash
cd ~/Development/losm/losm_visualizer
python losm_visualizer.py 1600 900 0 \<path to resources\>/resources/\<output prefix\> \<path and name of policy file\>
```
