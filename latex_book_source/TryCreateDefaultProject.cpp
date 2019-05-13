#include "the_book_global.hpp"

constexpr auto main_index_txt = u8R"1_____1(


:tex_raw:[[%主文档]]

:tex_raw:[==========[

\documentclass[12pt,hyperref,UTF8]{ctexbook}%使用大号字体

%解决新版latex一些BUG
\let\counterwithout\relax
\let\counterwithin\relax

%@P143
\usepackage{xcolor}        %导入包xcolor
\usepackage[
a4paper ,
left=3.0cm,                %靠近装订线的边距
right=3.0cm,               %远离装订线的边距
top=2.0cm,
bottom=1.3cm,
footskip=0.7cm,
headheight=1.3cm,
headsep=0.5cm,
marginparsep=0.8cm,        %边注与内容边距
marginparwidth=2.1cm       %边注宽度
]{geometry}                %导入包geometry

%引入边注包
\usepackage{marginnote}

 %导入常用包
\usepackage{graphicx}
\usepackage{float}
\usepackage{amsmath}
\usepackage{cite}
\usepackage{caption}
\usepackage{titlesec}
\usepackage{chngcntr}
\usepackage{setspace}
\usepackage{tocbibind}  %设置目录
\usepackage{tocloft}
\usepackage{multicol}
\usepackage{listings}   %引入程序代码
\usepackage{varwidth}   %P125
\usepackage{verbatim}

%%常见符号
\usepackage{wasysym}    %
\usepackage{textcomp}   %
\usepackage{pifont}     %

\usepackage{color}
\definecolor{colorbackgroundthisproject}{rgb}{1,1,1} %页面背景颜色
\definecolor{colortextthisproject}{rgb}{0,0,0}       %文字颜色
%设置页面颜色
\pagecolor{colorbackgroundthisproject}
%设置字体颜色
\color{colortextthisproject}

\usepackage{xhfill}
%\usepackage{times} do not use this pack ...

\usepackage{placeins}

%设置输出pdf格式
\usepackage[
    colorlinks=true ,
    %bookmarks=true,
    %bookmarksopen=false,
    %pdfpagemode=FullScreen,
    %pdfstartview=Fit,
    bookmarksnumbered=true,
    pdftitle={Qml} ,       %标题
    pdfauthor={Qml} ,      %作者
    pdfsubject={Qml} ,     %主题
    pdfkeywords={Qml} ,    %关键字
    linkcolor=colortextthisproject ,
    anchorcolor=colortextthisproject ,
    citecolor=colortextthisproject ,
    urlcolor=colortextthisproject
]{hyperref}

\usepackage{fontspec}
\definecolor{sourcegrayone}{rgb}{0.99,0.99,0.99}  %源代码背景颜色
\newfontfamily\sourcefontone{Consolas}            %源代码字体
\newfontfamily\sourcefontthree{DejaVu Sans Mono}  %源代码字体
%sudo apt-get install ttf-mscorefonts-installer   %linux安装字体
\newfontfamily\sourcefonttwo{Times New Roman}     %正文特殊符号字体

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\setmainfont{Times New Roman}
\setsansfont{DejaVu Sans}
\setmonofont{Latin Modern Mono}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%源代码默认样式
\lstset{float,
language=C,
breaklines=true,
basicstyle=     \scriptsize\sourcefontthree        , %设置字号，字体
stringstyle=    \scriptsize\sourcefontthree        , %设置字号，字体
keywordstyle=   \scriptsize\sourcefontthree        , %设置字号，字体
commentstyle=   \scriptsize\sourcefontthree        , %设置字号，字体
identifierstyle=\scriptsize\sourcefontthree        , %设置字号，字体
numbers=left,
numbersep=0.5em,
numberstyle=    \scriptsize\slshape\sourcefontone  , %设置字号，字体
frame=single,
backgroundcolor=\color{sourcegrayone},
showstringspaces=false ,
aboveskip=1pt,
belowskip=1pt,
abovecaptionskip=1pt,
belowcaptionskip=5pt
}
%\ifoddpage \lstset{numbers=left} \else \lstset{numbers=right}
\usepackage{changepage}    %判断奇数页偶数页

%设置item样式......
\usepackage{enumitem}
\setenumerate[1]{itemsep=0pt,partopsep=0pt,parsep=\parskip,topsep=5pt}
\setitemize[1]{itemsep=0pt,partopsep=0pt,parsep=\parskip,topsep=5pt}
\setdescription{itemsep=0pt,partopsep=0pt,parsep=\parskip,topsep=5pt}

%表
\usepackage{longtable}
\usepackage{booktabs}

%设置常量
\title{Qt Quick全面导引}                              %书籍名称
\author{Good Luck}                                   %作者名

%下划线
\usepackage{ulem}

%设置ctex
%@P135
\CTEXsetup[ number={ \arabic{chapter} } ]{chapter}
\CTEXsetup[ beforeskip={0ex},afterskip={0ex} ]{section}
\CTEXsetup[ beforeskip={0ex},afterskip={0ex} ]{subsection}
\CTEXsetup[ beforeskip={0ex},afterskip={0ex} ]{subsubsection}
%\CTEXsetup[ number={ \arabic{section} } , name={第,节} ]{section}

% Calibri
% http://www.uisdc.com/western-fonts-typesetting
\newfontfamily{\sourcefontfive}{Calibri}
\newenvironment{littlelongworld}
{  \small         \\\hspace*{\fill} \slshape\sourcefontfive   }
{                   \hspace*{\fill}\\ }

%设置路径计数器
\newcommand\treeindexnumbernameone{路径}
%\newcommand\theTreeIndexNumber{}
\newcounter{treeindexnumber}[section]
%\stepcounter{treeindexnumber}
%\refstepcounter{treeindexnumber}
\renewcommand\thetreeindexnumber{\thesection.\arabic{treeindexnumber}}

%设置命令计数器
\newcommand\commandnumbernameone{命令}
\newcounter{commandnumber}[section]
\renewcommand\thecommandnumber{\thesection.\arabic{commandnumber}}

%设置源码计数器
\newcommand\filesourcenumbernameone{源码}
\newcounter{filesourcenumber}[section]
\renewcommand\thefilesourcenumber{\thesection.\arabic{filesourcenumber}}

%设置图片计数器
\counterwithin{figure}{section}
\renewcommand\thefigure{\thesection.\arabic{figure}}

%设置表计数器
\counterwithin{table}{section}
\renewcommand\thetable{\thesection.\arabic{table}}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%解决目录字体重叠BUG
\makeatletter
\renewcommand{\numberline}[1]{%
\settowidth\@tempdimb{#1\hspace{0.5em}}%
\ifdim\@tempdima<\@tempdimb%
\@tempdima=\@tempdimb%
\fi%
\hb@xt@\@tempdima{\@cftbsnum #1\@cftasnum\hfil}\@cftasnumb}
\makeatother
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\lstnewenvironment{thebookfilesourceone}[1][]{
%begin env ...
    \lstset{#1}
}{
%end env ...
}

\lstnewenvironment{thebookfilesourceonepathtree}[1][]{
%begin env ...
    \lstset{#1}
}{
%end env ...
}

%命令行环境
\lstnewenvironment{thebookfilesourceonecommand}[1][]{
%begin env ...
    \lstset{
basicstyle=     \scriptsize\itshape\sourcefontone        , %设置字号，字体
stringstyle=    \scriptsize\itshape\sourcefontone        , %设置字号，字体
keywordstyle=   \scriptsize\itshape\sourcefontone        , %设置字号，字体
commentstyle=   \scriptsize\itshape\sourcefontone        , %设置字号，字体
identifierstyle=\scriptsize\itshape\sourcefontone        , %设置字号，字体
#1 }
}{
%end env ...
}

%设置标题
\setlength{\belowcaptionskip}{0.1em}
\setlength{\LTpost}{0pt}
%\setlength{\LTpre}{0pt}

\newcommand\thebookexistone{\rotatebox[origin=c]{12}{\scalebox{0.65}{$\exists$}}}
\newcommand\thebookallone{\rotatebox[origin=c]{-6}{$\forall$}}

%表格行距
\renewcommand\arraystretch{0.9}
%\setlength\belowrulesep{0pt}
%\setlength\aboverulesep{0pt}
%标题上部额外间距
\setlength{\abovecaptionskip}{5pt}
\setlength{\belowcaptionskip}{3pt}
%338
\setlength{\floatsep}{10pt plus 2pt minus 2pt}
\setlength{\textfloatsep}{10pt plus 2pt minus 2pt}
\setlength{\intextsep}{10pt plus 2pt minus 2pt}

\newcommand{\refTheBookFigure}[1]{\uwave{\figurename\ref{#1}}}
\newcommand{\refTheBookTable}[1]{\uwave{\tablename\ref{#1}}}
\newcommand{\refTheBookFileSource}[1]{\uwave{\filesourcenumbernameone\ref{#1}}}
\newcommand{\refTheBookTreeIndex}[1]{\uwave{\treeindexnumbernameone\ref{#1}}}
\newcommand{\refTheBookCommand}[1]{\uwave{\commandnumbernameone\ref{#1}}}
\newcommand{\refTheBookChapter}[1]{\uwave{第\ref{#1}章}}
\newcommand{\refTheBookSection}[1]{\uwave{第\ref{#1}节}}

\usepackage{tcolorbox}
%设置公式计数器
\newcommand\fileequalnumbernameone{公式}
\newcounter{fileequalnumber}[section]
\renewcommand\thefileequalnumber{\thesection.\arabic{fileequalnumber}}

\begin{document}

%设置标点挤压模式
\punctstyle{banjiao}

\frontmatter
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\pagestyle{empty}                 %关闭页眉页脚
\maketitle                        %生成封面
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\cleardoublepage
\pagestyle{headings}              %开启页眉页脚
\pagenumbering{roman}             %重新开始页码编号
\setcounter{tocdepth}{4}          %设置目录深度
\setcounter{secnumdepth}{4}       %设置编号深度
\tableofcontents                  %生成目录
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\mainmatter
%
%    arabic - 阿拉伯数字
%    roman  - 小写的罗马数字
%    Roman  - 大写的罗马数字
%    alph   - 小写的字符形式
%    Alph   - 大写的字符形式
%
\pagenumbering{arabic}           %重新开始页码编号
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%………………在这里加入你的内容………………
%\input{foreword/foreword.tex}     %前言


\cleardoublepage                              %增加空白页
\CTEXsetup[format={\bfseries\raggedright}]{section} %section左对齐
\setcounter{secnumdepth}{-2}                  %暂停编号，但加入目录
\chapter{附录}
\begin{multicols}{3}
\section{图片索引}
\input{figureIndex.tex}                       %图片索引目录
\section{表格索引}
\input{tableIndex.tex}                        %表格索引目录
\section{源码索引}
\input{sourceIndex.tex}                       %源码索引目录
\section{命令索引}
\input{commandSourceIndex.tex}                %命令索引目录
\section{路径索引}
\input{dirTreeSourceIndex.tex}                %目录树索引目录
\end{multicols}

\backmatter
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\end{document}

% \enlargethispage{1cm}
% http://www.ctex.org/documents/latex/graphics/node2.html
% https://www.jianshu.com/p/b1751078e28e
% \tiny
% \scriptsize
% \footnotesize
% \small
% \normalsize
% \large
% \Large
% \LARGE
% \huge
% \Huge

]==========]

:tex_raw:[[
% ______all_key_words
% the_book_chapter the_book_subsection the_book_subsubsection
% the_book_section the_book_image the_book_table
% the_book_file the_book_tree_file the_book_command_file
% littlelongworld tabbing ref
% figurename tablename filesourcenumbernameone
% treeindexnumbernameone commandnumbernameone footnote
% item itemize comment textbullet
% \hspace*{\parindent}
% FloatBarrier
]]

)1_____1"sv;

constexpr auto the_book_constexpr_txt = u8R"2____2(

)2____2"sv;

extern void tryCreateDefaultProjcet(){

    const auto & varDir = getOutPutFileDir();

    if( !QFileInfo::exists( varDir.absoluteFilePath(QStringLiteral("main_index.txt")) ) ){
        QFile varFile{ varDir.absoluteFilePath(QStringLiteral("main_index.txt")) };
        if( !varFile.open( QIODevice::WriteOnly ) ){
            the_book_throw("can not create "sv,"main_index.txt"sv);
        }
        varFile.write( "\xef\xbb\xbf" , 3 );
        varFile.write( main_index_txt.data(),main_index_txt.size() );
    }

    if( !QFileInfo::exists( varDir.absoluteFilePath(QStringLiteral("the_book_constexpr.txt")) ) ){
        QFile varFile{ varDir.absoluteFilePath(QStringLiteral("the_book_constexpr.txt")) };
        if( !varFile.open( QIODevice::WriteOnly ) ){
            the_book_throw("can not create "sv,"the_book_constexpr.txt"sv);
        }
        varFile.write( "\xef\xbb\xbf" , 3 );
        varFile.write( the_book_constexpr_txt.data(),the_book_constexpr_txt.size() );
    }

    varDir.mkdir( QStringLiteral("the_book_image") );

}
