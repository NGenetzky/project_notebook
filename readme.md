---
permalink: /project_notebook/
title: "README for Project Notebook"
excerpt: "README of Project Notebook"
modified: 2016-04-18T16:39:37-04:00
---

# Nathan Genetzky's Project Notebook

## Introduction

This is an electronic notebook that will be used to record progress as
projects are worked on. The primary purpose of the documents is to
provide informal documentation that another individual could follow
to achieve similar results. There are not strict formatting standards,
but eventually more concrete guidelines will be created.

## Project Notebook

The inspiration for this notebook arose from the usage of a research notebook
used while working on undergraduate research and from project notebooks kept
for a lab/project based course at South Dakota State University (SDSU). The benefits
of documenting the work was very apparent.

A large percentage of the work and results was in digital form. I would collect
arrays of measurements, perform calculations, and create graphs. Calculations
were performed using matlab scripts, simulations were created in PSpice, and
measurements were obtained from oscilloscopes or simulations. Typically a PDF
could be created that contained a representation of the data and then it could
be printed and pasted into the paper notebook.

When the notebook was started I considered a few of the
[Desired Properties of a Project Notebook][1]. It is important to tie together
the work done in a particular time period. The files with the format: 
"YYYY-MM-DD.md" should describe the work done on a day; 
([Ideas about Day markdown][2]) discusses about possible organization of content. 

## Internet of Things with Particle Devices

Particle is a type of a microcontroller that has wifi capabilities. An
introduction to the capability provided by the particle devices is given in
[Intro to Particle][9], and an example of its usage in [Using Particle Cloud][3].
Most of the code for projects involving particle devices is on a github
repository, [Particle Projects][4].

There are various communication protocols supported by the Particle devices.
The I2C projects were described and compared in [I2C on Particle][6]. CAN
communication was discussed in [Can with Particle][7].

One of my projects demonstrates controlling an RGB light from Matlab or
an android phone (via Tasker). The project is described in [this note][5], and
most of the code can be found in /2016/06/05 or on the repository on that day.

## Programming

### C++

C++ is fundamental for programming most embedded systems. It is important to
keep up to date with advancements in the language. SDSU teaches C++98 standard,
 but the C++11 and C++14 standards have improved the language significantly. In
 [Modern Cpp in Embedded][8] I reviewed literature and documented what I learned
or thought was important.


[1]: {% post_url 2016-05-10-desired-properties-of-the-notebook %}
[2]: {% post_url 2016-05-11-ideas-about-day-markdown %}
[3]: {% post_url 2016-06-08-using-particle-cloud %}
[4]: https://github.com/NGenetzky/particle-projects
[5]: {% post_url 2016-06-05-particle-code-now-on-github %}
[6]: {% post_url 2016-05-11-i2c-on-particle %}
[7]: {% post_url 2016-05-16-can-with-particle %}
[8]: {% post_url 2016-05-16-modern-cpp-in-embedded-systems %}
[9]: {% post_url 2016-06-24-intro-to-particle %}
