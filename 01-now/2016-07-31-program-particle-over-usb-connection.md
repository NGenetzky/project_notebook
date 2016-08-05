---
title: Program Particle over USB Connection
tags:
  - project_notebook
date: 2016-07-31
slug: program-particle-over-usb-connection
published: true
author: Nathan Genetzky
layout: single
---

While OTA (Over the air) programming is very convenient there are sometimes
when you want to program over USB.

I started to follow
[Tutorial: Installing DFU-Driver on Windows [24 Feb 2015]][p1] but the program
to install dfu-util, [Zadig][p2], did not work. Instead I found this other guide,
[dfu-util Installation Guide][g1], to be more helpful.

Using the Particle CLI to program.
```
particle flash --usb tinker
```

[p1]: https://community.particle.io/t/tutorial-installing-dfu-driver-on-windows-24-feb-2015/3518
[p2]: http://zadig.akeo.ie/
[g1]: https://github.com/redbear/Duo/blob/master/docs/dfu-util_installation_guide.md
