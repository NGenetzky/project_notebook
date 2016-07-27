---
title: Simple Example for Particle Device
tags:
  - project_notebook
date: 2016-07-24
slug: simple-example-for-particle-device
published: true
author: Nathan Genetzky
layout: single
---

A branch named ["board-rgb-demo"][directory] has been created in the repo
["particle-projects"][repo] which demonstrates the use of Particle Function to
control the micro controller on board features.

# Complexity

This project was designed to be easily understandable and to have very few
file dependencies. The project contains only five modules from the existing code;
this use symlinks to make them appear in the directory with the project but also
keep up-to-date with the master copy of the files.

# Exposed Variables and Functions

There is a function for controlling the rgb and one for controlling the other
features on the board.

```
Matt [************************] (Photon) is online
  Variables:
    rgb (string)
  Functions:
    int board(String args) 
    int rgb(String args) 
```

`board()` currently understands three words, which can be used by the end use
to use functions within the module.

- led_on
- led_off
- reset

`rgb()` understands the word "release" but is primarily used with three comma
separated integers less than 255. The RGB led on the device is set to a color
by sending a message in the format `RRR,GGG,BBB`.

[repo]: https://github.com/NGenetzky/particle-projects
[directory]: https://github.com/NGenetzky/particle-projects/tree/board-rgb-demo/board-rgb-demo

