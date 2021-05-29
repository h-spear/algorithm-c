# 해시테이블

- 키-주소 매핑에 의해 구현된 사전ADT
- HashTable = bucket array + hash function

## 버켓배열

---

해시테이블을 구현한 1차원 배열<br><br>

## 해시함수

---

해시함수 h는 주어진 형의 키를 고정 범위 [0, M-1]로 매핑

- 키들을 외견상 무작위하게(random) 해시테이블에 분산시켜야 한다.
- 계산이 빠르고 쉬워야 한다 O(1)<br><br>

## collision

---

collision(충돌) : 두 개 이상의 원소들이 동일한 셀로 매핌됨, h(k_1) = h(k_2)<br><br>

collision resolution

1. 분리연쇄법(separate chaining, chaining)

- 단순하고 빠르다.
- 추가적인 저장공간을 필요로 한다.

2. 개방주소법(open addressing)

- 충돌항목이 테이블의 다른 셀에 저장된다.
- 공간을 절약하지만 삭제가 어렵다.
- 군집화(clustering)
- 선형조사법, 2차 조사법, 이중해싱..
