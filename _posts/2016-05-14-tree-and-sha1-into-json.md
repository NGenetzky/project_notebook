---
author: Nathan Genetzky
date: '2016-05-14'
filename: 2016-05-14-tree-and-sha1-into-json.md
layout: single
published: true
slug: tree-and-sha1-into-json
tags:
- tags
- project_notebook
title: Tree and SHA1 into Json
---

# Tree and Sha1 into JSON

I needed a quicker way to reference the files in the projects I am currently
working on or submitting for archive. After looking only at some forums I was
able to quickly (~1 hour) write the code to do what I needed.

I used recursion to iterate into the sub directories. I used python dicts
(associative maps) to hold the data for each directory or file. I used a function
written by someone else to generate the sha1 hash.