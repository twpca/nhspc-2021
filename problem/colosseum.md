# 天空競技場 (colosseum)

## 問題描述

臘月寒冬，小傑來到天空競技場磨練競技程式的技術並賺取金幣。
天空競技場是一棟非常高的建築物，遠遠看去彷彿有一百萬層那麼高。
小傑來到的競技場是一棟 $`n`$ 層樓的建築物，樓層標號為 $`1`$ 到 $`n`$，樓層編號越大代表所在位置越上面。
參加者會在時間 $`0`$ 時選擇任一樓層作為起點進入或直接離開放棄挑戰，並可以在任意時間點任意樓層選擇結束挑戰並獲得累積的金幣獎勵。
進到競技場後，參賽者會從選擇的起點樓層開始一層一層往上直到離開，到結束挑戰前都不可跳過樓層也不可以往下面樓層走。
競技場設有高速移動的電梯，可以讓參賽者一瞬間移動到樓上一層，所以樓層之間的移動時間可以視為 $`0`$ 不計。

競技場每個樓層都有一位樓主，第 $`i`$ 層的開設時間為 $`x_i`$，挑戰門檻為 $`y_i`$。
參加者到樓層 $`i`$ 時若所持金幣未滿 $`y_i`$ 則無法參加這個樓層的競技，參加者只能繼續往上走或結束挑戰。
任何滿足金幣門檻（所持金幣 $`y_i`$ 以上）的參加者如果恰在開設時間 $`x_i`$ 或之後到達第 $`i`$ 樓的話就會強制發生戰鬥與樓主競技，不能拒絕。
此競技將耗費 $`t_i`$ 的時間並於競技結束時獲取 $`w_i`$ 的金幣。
如果在時間 $`x_i`$ 之前到達 $`i`$ 樓且滿足金幣門檻的參賽者，則可以選擇在這層樓等待至開設時間或是直接繼續往上走。

小傑對競技場的挑戰非常感興趣，但不巧他今天得在時間 $`m`$ 或以前離開競技場回去參加程式比賽，
請幫小傑規劃從哪一個樓層開始以及要在哪些樓層等待，讓他可以在 $`m`$ 的時間內得到最多的金幣。

\newpage
下面是一個 $`n=6, m=9`$ 的例子，
左方表格內是各樓層的開始時間 $`x_i`$、門檻值 $`y_i`$、競技耗時 $`t_i`$ 與可獲金幣 $`w_i`$，右圖中列舉了三種可能（但非全部）的路線。
(a) 路線從 $`1`$ 樓進入，因為到達時 $`1`$ 樓已達開設時間且滿足挑戰門檻所以必須競技，在一樓耗費 $`4`$ 時間獲得 $`1`$ 金幣。
然後依序在 $`2,3`$ 樓獲得 $`3`$ 與 $`1`$ 枚金幣。在時間 $`9`$ 時共獲得 $`5`$ 枚金幣離開。
(b) 路線由 $`2`$ 樓進入，先在 $`2`$ 樓等到 $`x_2 = 1`$ 時參加競技，耗費 $`2`$ 時間獲得 $`3`$ 金幣。
到達 $`3`$ 樓時因為門檻不滿足直接進入 $`4`$ 樓，$`4`$ 樓的開始時間 $`x_4=6`$ 未到，選擇不等待直接進入 $`5`$ 樓，
之後等待 $`1`$ 時間與耗費 $`5`$ 時間獲得 $`5`$ 枚金幣，總共獲取 $`8`$ 枚金幣離開，這是本例中可獲得最多金幣的策略之一。

\begin{minipage}{0.35\textwidth}
\begin{table}[H]
  \centering
  \begin{tabular}{|c|c|c|c|c|}
  \hline
  $i$ & $x_i$ & $y_i$ & $t_i$ & $w_i$ \\
  \hline
  $6$ & $1$ & $0$ & $7$ & $6$ \\
  \hline
  $5$ & $4$ & $3$ & $5$ & $5$ \\
  \hline
  $4$ & $6$ & $1$ & $1$ & $4$ \\
  \hline
  $3$ & $2$ & $4$ & $3$ & $1$ \\
  \hline
  $2$ & $1$ & $0$ & $2$ & $3$ \\
  \hline
  $1$ & $0$ & $0$ & $4$ & $1$ \\
  \hline
  \end{tabular}
  \caption{各樓層的開始時間及門檻}
\end{table}
\end{minipage}
\hfill
\begin{minipage}{0.64\textwidth}
  \begin{figure}[H]
  \begin{tikzpicture}[scale=0.9]
    \draw[help lines, color=gray!30, dashed] (0, 0) grid (10, 9);
    \draw[->, ultra thick] (0, 0) -- (10, 0) node[right]{時間};
    \draw[->, ultra thick] (0, 0) -- (0, 9) node[above]{樓層};
    \draw[blue, ultra thick] (9, -0.5) -- (9, 9.5) node[above]{$m=9$};

    \draw[->, thick] (0, 1) -- node[above]{\footnotesize 1F競技 (1\$)} (4, 1);
    \draw[->, thick] (4, 1) -- (4, 2);
    \draw[->, thick] (4, 2) -- node[above]{\footnotesize 2F競技 (3\$)} (6, 2);
    \draw[->, thick] (6, 2) -- (6, 3);
    \draw[->, thick] (6, 3) -- node[above]{\footnotesize 3F競技 (1\$)} (9, 3) node[right] {(a)};

    \draw[->, red, thick] (0, 2) -- node[above]{\footnotesize 等待} (1, 2);
    \draw[->, red, thick] (1, 2) -- node[above]{\footnotesize 2F (3\$)} (3, 2);
    \draw[->, red, thick] (3, 2) -- (3, 3);
    \draw[->, red, thick] (3, 3) -- node[right]{\footnotesize 上5F} (3, 4);
    \draw[->, red, thick] (3, 4) -- (3, 5);
    \draw[->, red, thick] (3, 5) -- node[above]{\footnotesize 等待} (4, 5);
    \draw[->, red, thick] (4, 5) -- node[above]{\footnotesize 5F (5\$)} (9, 5) node[right,black] {(b)};

    \draw[->, thick] (0, 6) -- node[above]{\footnotesize 等待} (1, 6);
    \draw[->, thick] (1, 6) -- node[above]{\footnotesize 6F (6\$)} (8, 6) node[right,black] {(c)};
  \end{tikzpicture}
  \end{figure}
\end{minipage}


## 輸入格式

\begin{format}
\f{
$n$ $m$
$x_1$ $y_1$ $t_1$ $w_1$
$x_2$ $y_2$ $t_2$ $w_2$
\vdots
$x_n$ $y_n$ $t_n$ $w_n$
}
\end{format}

- $`n`$, $`m`$ 分別代表競技場樓層數與小傑可以參加競技的時間
- $`x_i`$, $`y_i`$, $`t_i`$, $`w_i`$ 分別為樓層 $`i`$ 的開設時間、競技門檻、競技所需時間以及完成競技的獎勵

## 輸出格式

\begin{format}
\f{
$\textrm{ans}$
}
\end{format}

- $`\textrm{ans}`$ 為一個整數，代表最多可以得到的金幣數量

## 測資限制

* $`1 \le n \le 3 \times 10^5`$
* $`0 \le m, x_i, y_i \le 10^9`$（$`i \in \{1, 2, \ldots, n\}`$）
* $`1 \le t_i, w_i \le 1000`$（$`i \in \{1, 2, \ldots, n\}`$）
* 上面所有變數皆為整數

## 範例測試

## 評分說明

本題共有四組子任務，條件限制如下所示。
每一組可有一或多筆測試資料，該組所有測試資料皆需答對才會獲得該組分數。

|  子任務  |  分數  | 額外輸入限制 |
| :------: | :----: | ------------ |
| 1 | {{score.subtask1}} | $`n \le 1000`$ |
| 2 | {{score.subtask2}} | $`x_i = y_i = 0`$ |
| 3 | {{score.subtask3}} | $`x_i = 0`$ |
| 4 | {{score.subtask4}} | 無額外限制 |
