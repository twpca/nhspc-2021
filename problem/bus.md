# 校園公車 (bus)

## 問題描述

H 大學設有校園公車在固定路線上來回行駛。
想搭乘校園公車的師生或訪客，可以在公車路線上的任意地點以招手方式請駕駛停靠後上車。
由於校園廣大，為方便師生與訪客利用校園公車，校方打算開發一個手機 app，
其中一個服務是透過 GPS 來定位出使用者在校園中的位置，提供最接近的上車地點。

H 大學校園內的任一位置皆能用二維座標 $`(x, y)`$ 表示。
校園公車的路線是由 $`n`$ 條線段所組成，我們以出發點 $`P_0(x_0, y_0)`$、轉折點 $`P_1(x_1, y_1), P_2(x_2, y_2), \ldots, P_{n-1}(x_{n-1}, y_{n-1})`$、以及終點 $`P_n(x_n, y_n)`$ 來描述。
在任意兩個相鄰的轉折點之間，公車以直線運行。
以下圖為例，公車路線為 $`P_0(1, 3), P_1(3, 3), P_2(5, 1), P_3(7, 2), P_4(7, 4), P_5(9, 3)`$。
如果手機使用者在 $`O_1(2, 1)`$，那麼 app 會回報最接近的上車地點在 $`A(2, 3)`$，距離是 $`2`$；
如果手機使用者在 $`O_2(5, 0)`$，那麼 app 會回報最接近的上車地點在 $`B(5, 1)`$，距離是 $`1`$。

\begin{figure}[h]
   \centering
   \begin{tikzpicture}[scale=1]
      \filldraw[black] (1, 3) circle (1pt) node[anchor=south east]{\small $P_0$};
      \filldraw[black] (3, 3) circle (1pt) node[anchor=south west]{\small $P_1$};
      \filldraw[black] (5, 1) circle (1pt) node[anchor=east]{\small $P_2$};
      \filldraw[black] (7, 2) circle (1pt) node[anchor=north west]{\small $P_3$};
      \filldraw[black] (7, 4) circle (1pt) node[anchor=south east]{\small $P_4$};
      \filldraw[black] (9, 3) circle (1pt) node[anchor=north west]{\small $P_5$};

      \filldraw[black] (2, 3) circle (1pt) node[anchor=south]{\small $A$};
      \filldraw[black] (5, 1) circle (1pt) node[anchor=south]{\small $B$};
      \draw (1, 3) -- (3, 3);
      \draw (3, 3) -- (5, 1);
      \draw (5, 1) -- (7, 2);
      \draw (7, 2) -- (7, 4);
      \draw (7, 4) -- (9, 3);
      \filldraw[red] (2, 1) circle (1pt) node[anchor=north]{\small $O_1$};
      \filldraw[red] (5, 0) circle (1pt) node[anchor=north]{\small $O_2$};
      \draw[dashed, color=red] (2, 1) -- (2, 3) node[midway,right] {\scriptsize $d=2$};
      \draw[dashed, color=red] (5, 0) -- (5, 1) node[midway,right] {\scriptsize $d=1$};
   \end{tikzpicture}
\end{figure}

給定一位 app 使用者的位置以及校園公車的路線，請寫一支程式來計算該使用者與最近上車地點的距離。

## 輸入格式

\begin{format}
\f{
$x$ $y$ $n$
$x_0$ $y_0$
$x_1$ $y_1$
\vdots
$x_n$ $y_n$
}
\end{format}

- $`(x, y)`$ 為使用者的位置
- $`n`$ 為校園公車路線的線段數
- $`(x_0, y_0), (x_1, y_1), \ldots, (x_n, y_n)`$ 為校園公車的路線（包含起點、轉折點與終點）

## 輸出格式

\begin{format}
\f{
$\textrm{ans}$
}
\end{format}

- $`\textrm{ans}`$ 為一非負浮點數，代表使用者與最近上車地點的距離

## 測資限制

* $`1 \le n \le 100`$
* $`0\le x, y\le10^6`$
* 對於所有的 $`i\in\{0, 1, \ldots, n\}`$，皆有 $`0 \le x_i, y_i \le 10^6`$
* 對於所有的 $`i\in\{0, 1, \ldots, n-1\}`$，皆有 $`(x_i, y_i)\ne(x_{i+1}, y_{i+1})`$
* 輸入的數皆為整數

## 範例測試

## 評分說明

本題共有三組子任務，條件限制如下所示。
每一組可有一或多筆測試資料，該組所有測試資料皆需答對才會獲得該組分數。
若正確答案非 $`0`$，輸出和正確答案的絕對或相對誤差在 $`10^{-6}`$ 就算正確。
若答案為 $`0`$，輸出必須要和正確答案絕對誤差在 $`10^{-6}`$ 以內。

|  子任務  |  分數  | 額外輸入限制 |
| :------: | :----: | ------------ |
| 1 | {{score.subtask1}} | 校園公車路線為一垂直或水平線段，且所有座標皆在 $`100`$ 以內 |
| 2 | {{score.subtask2}} | 校園公車路線的每一個線段都是垂直或水平 |
| 3 | {{score.subtask3}} | 無額外條件限制 |
