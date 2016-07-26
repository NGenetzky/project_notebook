---
author: Nathan Genetzky
date: '2016-07-22'
filename: 2016-07-22-quicker-publishing-from-project-notebook.md
layout: single
published: false
slug: quicker-publishing-from-project-notebook
tags:
- project_notebook
title: Quicker Publishing from Project Notebook
---

I need to automate more parts of the writing and publishing process. First
I need a quick way to create new notes with some good metadata.
I need to have a single script that can be run to move and prepare the files
that should be publicly hosted from my project notebook. The files that should
be publicly hosted should be in a separate branch from the development branch.

## Creating new notes

I wrote a simple bash script that will create a new file with a supplied title.
The date, slug, title, and author are automatically set. The usage is very
simple:

```
jekyll_new_post_now "The Post Title, With or Without Quotes"
```

## Front Matter
The Jekyll front matter is an important part of preparing the file.

I started a bash script to do some simple actions on markdown files. Although
it works for a few minor things it was much to difficult to write in bash.

Instead I wrote a python module to interact with the frontmatter using a
library. I created a class to represent a Jekyll Post. I then wrote two
functions to that were used in the main body to move all files to a particular
directory with a particular name for each file. Meta data was also altered.


## Move files to Public branch

I need a simple script that will:
1. create a directory with the public branch checked out.
2. move all the files with the proper formatting to a public directory.


## Pull New Changes

A script should update the git submodule on the jekyll website.