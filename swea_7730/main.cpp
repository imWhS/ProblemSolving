/*
 7730 나무 깎는 홍준

 홍준이가 가구를 만들기 위해 필요한 원목의 총 길이는 M 이다.
 나무들을 잘라야 원목을 얻을 수 있다.
 나무는 N 개가 있으며, 길이는 제각각이다.
 홍준이는 한 번만 팔을 H 높이만큼 휘둘러 나무들을 자를 수 있다. 이 때 나무는 H보다 높아야 잘릴 수 있다.
 H 보다 높은 나무가 H 만큼 잘린 후 남은 나무 길이의 합이 원목의 길이가 된다.
 Ex. H = 18, 각 나무 높이가 15, 20, 23, 18일 때 20, 23 높이를 가진 나무가 잘리며, 잘린 후 남은 나무 길이 합인 2 + 5 = 7 이 원목의 길이가 된다.

 input
 T
 나무의 수 N (1 <= N <= 1000000), 필요한 원목의 총 길이 M (1 <= M <= 2000000000)
 각 나무 별 높이 (각 나무의 높이 <= 1000000000, 모든 나무 길이의 합은 M 이상 임을 보장)

 output
 필요한 원목의 총 길이 M 만큼 얻기 위한 나무 절단 높이 H 최대 값
 */

#include <iostream>

using namespace std;

long long N, M;
long long tree[1000001];

long long max_height;

int solution() {
    long long base = 0, end = max_height, mid;
    long long sum, result = 0;

    while(base <= end) {
        sum = 0;
        mid = (base + end) / 2;
        //조건에 맞는 나무 순차 탐색
        for(long long n = 1; n <= N; n++) {
            //절단 높이보다 높지 않은 나무는 무시
            if(tree[n] <= mid) continue;
            //절단 후 남은 높이를 원목 길이 합에 포함
            sum += tree[n] - mid;
        }

        //해당 H에서의 원목 총 길이 M 도달 여부 확인
        if(sum >= M) {
            //더 좁은 범위에서도 재시도하기 위해 base 오프셋 조정
            base = mid + 1;
            result = mid;
        } //M 도달한 경우 H 값 출력
        else end = mid - 1; //잘린 나무가 없거나 M 도달 못한 경우 다음 더 넓은 범위의 H 값으로 재시도
    }

    return result;
}

int main() {
    int T;
    cin >> T;
    for(int t = 1; t <= T; t++) {
        cin >> N >> M;
        for(long long n = 1; n <= N; n++) {
            cin >> tree[n];
            if(max_height < tree[n]) max_height = tree[n];
        }

        cout << '#' << t << ' ' << solution() << endl;

        //reset N, M, tree
        N = 0, M = 0, max_height = 0;
        for(long long n = 1; n <= N; n++) tree[n] = 0;
    }

    return 0;
}
