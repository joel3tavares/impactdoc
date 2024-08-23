#!/bin/bash

shopt -s lastpipe

src=$CI_COMMIT_SHA
target=$CI_MERGE_REQUEST_DIFF_BASE_SHA

git fetch --depth 1 origin $target

files=$(git diff --name-only $target $src -- '*.php')

for file in $files; do
        modifiedLines=()

        git diff -U0 $target $src -- $file | grep '^@@' | sed -n 's/.*+\([0-9]\+\)\(,[0-9]\+\)\?.*/\1 \2/p' | sed 's/,//' | while read -r line; do
                lineNumbers=($line)
                if [ ${#lineNumbers[@]} -eq 1 ]; then
                        modifiedLines+=(${lineNumbers[0]})
                else
                        if [ ${lineNumbers[1]} -eq 0 ]; then
                                modifiedLines+=(${lineNumbers[0]})
                        else
				startLine=${lineNumbers[0]}
				endLine=`expr ${lineNumbers[0]} + ${lineNumbers[1]}`
                                modifiedLines+=(`seq ${startLine} ${endLine}`)
                        fi
                fi
        done

  	impactdoc "$file" "${modifiedLines[@]}"
done
