#!/bin/bash

# GNU awk manual https://www.gnu.org/software/gawk/manual/html_node/index.html
# AWK cheatsheet at https://gist.github.com/Rafe/3102414qaq


# Remove the last column:
# cut -d, -f11 --complement worldcities.csv > worldcities_modified.csv

# For stripping the apostrophe from fields and creating a POINT, awk can be used:
awk '{FS="\" *, *\"";OFS=";"}NR > 1{for (i=NF; i>0; i--) gsub(/^\"|\"$/,"",$i);point="("$3","$4")";print $1,$2,point,$5,$6,$7,$8,$9,$10}' worldcities.csv  > worldcities_modified.csv