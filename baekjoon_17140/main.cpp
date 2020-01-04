/*
 * 이차원 배열과 연산
 *
 * 배열 A의 크기는 3*3
 * 1초가 지날 때마다 R, C 연산 중 하나가 배열에 적용
 * - R 연산: 행의 개수 >= 열의 개수인 경우 배열 A의 모든 행에 대해 정렬 수행
 * - C 연산: 행의 개수 < 열의 개수인 경우 배열 A의 모든 열에 대해 정렬 수행
 *
 * 한 행/열의 수를 정렬하려면
 * - 각 수가 몇 번 나왔는지 알아야 한다.
 * - 수의 등장 횟수가 커지는 순으로, 만약 이러한 것이 여러가지면 수가 커지는 순으로 정렬한다.
 * - 그 다음으로 배열 A에 정렬된 결과를 다시 넣어야 한다.
 * - 정렬된 결과를 배열에 넣을 때에는 수의 등장 횟수를 모두 넣으며, 순서는 수가 먼저이다.
 */

#include <iostream>



int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}