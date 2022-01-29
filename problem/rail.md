# 鐵路鋪設 (rail)

## 問題描述

古力德市是一座相當特殊的城市。不同於一般的同心圓狀，古力德市是 $`2\times L`$ 的棋盤狀，從空中俯瞰就像一條巨大壯觀的蟒蛇，這個景色也吸引了不少觀光客。
近年來，為了提升觀光客訪問古力德市的體驗，古力德市政府決定在每一格的正中央設立火車站，並鋪設鐵路路線來連接這 $`2L`$ 座火車站。

一段鐵路連接相鄰兩個方格的車站，並根據這兩個方格是否為對角線相鄰分為**長鐵路**與**短鐵路**，如下圖所示。

\begin{minipage}{0.5\textwidth}
  \begin{figure}[H]
  \centering
  \begin{tikzpicture}[scale=1]
    \draw[step=1.0,black,thick] (0, 0) grid (2, 2);
    \draw[-,ultra thick,blue] (0.5, 0.5) -- (1.5, 1.5);
    \draw[step=1.0,black,thick] (4, 0) grid (6, 2);
    \draw[-,ultra thick,blue] (4.5, 1.5) -- (5.5, 0.5);
  \end{tikzpicture}
  \caption{兩種長鐵路}
  \end{figure}
\end{minipage}
\begin{minipage}{0.5\textwidth}
  \begin{figure}[H]
  \centering
  \begin{tikzpicture}[scale=1]
    \draw[step=1.0,black,thick] (0, 0) grid (2, 1);
    \draw[-,ultra thick,blue] (0.5, 0.5) -- (1.5, 0.5);
    \draw[step=1.0,black,thick] (4, 0) grid (5, 2);
    \draw[-,ultra thick,blue] (4.5, 0.5) -- (4.5, 1.5);
  \end{tikzpicture}
  \caption{兩種短鐵路}
  \end{figure}
\end{minipage}

若兩段鐵路共用同一座車站，則稱這兩段鐵路屬於同一條路線，當然**每座車站都要有一條路線經過**。
另，鋪設多條路線是被允許的，但因成本問題每一條路線**最多只能有一段長鐵路**。
最後，為了避免外地觀光客坐錯車降低訪問體驗，每條路線都必須是**環狀**的（確保搭乘順時針或逆時針方向的車都會抵達目的地），且任兩條路線**不會有任何的重疊或交叉**（意即每座車站皆恰有一條路線經過一次）。

給定古力德市的寬度 $`L`$，請求出有多少種可能的鋪設方式。因為這個數字可能很大，你只要求出鋪設方法數除以 $`10^9+7`$ 的餘數就行了。

以下為 $`L = 4`$ 的範例：在 $`2 \times 4`$ 的地圖中，共有 $`6`$ 種鋪設方式。

\begin{minipage}{0.33\textwidth}
  \begin{figure}[H]
  \centering
  \begin{tikzpicture}[scale=1]
    \def \cycles {
        {0/0/1/0, 1/0/2/0, 2/0/3/0, 3/0/3/1, 3/1/2/1, 2/1/1/1, 1/1/0/1, 0/1/0/0}}
    \draw[step=1.0,black,thick] (0, 0) grid (4, 2);
    \foreach \c in \cycles
    \foreach \xa / \ya / \xb / \yb in \c {
        \def\xc{\directlua{
            tex.sprint(\xa + 0.5)
        }}
        \def\yc{\directlua{
            tex.sprint(\ya + 0.5)
        }}
        \def\xd{\directlua{
            tex.sprint(\xb + 0.5)
        }}
        \def\yd{\directlua{
            tex.sprint(\yb + 0.5)
        }}
        \draw[-,ultra thick,blue] (\xc, \yc) -- (\xd, \yd);
    }
  \end{tikzpicture}
  \end{figure}
\end{minipage}
\begin{minipage}{0.33\textwidth}
  \begin{figure}[H]
  \centering
  \begin{tikzpicture}[scale=1]
    \def \cycles {
        {0/0/1/0, 1/0/1/1, 1/1/0/1, 0/1/0/0},
        {2/0/3/0, 3/0/3/1, 3/1/2/1, 2/1/2/0}}
    \draw[step=1.0,black,thick] (0, 0) grid (4, 2);
    \foreach \c in \cycles
    \foreach \xa / \ya / \xb / \yb in \c {
        \def\xc{\directlua{
            tex.sprint(\xa + 0.5)
        }}
        \def\yc{\directlua{
            tex.sprint(\ya + 0.5)
        }}
        \def\xd{\directlua{
            tex.sprint(\xb + 0.5)
        }}
        \def\yd{\directlua{
            tex.sprint(\yb + 0.5)
        }}
        \draw[-,ultra thick,blue] (\xc, \yc) -- (\xd, \yd);
    }
  \end{tikzpicture}
  \end{figure}
\end{minipage}
\begin{minipage}{0.33\textwidth}
  \begin{figure}[H]
  \centering
  \begin{tikzpicture}[scale=1]
    \def \cycles {
        {0/0/1/0, 1/0/2/0, 2/0/1/1, 1/1/0/1, 0/1/0/0},
        {3/0/3/1, 3/1/2/1, 2/1/3/0}}
    \draw[step=1.0,black,thick] (0, 0) grid (4, 2);
    \foreach \c in \cycles
    \foreach \xa / \ya / \xb / \yb in \c {
        \def\xc{\directlua{
            tex.sprint(\xa + 0.5)
        }}
        \def\yc{\directlua{
            tex.sprint(\ya + 0.5)
        }}
        \def\xd{\directlua{
            tex.sprint(\xb + 0.5)
        }}
        \def\yd{\directlua{
            tex.sprint(\yb + 0.5)
        }}
        \draw[-,ultra thick,blue] (\xc, \yc) -- (\xd, \yd);
    }
  \end{tikzpicture}
  \end{figure}
\end{minipage}

\begin{minipage}{0.33\textwidth}
  \begin{figure}[H]
  \centering
  \begin{tikzpicture}[scale=1]
    \def \cycles {
        {0/0/1/0, 1/0/2/1, 2/1/1/1, 1/1/0/1, 0/1/0/0},
        {2/0/3/0, 3/0/3/1, 3/1/2/0}}
    \draw[step=1.0,black,thick] (0, 0) grid (4, 2);
    \foreach \c in \cycles
    \foreach \xa / \ya / \xb / \yb in \c {
        \def\xc{\directlua{
            tex.sprint(\xa + 0.5)
        }}
        \def\yc{\directlua{
            tex.sprint(\ya + 0.5)
        }}
        \def\xd{\directlua{
            tex.sprint(\xb + 0.5)
        }}
        \def\yd{\directlua{
            tex.sprint(\yb + 0.5)
        }}
        \draw[-,ultra thick,blue] (\xc, \yc) -- (\xd, \yd);
    }
  \end{tikzpicture}
  \end{figure}
\end{minipage}
\begin{minipage}{0.33\textwidth}
  \begin{figure}[H]
  \centering
  \begin{tikzpicture}[scale=1]
    \def \cycles {
        {0/0/1/0, 1/0/0/1, 0/1/0/0},
        {2/0/3/0, 3/0/3/1, 3/1/2/1, 2/1/1/1, 1/1/2/0}}
    \draw[step=1.0,black,thick] (0, 0) grid (4, 2);
    \foreach \c in \cycles
    \foreach \xa / \ya / \xb / \yb in \c {
        \def\xc{\directlua{
            tex.sprint(\xa + 0.5)
        }}
        \def\yc{\directlua{
            tex.sprint(\ya + 0.5)
        }}
        \def\xd{\directlua{
            tex.sprint(\xb + 0.5)
        }}
        \def\yd{\directlua{
            tex.sprint(\yb + 0.5)
        }}
        \draw[-,ultra thick,blue] (\xc, \yc) -- (\xd, \yd);
    }
  \end{tikzpicture}
  \end{figure}
\end{minipage}
\begin{minipage}{0.33\textwidth}
  \begin{figure}[H]
  \centering
  \begin{tikzpicture}[scale=1]
    \def \cycles {
        {0/0/1/1, 1/1/0/1, 0/1/0/0},
        {1/0/2/0, 2/0/3/0, 3/0/3/1}, {3/1/2/1}, {2/1/1/0}}
    \draw[step=1.0,black,thick] (0, 0) grid (4, 2);
    \foreach \c in \cycles
    \foreach \xa / \ya / \xb / \yb in \c {
        \def\xc{\directlua{
            tex.sprint(\xa + 0.5)
        }}
        \def\yc{\directlua{
            tex.sprint(\ya + 0.5)
        }}
        \def\xd{\directlua{
            tex.sprint(\xb + 0.5)
        }}
        \def\yd{\directlua{
            tex.sprint(\yb + 0.5)
        }}
        \draw[-,ultra thick,blue] (\xc, \yc) -- (\xd, \yd);
    }
  \end{tikzpicture}
  \end{figure}
\end{minipage}

## 輸入格式

\begin{format}
\f{
$L$
}
\end{format}

- $`L`$ 為古力德市的寬度

## 輸出格式

\begin{format}
\f{
$\textrm{ans}$
}
\end{format}

- $`\textrm{ans}`$ 為一整數，代表鐵路鋪設方法數除以 $`10^9+7`$ 的餘數

## 測資限制

* $`1 \le L \le 10^{10}`$
* 輸入的數皆為整數

## 範例測試

## 評分說明

本題共有四組子任務，條件限制如下所示。
每一組可有一或多筆測試資料，該組所有測試資料皆需答對才會獲得該組分數。

|  子任務  |  分數  | 額外輸入限制 |
| :------: | :----: | ------------ |
| 1 | {{score.subtask1}} | $`L \le 7`$ |
| 2 | {{score.subtask2}} | $`L \le 10^3`$ |
| 3 | {{score.subtask3}} | $`L \le 10^5`$ |
| 4 | {{score.subtask4}} | 無額外限制 |
