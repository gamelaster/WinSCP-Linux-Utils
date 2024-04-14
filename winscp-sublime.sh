#!/bin/bash

FILE=$1

# Remove C: prefix
FILE=${FILE:2}

# Replace \ to /
FILE=${FILE//\\//}

# Open file in Sublime
subl $FILE