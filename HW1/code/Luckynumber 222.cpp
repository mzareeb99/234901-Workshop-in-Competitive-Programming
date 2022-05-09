#include <iostream>
#include <vector>
using namespace std;
typedef vector<bool> vb;
#define  MAX_SIZE 2000010
vb lucky_nums;
class segmentTree {
public:
    vector<int> vec;
    int size;
    segmentTree(){
        size = 2097152;
        vec = vector<int>(size * 4, 0);
        for (int i = 1; i < size; i += 2) {
            modify(i, 1);
        }
    }
    void modify(int p, int value) {
        for (vec[p += size] = value; p > 1; p /= 2)
            vec[p>>1] = vec[p] + vec[p^1];
    }
    int find_num_by_index(int index) {
        int i = 0;
        int current_node = 1;
        while (current_node < size) {
            if (vec[current_node * 2] + i >= index) {
                current_node *= 2;
            }
            else {
                i += vec[current_node * 2];
                (current_node *= 2)++;
            }
        }
        return current_node - size;
    }

    int get_num_of_bits_on() {
        return vec[1];
    }
};
void calc_lucky_nums() {
    lucky_nums[1] = true;
    segmentTree tree;
    for (int i = 2;
         i <= tree.get_num_of_bits_on();
         i++) {

        int next_lucky = tree.find_num_by_index(i);
        if (next_lucky >= lucky_nums.size()) {
            continue;
        }
        lucky_nums[next_lucky] = true;
        for (int j = next_lucky;
             j < tree.get_num_of_bits_on();
             j += (next_lucky - 1)) {

            int next_to_remove = tree.find_num_by_index(j);
            tree.modify(next_to_remove, 0);
        }
    }
}
int main() {
    lucky_nums = vector<bool>(MAX_SIZE,false);
    calc_lucky_nums();
    int next_num;
    while (cin >> next_num) {
        if (next_num % 2 == 1) {
            printf("%d is not the sum of two luckies!\n", next_num);
        }
        else {
            for (int i = next_num / 2; i > 0; i--) {
                if (lucky_nums[i] && lucky_nums[next_num - i]) {
                    printf("%d is the sum of %d and %d.\n", next_num, i, next_num - i);
                    break;
                }
            }
        }
    }
    return 0;
}
