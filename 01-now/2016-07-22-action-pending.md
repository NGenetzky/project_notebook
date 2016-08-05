---
title: Action Pending
tags:
  - project_notebook
  - GTD
  - Fourney
  - Ulmer
  - Mettler
  - Tonkoski
  - Fan
date: 2016-07-22
slug: action-pending
published: true
author: Nathan Genetzky
layout: single
---

I want to approach my current todo list with the GTD methodology. I will first
collect anything that could be turned into a pending action.

# 01-capture

## Working on Projects with Dr. Fourney

1. Create CAN sniffer program
2. Create library for reading/writing structs of data from/to particle device
   over wifi with Particle variables.
3. Create library for reading/writing structs of data from/to particle device
   over wifi with Thingspeak.
4. Create library for reading/writing structs of data from/to particle device
   over serial.
5. Create MATLAB program to read and save the structs exposed by the Particle
   device.
6. Expose struct that represents the character spaces on 20x4 lcd screen.

## Working on Project Notebook with Dr. Fourney

1. Make it easier to get to the raw or rendered notes stored on Github from the
   Jekyll website.
2. Fix the broken internal file links.
3. Fix links on homepage of website to target mmistakes's website.
4. Create pages for project notebook - focus on content that doesn't change over time.

## Prepare for Senior Design

1. Review Jordan Ulmer's Senior Design project Proposal.
2. Schedule a meeting with Mr. Mettler about senior design.
3. Schedule meeting with Tonkoski about possible Microgrid project.
4. Email Dr. Fan about possible projects in the MCL for senior design.

# 02-clarify

## Working on Projects with Dr. Fourney

1. Create CAN sniffer program
    1. Create struct to model a CAN package.
    2. Transfer the struct across CAN and verify its integrity.
2. Create library for reading/writing structs of data from/to particle device
   over wifi with Particle variables.
    1. create "str()" function for the struct above.
3. Create library for reading/writing structs of data from/to particle device
   over wifi with Thingspeak.
    1. Create publish event from the data in the struct above.
4. Create library for reading/writing structs of data from/to particle device
   over serial.
    1. Transmit the str representation of the struct over serial.
5. Create MATLAB program to read and save the structs exposed by the Particle
   device.
    1. Provide a function to read the string rep of struct into a variable.
    2. Provide functions to convert the variable into more useful forms.
6. Expose struct that represents the character spaces on 20x4 lcd screen.
    1. Define the struct.
    2. Define way to write new values to struct
    3. Create matlab array that mirrors the value of the struct.

## Working on Project Notebook with Dr. Fourney

1. Make it easier to get to the raw or rendered notes stored on Github from the
   Jekyll website.
    1. Research if other jekyll developers have already created something I
       could use.
    2. Create vimscript that would add or update a reference style link to the
       file on github.
    3. Add link to a variable in the yaml frontmatter.
    4. Use liquid tags to output the link to the static page.
2. Fix the broken internal file links.
    1. Create regex that matches the internal link format.
    2. Create script to convert to jekyll relative path using *base_path*.
    3. Create script to convert to absolute path with a hardcoded base.
3. Fix links on homepage of website to target mmistakes's website.
    1. identify bad links and create list
    2. iterate list and redirect them or find commonality in the changes and
    try to use sed.
4. Create pages for project notebook - focus on content that doesn't change over time.
    a. project_notebook/index.md

## Prepare for Senior Design

1. Review Jordan Ulmer's Senior Design project Proposal.
    1. Download a copy onto tablet
    2. Read
    3. Prepare questions to ask
2. Schedule a meeting with Mr. Mettler about senior design.
    1. email
    2. attend
3. Schedule meeting with Tonkoski about possible Microgrid project.
    1. email
    2. prepare
    3. attend
4. Email Dr. Fan about possible projects in the MCL for senior design.
    1. email
