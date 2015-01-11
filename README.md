losm
====

A library to manage OSM Files. First, a python converter is included, which converts an OSM file to a collection of files in a very simple format. Also, C++ code is provided which loads the files as a weighted graph.

How To Use
----------

1. Go to http://www.openstreetmap.org and center the desired location in the window.
2. Click the "Export" button on the top left, then the "Export" button on the far left (once it appears).
3. Save the "???.osm" file.
4. Run the command "python losm_converter.py ???.osm <desired output prefix>"

