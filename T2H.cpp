#include <iostream>
#include <vector>

using std::cin, std::cout, std::vector;

struct longLong {
    uint8_t bytes[8] = {0};
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t N;
    vector <longLong> nums = {};
    cin >> N;
    for (int64_t i = 0; i < N; ++i) {
        uint64_t temp = 0;
        cin >> temp;
        longLong temp_LL = {};
        for (int j = 0; j < 8; ++j) {
            temp_LL.bytes[j] = temp % 256;
            temp >>= 8;
        }
        nums.push_back(temp_LL);
    }
    vector <longLong> nums2 = nums;
    uint64_t digit[256] = {0};
    for (int j = 0; j < 8; ++j) {
        for (int64_t i= 0; i < N; ++i) {
            ++digit[nums[i].bytes[j]];
        }
        for (uint16_t i = 1; i < 256; ++i) {
            digit[i] += digit[i - 1];
        }
        for (int64_t i = N - 1; i > -1; --i) {
            --digit[nums[i].bytes[j]];
            nums2[digit[nums[i].bytes[j]]] = nums[i];
        }
        nums = nums2;
        for (int16_t i = 0; i < 256; ++i) {
            digit[i] = 0;
        }
    }
    for (int64_t i = 0; i < N; ++i) {
        uint64_t tmp = 0;
        for (int j = 7; j > 0; --j) {
            tmp += nums[i].bytes[j];
            tmp <<= 8;
        }
        tmp += nums[i].bytes[0];
        cout << tmp << " ";
    }
    cout << '\n';
    return 0;
}
