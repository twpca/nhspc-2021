# 天竺鼠遊行 (puipui)

## 問題描述

車車農場養了一些天竺鼠，這些天竺鼠很可愛也有很多粉絲，而農場在每週末舉辦的天竺鼠遊行更是遊客的焦點之一。
農場裡共有 $`n`$ 隻天竺鼠，牠們的高度都不盡相同，我們用 $`h_i`$ 來表示第 $`i`$ 隻天竺鼠的高度。
農場主人希望挑選一些天竺鼠來參加遊行，
由於這週恰逢連休遊客眾多，他希望能組成 $`p`$ 個遊行隊伍來參加一場盛大的遊行，其中每個隊伍都由 $`k`$ 隻天竺鼠排成環狀組成。
並且為了讓本週遊行更有看點，農場主人決定要調整隊伍的順序增加整齊度，
讓每一個隊伍裡天竺鼠與其相鄰天竺鼠的高度差距都不會太大，
請你幫他計算所有可能的隊伍順序裡，相鄰天竺鼠最大高度差的最小值是多少。

舉例來說，$`n = 14`$、$`k = 6`$ 且 $`p = 2`$，天竺鼠高度各為
$`(6, 9, 6, 4, 5, 5, 3, 6, 4, 8, 8, 7, 6, 1)`$。
農場主人想要選出其中 $`12`$ 隻天竺鼠排出兩個環狀隊伍，
若選擇高度 $`(9, 6, 6, 5, 5, 4)`$ 的天竺鼠順時針排在第一個隊伍，
高度 $`(3, 6, 4, 8, 8, 7)`$ 的天竺鼠依順時針排在第二個隊伍。
此時第一個隊伍的最大高度差為 $`|9 - 4|=5`$，第二個隊伍的最大高度差為 $`|4-8| = 4`$。
我們說這個排列方式最大的高度差為 $`5`$。

另一個排列方式為如下圖的兩個環狀隊伍（剩下高度 $`9`$ 與 $`1`$ 的天竺鼠本週休息不參加遊行）。
圖中每個圓圈代表一隻天竺鼠，圓圈內數字代表天竺鼠高度，而兩個圓圈之間的數字則是他們的高度差。
這個選取與排列方式的最大高度差是 $`2`$，是所有可能選取與排列方式中最小的，因此本範例的答案是 $`2`$。

\begin{minipage}{0.49\textwidth}
  \begin{figure}[H]
  \centering
  \begin{tikzpicture}[scale=0.9]
    \def \N {
        0/6,
        60/5,
        120/6,
        180/5,
        240/3,
        300/4}
    \def \M {
        1/2/1,
        2/3/1,
        3/4/1,
        4/5/2,
        5/6/1,
        6/1/2}
    \foreach \pos / \num in \N {
        \def\id{\directlua{tex.sprint(\pos // 60 + 1)}}
        \node[circle,draw,minimum size=0.5cm] (\id) at (\pos+90:2) {$\num$};
    }
    \foreach \x / \y / \w in \M {
        \def\st{\directlua{
            tex.sprint((\x-1) * 60 + 90)
        }}
        \def\ed{\directlua{
            local y = \y;
            if y == 1 then
                y = y + 6
            end
            tex.sprint((y-1) * 60 + 90)
        }}
        \def\mid{\directlua{
            tex.sprint((\st+\ed) / 2)
        }}
        \path[draw,thick,-,black,shorten <= 10pt,shorten >= 10pt] (\x) arc(\st:\ed:2) (\y) node at (\mid:2.5) {$\w$};
    }
  \end{tikzpicture}
  \caption{隊伍一}
  \end{figure}
\end{minipage}
\begin{minipage}{0.49\textwidth}
  \begin{figure}[H]
  \centering
  \begin{tikzpicture}[scale=0.9]
    \def \N {
        0/8,
        60/7,
        120/8,
        180/6,
        240/4,
        300/6}
    \def \M {
        1/2/1,
        2/3/1,
        3/4/2,
        4/5/2,
        5/6/2,
        6/1/2}
    \foreach \pos / \num in \N {
        \def\id{\directlua{tex.sprint(\pos // 60 + 1)}}
        \node[circle,draw,minimum size=0.5cm] (\id) at (\pos+90:2) {$\num$};
    }
    \foreach \x / \y / \w in \M {
        \def\st{\directlua{
            tex.sprint((\x-1) * 60 + 90)
        }}
        \def\ed{\directlua{
            local y = \y;
            if y == 1 then
                y = y + 6
            end
            tex.sprint((y-1) * 60 + 90)
        }}
        \def\mid{\directlua{
            tex.sprint((\st+\ed) / 2)
        }}
        \path[draw,thick,-,black,shorten <= 10pt,shorten >= 10pt] (\x) arc(\st:\ed:2) (\y) node at (\mid:2.5) {$\w$};
    }
  \end{tikzpicture}
  \caption{隊伍二}
  \end{figure}
\end{minipage}

## 輸入格式

\begin{format}
\f{
$n$ $k$ $p$
$h_1$ $h_2$ $\cdots$ $h_n$
}
\end{format}

* $`n`$, $`k`$, $`p`$ 分別代表天竺鼠個數、每個隊伍的天竺鼠數以及隊伍數
* $`h_i`$ 為第 $`i`$ 隻天竺鼠的高度

## 輸出格式

\begin{format}
\f{
$\textrm{ans}$
}
\end{format}

* $`\textrm{ans}`$ 為整數，代表所有隊伍相鄰天竺鼠高度差的最小值

## 測資限制

* $`1 \le n \le 10^6`$
* $`2 \le k \le n`$
* $`1 \le p \le n`$
* $`kp \le n`$
* $`1 \le h_i \le 10^9`$
* 上面所有變數皆為整數

## 範例測試

## 評分說明

本題共有四組子任務，條件限制如下所示。
每一組可有一或多筆測試資料，該組所有測試資料皆需答對才會獲得該組分數。

|  子任務  |  分數  | 額外輸入限制 |
| :------: | :----: | ------------ |
| 1 | {{score.subtask1}} | $`k=n`$，$`n \le 10`$，$`p=1`$ |
| 2 | {{score.subtask2}} | $`k=n`$，$`n \le 10^5`$，$`p=1`$ |
| 3 | {{score.subtask3}} | $`p=1`$ |
| 4 | {{score.subtask4}} | 無額外限制 |
