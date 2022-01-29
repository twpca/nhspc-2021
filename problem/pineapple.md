# 鳳梨關稅 (pineapple)

## 問題描述

大洋上有 $`n`$ 個島嶼聚落，為了方便起見將這些聚落從 $`1`$ 到 $`n`$ 編號。
這些島嶼聚落使用著共通的貨幣大洋銀幣。
聚落間有繁盛的貿易，並且在這些聚落之間有一些固定的航線往來，這些航線是聚落間的交流與物產貿易的主要手段。
每一條航線都是往返於固定兩個聚落。
若一航線是往返於聚落 $`u`$ 與聚落 $`v`$，則以 $`\{u, v\}`$ 或 $`\{v, u\}`$ 表示該航線，
兩種表示方法相同，代表聚落 $`u`$ 與聚落 $`v`$ 可以直航交易兩地物產。
如果聚落 $`u`$ 與聚落 $`v`$ 之間沒有航線直接往返，也可能透過複數條航線進行貿易。
若存在一系列的航線 $`\{u, p_1\}, \{p_1, p_2 \}, \ldots, \{p_{r-1}, p_r\}, \{p_r, v\}`$，
則聚落 $`u`$ 與聚落 $`v`$ 之間便可以進行貿易，反之則不可以。

為了保護大洋的生態，所有聚落的共識是在任兩個島嶼聚落之間都能夠進行貿易往來的前提下維持盡可能少的航線，
而經過一番推算後，僅需有 $`n - 1`$ 條航線便足夠。
這些可以進行貿易的固定航線，編號從 $`1`$ 到 $`n – 1`$，分別以 $`\{u_1, v_1\}, \{u_2,v_2\}, \ldots, \{u_{n - 1}, v_{n - 1}\}`$ 表示。

在這片大洋上，每個聚落為了保護自己內部的產業不受到外部的低價商品傾銷、惡性競爭，因此針對各項商品都設定有關稅。
而在大洋上關稅課徵的方式是針對航線，在每一航線上，船上所裝載的商品都要被抽一次稅金。
依據商品的種類不同有不同的抽稅方式；而針對鳳梨，則是每一顆裝載在船上的鳳梨都要被課徵一枚大洋銀幣。

貢丸居住在大洋上的米粉島，最近退休了在種鳳梨想要販售到大洋的其他聚落去。
貢丸建立了自己的品牌「貢丸鳳梨」，由於品質優良，口碑良好，他開始收到來自其他聚落的鳳梨訂單。
為了要賺多一點錢，他總會想辦法準備好鳳梨出口到其他島嶼去，並且依照被收取的關稅來調整售價。

近年自由貿易的風潮興起，有些航線開始針對特定的商品免除關稅，鳳梨也在其中。
隨著時間經過，貢丸需要不斷的依據變更的關稅來調整貢丸鳳梨的價格，避免過高的定價，傷害到貢丸鳳梨在市場上的競爭力。

\newpage
下面是一個例子，假設有 $`n=5`$ 個島嶼聚落，與 $`4`$ 條航線 $`\{1,2\}, \{2, 3\}, \{2, 4\}, \{5, 2\}`$，
米粉島的編號是 $`1`$，並有 $`3`$ 筆訂單如下：

1. 出貨 $`5`$ 顆鳳梨到編號 $`5`$ 的島嶼
1. 出貨 $`2`$ 顆鳳梨到編號 $`3`$ 的島嶼
1. 出貨 $`5`$ 顆鳳梨到編號 $`5`$ 的島嶼

在前兩筆訂單之間，航線 $`\{2, 3\}`$ 將會免除鳳梨的關稅，
在後兩筆訂單之間，航線 $`\{5, 2\}`$ 將會免除鳳梨的關稅，
所以三筆訂單分別會被課徵每顆鳳梨$`2`$、$`1`$、$`1`$枚大洋銀幣。
下面三個圖為每一次免稅後的航線圖，其中虛線為免關稅路線。

\begin{minipage}{0.33\textwidth}
  \begin{figure}[H]
  \centering
  \begin{tikzpicture}[scale=0.75]
    \foreach \x in {0,72,...,338} {
        \def\id{\directlua{tex.sprint(\x // 72 + 1)}}
        \node[circle,draw,minimum size=0.5cm] (\id) at (\x+90:2) {$\id$};
    }
    \path[draw,thick,-,black] (1) -- (2);
    \path[draw,thick,-,black] (2) -- (3);
    \path[draw,thick,-,black] (2) -- (4);
    \path[draw,thick,-,black] (2) -- (5);
  \end{tikzpicture}
  \caption{(a): 初始航線圖}
  \end{figure}
\end{minipage}
\begin{minipage}{0.33\textwidth}
  \begin{figure}[H]
  \centering
  \begin{tikzpicture}[scale=0.75]
    \foreach \x in {0,72,...,338} {
        \def\id{\directlua{tex.sprint(\x // 72 + 1)}}
        \node[circle,draw,minimum size=0.5cm] (\id) at (\x+90:2) {$\id$};
    }
    \path[draw,thick,-,black] (1) -- (2);
    \path[draw,thick,-,black,dashed] (2) -- (3);
    \path[draw,thick,-,black] (2) -- (4);
    \path[draw,thick,-,black] (2) -- (5);
  \end{tikzpicture}
  \caption{(b): 第一次免稅調整後}
  \end{figure}
\end{minipage}
\begin{minipage}{0.33\textwidth}
  \begin{figure}[H]
  \centering
  \begin{tikzpicture}[scale=0.75]
    \foreach \x in {0,72,...,338} {
        \def\id{\directlua{tex.sprint(\x // 72 + 1)}}
        \node[circle,draw,minimum size=0.5cm] (\id) at (\x+90:2) {$\id$};
    }
    \path[draw,thick,-,black] (1) -- (2);
    \path[draw,thick,-,black,dashed] (2) -- (3);
    \path[draw,thick,-,black] (2) -- (4);
    \path[draw,thick,-,black,dashed] (2) -- (5);
  \end{tikzpicture}
  \caption{(c): 第二次免稅調整後}
  \end{figure}
\end{minipage}

貢丸的祕書幫忙他整理明年需要出貨的訂單，以及航線調整關稅的時程，貢丸想要請精打細算的你，
幫忙撰寫一個程式，算出每一筆訂單需要繳交多少關稅才能出貨給顧客。

## 輸入格式

\begin{format}
\f{
$n$ $s$ $t$ $w$
$u_1$ $v_1$
$u_2$ $v_2$
$\vdots$
$u_{n-1}$ $v_{n-1}$
$\textrm{Query}_1$
$\textrm{Query}_2$
$\vdots$
$\textrm{Query}_{t+w}$
}
\end{format}

- $`n`$、$`s`$、$`t`$、$`w`$ 分別代表島嶼聚落數量、米粉島的編號、明年訂單總數及調整關稅航線的總數。
- $`u_i`$、$`v_i`$ 代表第 $`i`$ 條航線會在島嶼聚落 $`u_i`$、$`v_i`$ 間往返。
- $\textrm{Query}_i$ 代表第 $`i`$ 個出貨或變更航線的資訊，越前面代表事件越先發生。$\textrm{Query}_i$ 有以下兩種可能的格式:

1. 出貨 $`x`$ 顆鳳梨到編號 $`y`$ 的聚落
\begin{format}
\f{
$1$ $x$ $y$
}
\end{format}

2. 航線 $`z`$ 免稅
\begin{format}
\f{
$2$ $z$
}
\end{format}

## 輸出格式

\begin{format}
\f{
$a_1$
$a_2$
\vdots
$a_t$
}
\end{format}

- $`a_i`$ 代表第 $`i`$ 筆訂單所需繳納的關稅總額

## 測資限制

* $`1 \le n \le 10^5`$
* $`1 \le s \le n`$
* $`1 \le t \le 10^5`$
* $`0 \le w < n`$
* $`1 \le u_i, v_i \le n`$，且 $`u_i \neq v_i`$
* 任意聚落都可以透過給定航線互相航行
* $`1 \le x \le 10^5`$
* $`1 \le y \le n`$
* $`1 \le z \le n-1`$，免稅資訊中相同的 $`z`$ 不會重複出現
* $`\textrm{Query}_1`$ 到 $`\textrm{Query}_{t+w}`$ 中恰有 $`t`$ 個出貨詢問以及 $`w`$ 個免稅事件
* 上述變數皆為整數

## 範例測試

## 評分說明

本題共有三組子任務，條件限制如下所示。
每一組可有一或多筆測試資料，該組所有測試資料皆需答對才會獲得該組分數。

|  子任務  |  分數  | 額外輸入限制 |
| :------: | :----: | ------------ |
| 1 | {{score.subtask1}} | $`n \le 100`$，$`x \le 1000`$ |
| 2 | {{score.subtask2}} | 只有一條航線會停靠米粉島，且其餘島嶼聚落至多只有兩條航線會停靠 |
| 3 | {{score.subtask3}} | 無額外限制 |
