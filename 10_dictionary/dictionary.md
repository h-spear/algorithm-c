# 사전

## 무순사전

insertItem : O(1)  
findElement : O(n)  
removeElement : O(n)

---

## 순서사전

insertItem : O(logn)  
findElement(이진탐색) : O(logn)  
findElement(선형탐색) : O(n)  
removeElement : O(n)

이진탐색 효율을 생각하면 배열로 구현하는 것이 유리하다.

---

### 분할통치 vs 이진탐색

분할통치 : 이등분된 두 개의 양쪽 범위를 모두 고려한다  
이진탐색 : 이등분된 두 개의 범위 중 한쪽만 고려한다

작동 원리는 비슷하지만 전체적인 작업 수행량은 이진탐색이 더 적음.
