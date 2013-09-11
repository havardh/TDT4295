Report
======
The structure of the report is higly inspired from last years computer design project :)

Instructions of how to orgianize and write the report is given below.

Structure
---------
The report is ordered into several directories for each `chapter`, where each chapter has
it's own `sections` and `figures`.
An example of the directory structure is as follows:

<pre>
report/
|---chapters/
|   |---intro.tex
|   |---intro/
|   |   |---assignment.tex
|   |   |---abstract.tex
|   |---fpga.tex
|   |---fpga/
|       |---isa.tex
|---figures/
|   |---intro/
|   |   |---intro-table.tex
|   |---fpga/
|       |---isa-table1.tex
|       |---isa-figure1.tex
|---appendices/
|   |---"appendices go here"
|---report.tex
|---config.tex
|---Makefile
</pre>

<h4>report.tex</h4>
This file defines the general structure of the report, like e.g. the order of chapters.

Include a new chapter like this
```
\input{chapters/<chap>}
```

<h4>config.tex</h4>
This file is used to include latex-packages and fix the layout of the report.

Chapters
--------
To write a new chapter, create a new file in `chapters/<chap>.tex` 
and a new directory `chapters/<chap>/` in which you create every section of the chapter
`chapters/<chap>/<chap-section>.tex`.

The `<chap>.tex` should have the following content.

```
\chapter{Chaptername}\label{chapter:\<chap>}

\input{chapters/<chap>/<chap-section>}
\input{...}
```
<h4>Sections</h4>
Each section is written like this:

```
\section{<Section Header>}
Text in section

\subsection{<Sub Section Header>}
Text in subsection
```

Figures
-------
All figures is put in the a directory like `figures/<chap>/<figure-name>.tex`, where `<chap>` 
specifies which chapter the figure is related to.

All types of figures should be included in this direcotry, including
* tables
* pictures
* tex-figures

<h4>Creating a figure</h4>
A figure might be formatted like this
```
\begin{figure}[h]
    \centering
    \begin{bytefield}[endianness=big,bitwidth=0.05\linewidth]{16}
        \bitheader{0-15} \\
        \bitbox{2}{Group} &
        \bitbox{2}{Funct} &
        \bitbox{2}{Option} &
        \bitbox{5}{Reg A} &
        \bitbox{5}{Reg B} 
    \end{bytefield}

    \caption{Arithmetic instructions}
    \label{fig:arith_instr_format}
\end{figure}
```
Remember to <b>always</b> label the figure after the caption, 
otherwise references to the figures will fail!

<h4>Placing figures</h4>
The character inside the square brackets in `\begin{figre}[X]`
specifies where the figure is placed in the text.

Exchange `X` with
* `h` - to place the figure somwhere <b>after</b> the \include
* `H` - to place the figure <b>exactly</b> at the \include
* `b` - to place the figure at the <b>bottom</b> of the page
* `t` - to place the figure at the <b>top</b> of the page

<h4>Including figures</h4>
Do this to include the figures into the section that you're working on

```
\input{figures/<chap>/<figure-name>.tex}
```

<h4>Referencing figures</h4>
Each figure should have a unique label to identify it with,
the label should be defined like this
```
\label{fig:<figure-lbl1>}     % If the figure is a tex-figure

\label{tab:<table-lbl1>}      % If the figure is a table
```

Do this to reference the figure in the text, notice that you're
referencing the defined label
```
\ref{fig:<figure-lbl1>}
```
