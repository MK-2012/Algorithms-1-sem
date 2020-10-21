#include <iostream>
#include <vector>

using std::cin, std::cout, std::vector, std::string;

class Heap {
private:
    struct Pair {
        int64_t val = 0;
        int64_t req = 0;
    };
    int64_t size = 0;
    vector <Pair> heap = {{100000000, -1}};
    vector <int64_t> alignment = {-1};
    void siftUp(int64_t ind) {
        int64_t i = ind;
        while ((i > 1) && (heap[i].val < heap[i / 2].val)) {
            Pair temp_pair;
            temp_pair = heap[i];
            heap[i] = heap[i / 2];
            heap[i / 2] = temp_pair;
            int64_t temp;
            temp = alignment[heap[i].req];
            alignment[heap[i].req] = alignment[heap[i / 2].req];
            alignment[heap[i / 2].req] = temp;
            i /= 2;
        }
    }
    void siftDown(int64_t ind) {
        int64_t i = ind;
        while (2 * i <= size) {
            int64_t j = -1;
            if (heap[2 * i].val < heap[i].val) {
                j = 2 * i;
            }
            if ((2 * i + 1 <= size) && (heap[2 * i + 1].val < heap[i].val) && ((j == -1) || (heap[2 * i].val > heap[2 * i + 1].val))) {
                j = 2 * i + 1;
            }
            if (j == -1) {
                break;
            } else {
                Pair temp_pair;
                temp_pair = heap[i];
                heap[i] = heap[j];
                heap[j] = temp_pair;
                int64_t temp;
                temp = alignment[heap[i].req];
                alignment[heap[i].req] = alignment[heap[j].req];
                alignment[heap[j].req] = temp;
                i = j;
            }
        }
    }
public:
    int64_t getMin() {
        alignment.push_back(-1);
        int64_t tmp;
        tmp = heap[1].val;
        return tmp;
    }
    void insert(int64_t a) {
        heap.push_back({a, alignment.size()});
        ++size;
        alignment.push_back(size);
        siftUp(size);
    }
    void decreaseKey(int64_t ind, int64_t delta) {
        heap[alignment[ind]].val -= delta;
        siftUp(alignment[ind]);
        alignment.push_back(-1);
    }
    void extractMin() {
        alignment[heap[1].req] = -1;
        alignment[heap[size].req] = 1;
        heap[1] = heap[size];
        --size;
        heap.pop_back();
        siftDown(1);
        alignment.push_back(-1);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    Heap heap;
    int64_t n;
    cin >> n;
    for (int64_t i = 0; i < n; ++i) {
        string str;
        int64_t a = 0;
        int64_t delta = 0;
        cin >> str;
        switch (str[0]) {
            case 'i':
                cin >> a;
                heap.insert(a);
                break;
            case 'g':
                int64_t temp;
                temp = heap.getMin();
                cout << temp << '\n';
                break;
            case 'e':
                heap.extractMin();
                break;
            case 'd':
                cin >> a >> delta;
                heap.decreaseKey(a, delta);
                break;
        }
    }
    return 0;
}
