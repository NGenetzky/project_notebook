#!/usr/bin/env bash

if [ -z "$1" ]; then
  echo "Usage: provide a title argument."
  exit -1
else
  title="$@"
fi

d=$(date +"%Y-%m-%d")

slug=$(echo $title | tr '[:upper:]' '[:lower:]' | tr '[:space:]' '-')
slug="${slug:0:${#slug}-1}"

dir="."
filename="$d-$slug.md"
post="$dir/$filename"

body=""
read -d '' body <<EOF
---
title: $title
tags:
  - project_notebook
date: $d
slug: $slug
published: false
author: Nathan Genetzky
layout: single
---
EOF

echo "$body" > $post
