# 汽車不再繞圈圈 (car)

## 問題描述

小戸川市以觀光和計程車的發達聞名，外國遊客們常常在城巿裡搭計程車往返各個景點。
城巿裡的道路交通網是一個有向圖（directed graph），每條道路的通行方向可以透過特殊的權限由主控台改變。
詳細一點來說，城市共有 $`n`$ 個景點（編號由 $`1`$ 至 $`n`$）與 $`m`$ 條道路（編號由 $`1`$ 到 $`m`$）。
第 $`i`$ 條道路由 $`u_i`$ 單向通往 $`v_i`$，並且需要至少 $`c_i`$ （$`c_i \ge 1`$）的管理者權限才能改變方向。
管理權限可以由一個正整數表示，數字越大代表權限越大；
若管理者有 $`P`$ 的權限，則他可以透過系統改變任意 $`c_i \le P`$ 的道路方向。

某天小戸川市的交通局被觀光客投訴部份計程車司機會利用城巿裡的道路載著乘客繞圈圈以收取更高的費用。
為了避免這個亂象，城巿的交通局長決定透過改變城市中某些道路的方向，使得城市中不存在環，讓計程車司機們無法在城巿裡繞圈圈。
交通局長請資訊專長的你幫忙計算至少要多大的權限才能達成目標。
請注意由於城市的都市規劃不佳，兩景點間可能有複數條道路存在或者完全無法到達的情況發生。

以下圖為例，其中邊上的數字代表改變該條道路方向所需的權限，
若管理者權限為 $`2`$，並改變 $`(2,1)`$、$`(2,3)`$ 這兩條道路的方向即可達成目標。
這也是能達成交通局長目標的管理者權限最小值。

\begin{minipage}{0.49\textwidth}
  \begin{figure}[H]
    \centering
    \begin{tikzpicture}[scale=0.8]
      \def \Nodes {
        1/6/3,
        2/3/3,
        3/0/3,
        4/0/0,
        5/3/0}
      \def \Edges {
        2/1/1/above,
        1/5/4/below,
        5/2/6/left,
        2/3/2/above,
        3/4/3/left,
        4/5/2/below}

      \foreach \id / \x / \y in \Nodes {
        \node[draw,circle] (\id) at (\x, \y) {\id};
      }
      \foreach \x / \y / \w / \labelpos in \Edges {
        \path[draw,->,thick] (\x) -- (\y) node[midway,\labelpos] {\w};
      }
    \end{tikzpicture}
    \caption{改變道路方向前}
  \end{figure}
\end{minipage}
\begin{minipage}{0.49\textwidth}
  \begin{figure}[H]
    \centering
    \begin{tikzpicture}[scale=0.8]
      \def \Nodes {
        1/6/3,
        2/3/3,
        3/0/3,
        4/0/0,
        5/3/0}
      \def \Edges {
        1/2/1/above/red,
        1/5/4/below/black,
        5/2/6/left/black,
        3/2/2/above/red,
        3/4/3/left/black,
        4/5/2/below/black}

      \foreach \id / \x / \y in \Nodes {
        \node[draw,circle] (\id) at (\x, \y) {\id};
      }
      \foreach \x / \y / \w / \labelpos / \color in \Edges {
        \path[draw=\color,->,thick] (\x) -- (\y) node[midway,\labelpos] {\w};
      }
    \end{tikzpicture}
    \caption{改變道路方向後}
  \end{figure}
\end{minipage}

## 輸入格式

\begin{format}
\f{
$n$ $m$
$u_1$ $v_1$ $c_1$
$u_2$ $v_2$ $c_2$
$\vdots$
$u_m$ $v_m$ $c_m$
}
\end{format}

* $`n`$、$`m`$ 分別代表城市數與道路數
* $`u_i`$、$`v_i`$、$`c_i`$ 代表第 $`i`$ 條道路單向連接 $`u_i`$ 到 $`v_i`$，且改變方向需要的權限為 $`c_i`$

## 輸出格式

\begin{format}
\f{
$P$ $R$
$e_1$
$e_2$
$\vdots$
$e_R$
}
\end{format}

* $`P`$ 為一整數，代表達成交通局長目標需要最少的權限大小。若不需要改變任何道路方向即可達成交通局長的要求，$`P`$ 請輸出 $`0`$
* $`R`$ 為一整數，代表需要改變方向的道路個數
* $`e_i`$ 為一整數，代表第 $`i`$ 條想要改變方向的道路編號。注意同一條道路編號不可以在 $`e`$ 出現兩次以上，並且改變此條道路所需的權限也不可以超過 $`P`$（意即必須滿足 $`c_{e_i} \le P`$）

請注意雖然輸出的權限大小必須最小，但改變的道路數量可以是任意數量。
若有多組改變方案可以滿足要求，請輸出任意一組即可。

## 測資限制

* $`2 \le n \le 10^5`$
* $`0 \le m \le 10^5`$
* $`1 \le u_i, v_i \le n`$，且 $`u_i \neq v_i`$（$`i \in \{1, 2, \ldots, m\}`$）
* $`1 \le c_i \le 10^9`$（$`i \in \{1, 2, \ldots, m\}`$）
* 上面所有變數皆為整數

## 範例測試

## 評分說明

本題共有三組子任務，條件限制如下所示。
每一組可有一或多筆測試資料，該組所有測試資料皆需答對才會獲得該組分數。

|  子任務  |  分數  | 額外輸入限制 |
| :------: | :----: | ------------ |
| 1 | {{score.subtask1}} | $`n,m \le 20`$ |
| 2 | {{score.subtask2}} | $`c_i \le 100`$ |
| 3 | {{score.subtask3}} | 無額外限制 |
