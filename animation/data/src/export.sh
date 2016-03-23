#!/usr/bin/bash
if [[ -z $1 ]]; then
	echo "Small program using inkscape to export svg to png into ../img dir"
	echo "usage: $0 width"
	exit 1
fi
for i in *.svg; do
	# -C: page (canvas ?), -w: width, -e: export to png
	inkscape -C -w $1 -e=${i/%svg/png} $i
	mv ${i/%svg/png} ../img
done
