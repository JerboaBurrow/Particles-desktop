#! /bin/bash

SIZE=128

for asset in *.svg
do
  name="${asset%.*}"
	inkscape -w $SIZE -h $SIZE -o assets/${name}.png $asset
done