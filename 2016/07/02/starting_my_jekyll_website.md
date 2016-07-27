---
title:  "Starting my Jekyll Website!"
tags:
  - Jekyll
  - MinimalMistakes
  - project_notebook
date:   2016-07-02
published: true

author: Nathan Genetzky

layout: single
---

I am forking [mmistakes/minimal-mistakes][gh1] to have a prebuilt website theme
that I can put my content in.

## Procedure to setup repo

1. I forked the repo on the github website.
2. Cloned into mm_site
3. Moved existing gh-site to new branch.

```bash
git clone https://github.com/NGenetzky/minimal-mistakes.git mm_site
cd mm_site/
git checkout -b gh-pages origin/gh-pages
git branch mmistakes-pages
```

## Idea to keep website separate from content

I can hopefully keep from getting locked into a particular theme or tool to
display my content.

### Storing content in repository

I would like to keep the website in a repository separate from the repository
that contains the content. I would like to use git submodules to do this.
[@jryio][jryio] wrote a [post][jry] about this.

Limitations:

- content can only contain "\_posts" and pages
- content can not utilize collections (without using symlinks)
- The website repo has to update the submodule when it wants the content updated.

### Storing the website theme in a repository

Another approach would be storing the theme in a submodule. [@lafaria][lafaria]
wrote an article about this
 ([Best practices installing Jekyll theme using git submodules][med1]).
The Plugins, Layouts, and Includes can be handled by the jekyll's config.
The issue arises since the other parts of the theme require symlinks.

## Github page hosting

[Github Pages][gh1] will automatically host a jekyll or static website. A project specific
site is created by putting the website in the "gh-pages" branch, and a user
specific site can be created in a repository named "<username>.github.io" 
(where <username> is replaced). By putting a website in these specific locations
then a page will be hosted at one of the following:
- http(s)://<username>.github.io/<projectname>``
- http(s)://<username>.github.io

### Jekyll website served by Github

Github will build and serve a jekyll project. The advantage of this is an
automatic build. The disadvantage is that it does not support symlinks or
plugins.

### Static website served by Github

Github would also host a static website  This could be the contents of the
 "_site" folder after building a jekyll project. The advantage here is that
that any content that can be made into a static website is acceptable. To be
sure the project is not built with jekyll a ".nojekyll" empty file should be
in the root of the repo.

Advantages:
- Plugins could be used
- Symlinks could be used
Disadvantages:
- Must manually build the project with every update.

## YAML front matter is required for files

Jekyll will process all files that contain front matter. YAML in the front
matter is accessible when using the post/page to create a webpage.

### Scripting with front matter

[Using **sed** to remove front matter.][so1]

```sh
sed '1 { /^---/ { :a N; /\n---/! ba; d }  }' filename

1 {              # in the first line
  /^---/ {       # if it starts with ---
    :a           # jump label for looping
    N            # fetch the next line, append to pattern space
    /\n---/! ba; # if the result does not contain \n--- (that is, if the last
                 # fetched line does not begin with ---), go back to :a
    d            # then delete the whole thing.
   }
 }
                 # otherwise drop off the end here and do the default (print
                 # the line)
```

[Shell Script to create Jekyll posts][jb1] is a script that makes it easier
to create new posts.

[Script to change date on all files modfied in git][so2].

```sh
#!/bin/sh
# Contents of .git/hooks/pre-commit

git diff --cached --name-status | grep "^M" | while read a b; do
  cat $b | sed "/---.*/,/---.*/s/^date:.*$/date: $(date -u "+%Y-%m-%d %T %Z")/" > tmp
  mv tmp $b
  git add $b
done
```



[gh1]: https://github.com/mmistakes/minimal-mistakes
[jryio]: https://twitter.com/jryio
[jry]: http://jry.io/posts/make-your-jekyll-blog-awesome-with-git-submodules/
[lafaria]; https://medium.com/@lafraia
[med1]: https://medium.com/@lafraia/best-practices-installing-jekyll-theme-using-git-submodules-a40a5f7a9edc#.ebqc34s00
[gh1]: https://help.github.com/articles/user-organization-and-project-pages/
[jb1]: http://blog.johanbove.info/blog/2015/07/23/quick-way-of-start-jekyll-posts.html
[so1]: http://stackoverflow.com/a/28222257
[so2]: http://stackoverflow.com/a/33721446
