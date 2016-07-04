---
title:  "Tree and SHA1 into Json"
tags:
  - code_review
  - short
  - project_notebook
date: 2016-05-14
published: true

author: Nathan Genetzky

layout: single
---

I needed a quicker way to reference the files in the projects I am currently
working on or submitting for archive. After looking only at some forums I was
able to quickly (~1 hour) write the code to do what I needed.

I used recursion to iterate into the sub directories. I used python dicts
(associative maps) to hold the data for each directory or file. I used a function
written by someone else to generate the sha1 hash.

[archive_tree.py][1]
[json_tree.py][2]

[1]: https://github.com/NGenetzky/project_notebook/blob/5d87437ec597a112eb6b72e5338060424d27885b/2016/05/14/json_tree.py
[2]: https://github.com/NGenetzky/project_notebook/blob/5d87437ec597a112eb6b72e5338060424d27885b/2016/05/14/json_tree.py
