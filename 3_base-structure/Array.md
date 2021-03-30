# Array

> V : array name<br>
> N : array size<br>
> i : array index<br>
>
> - 시작: 0 또는 LB(lower bound)
> - 끝 : N-1 또는 UB(upper bound)
>
> base : 배열의 첫 번째 셀 위치(LB)

## 1차원 배열

> ## V[LB..UB]
>
> ---
>
> V[i] : array element<br>
> V[k]의 offset = k - LB

## 2차원 배열

> ## V[LB<sub>1</sub>..UB<sub>1</sub>, LB<sub>2</sub>..UB<sub>2</sub>]
>
> ---
>
> table(row, column)<br>
> V[k<sub>1</sub>,k<sub>2</sub>]의 offset = (k<sub>1</sub>-LB<sub>1</sub>)(UB<sub>2</sub>-LB<sub>2</sub>+1)+(k<sub>2</sub>-LB<sub>2</sub>)

## 3차원 배열

> ## V[LB<sub>1</sub>..UB<sub>1</sub>, LB<sub>2</sub>..UB<sub>2</sub>, LB<sub>3</sub>..UB<sub>3</sub>]
>
> ---
>
> 가로, 세로, 높이<br>
> V[k<sub>1</sub>,k<sub>2</sub>,k<sub>3</sub>]의 offset = (k<sub>1</sub>-LB<sub>1</sub>)(UB<sub>2</sub>-LB<sub>2</sub>+1)(UB<sub>3</sub>-LB<sub>3</sub>+1)+(k<sub>2</sub>-LB<sub>2</sub>)(UB<sub>3</sub>-LB<sub>3</sub>+1)+(k<sub>3</sub>-LB<sub>3</sub>)
