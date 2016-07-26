---
author: Nathan Genetzky
date: '2016-07-04'
filename: 2016-07-04-working-on-web-view-of-notes.md
layout: single
published: false
slug: working-on-web-view-of-notes
tags:
- project_notebook
title: Working on Web View of Notes
---

Working on improving the presentation of my notes. Currently my notes are hosted
at [github pages][mm].

## Online Markdown (kramdown) Editor

While I am working on fixing my notes I am finding a lot of invalid syntax.
It could be helpful to use an [online editor][kramdown] to verify the markdown
syntax before posting.

## Tips for writing better markdown 

- Leave excessive space around special things like lists, code blocks, and quotes.
- Always use links in format:

```markdown
[displayed][unique_per_doc]

[unique_per_doc]: www.example.com
```

## Displaying Word Documents

Idealy I should be able to use pandoc, but it didn't like words encoding.

```
pandoc -s Project1Report_NateJerome+EE347.docx --reference-links -t markdown -o Project1Report_NateJerome+EE347.md
pandoc: Cannot decode byte '\xe6': Data.Text.Encoding.Fusion.streamUtf8: Invalid UTF-8 stream
```

So I used word to export it as a html.
The encoding of html exported from word document is not utf8. I used inconv to
change the encoding.

```
iconv -f WINDOWS-1252 -t UTF8 Project1Report_NateJerome+EE347.htm > 2015-03-26-ee347-project1-report.htm
```

I was able to host this htm file. Otherwise I could also use pandoc to convert
it to markdown. The markdown file did not contain any of the images. The tables
also were distorted sometimes.

```
pandoc -s 2015-03-26-ee347-project1-report.htm --reference-links -t markdown -o 2015-03-26-ee347-project1-report.md
```

Next I installed a plugin for Microsoft Word called [writage][1]. This allowed
word to save as a markdown file directly. It did not distort any of the tables.
All of the images in the word document were exported into a separate directory
"media" and then linked to from the markdown document using html syntax.

The simple equations were handled by the l

[1]: http://www.writage.com/
[mm]:  https://ngenetzky.github.io/minimal-mistakes/
[kramdown]: http://kramdown.herokuapp.com/