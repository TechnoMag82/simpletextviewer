
# Simple Text Viewer

Desktop application for browse source code with syntax highlighting on Linux OS, written on C++ Qt 5.x

### Motivation
Browsing with application source code in GUI mode on OS Linux with syntax highlighting in read-only mode opening files, as a replacement of viewer in Double Commander.

## Base functions

1. Opening files only in read-only mode
2. Syntax highlighting of source code
3. Custom color theme of syntax highlighting
4. Custom create rules of syntax highlighting based on types of file
5. Searching text in sources

## Files configurations and paths

Base resource files locate in ***/usr/share/simpletextviewer***

- Color themes ***../themes***. For example: ***default.theme***
- Rules of syntax highlighting ***../syntax***, For example: ***syntax_cpp.syn***

> File name of syntax contain with **syntax_xxx.syn**
> 
> **where**
> 
>  xxx - extention of opened file for browse

Base application config file location in
$HOME/.config/simpletextviewer/.editor.conf

This file contain current used theme name:
theme=default

## Creating color theme

File of color theme contains color with KEY=COLOR

```
    background=#FFFFFF
    base_text_color=#000000
    keywords=#000C80
    braces=#FFAC23
    comments=#858585
    objects=#000000
    control_characters=#000000
    macros=#000000
    strings=#115C00
    chars=#115C00
    numbers=#FF0000
    line_number=#000000
    current_line=#C7C7C7
    preprocessor=#0C6F5A
```

> Key names and color format must be strict keeps.

## Creating rules of syntax highlighting

File of syntax rules contains lines with KEY=VALUE

Where
 KEY - name of type word or characters
 VALUE = space-separated word which must coloring

For example:

```
    keywords=int bool char byte long double
    comments_single=//
    comments_block=/* */
    preprocessor=#include #ifndef #define #endif
    objects=Array List Set QString QFile QColor
    macros=SIGNAL tr
    braces=[ ] { } ( )
    control_characters=|| && :: << >> -> => <= != == & ! ? = . , + - = | ; < > *
```

For values such as "braces", "control_characters" importance is order: in begin placed complex values, further - simple values.

## In planning

- Settings dialog for create color themes and syntax rules


(c) TechnoMag, june 2023
