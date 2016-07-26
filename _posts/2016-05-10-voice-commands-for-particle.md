---
author: Nathan Genetzky
date: '2016-05-10'
filename: 2016-05-10-voice-commands-for-particle.md
layout: single
published: true
slug: voice-commands-for-particle
tags:
- short
- particle
- project_notebook
title: Voice Commands for Particle
---

Working on using voice commands from my phone to control Particle devices.

Successfully works if I do the filtering on the phone side. If I send the comamnd
straight through from the voice regonition to the Particle, then it doesn't work
very well. I am going to try to have my phone post a Particle.Publish instead;
the hope is then I could use a python app or something to watch the stream and 
interrpret it.