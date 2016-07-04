#!/bin/sh
# Contents of .git/hooks/pre-commit

# git diff --cached --name-status                                                \
    # | grep "^M"                                                              \
    # | while read a b; do                                                     \
  # cat $b | sed "/---.*/,/---.*/s/^date:.*$/date: $(date -u "+%Y-%m-%d %T %Z")/" > tmp
  # mv tmp $b
  # git add $b
# done

#Standalone sed scripts
delete='1 { /^---/ { :a N; /\n---/! ba; d }  }'
extract='1 { /^---/ { :a N; /\n---/! ba; p }  }; Q'
extract2='/---.*/,/---.*/ { p } ; d'
remove_date='/^date:.*$/ {d}'
remove_CR="s/\r//"

# Utilize variables
today="$(date -u "+%Y-%m-%d")"
set_date_to_now="s/^date:.*$/date: $today/"
remove_attr_date="/---.*/,/---.*/ { $set_date_to_now ; $remove_CR ; p} ; d"

# Extract yaml front matter
fm=$(cat $1 | sed "$extract" )

# Find the title
title=$(echo "$fm" | sed "s/^title:\s*\"\(.*\)\"/\1/ p ; d")
YYYYMMDD='(19|20)\d\d[- /.](0[1-9]|1[012])[- /.](0[1-9]|[12][0-9]|3[01])'
filedate=$(echo "$fm" | sed "s/^date:\s*\(.*\)$/\1/ p ; d")

if [ -z "$title"  ]; then
    echo "ERROR($1)-Unable to parse title"
fi
if [ -z "$filedate"  ]; then
    echo "ERROR($1)-Unable to parse date"
fi

filename="$filedate-$title"
echo "$filename"

# echo "$fm" > "$1.yml"
# cp "$1" "$1.bak"

# Modifies the date to today.
# content=$(cat $1 | sed "$delete" )
# echo "$fm" | sed "$set_date_to_now" | sed "$remove_CR" > "$1.post"
# echo "$content" | sed "$remove_CR" >> "$1.post"
