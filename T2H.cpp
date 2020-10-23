#include <iostream>
#include <vector>

using std::cin, std::cout, std::vector;

struct longLong {
    uint8_t byte1 = 0;
    uint8_t byte2 = 0;
    uint8_t byte3 = 0;
    uint8_t byte4 = 0;
    uint8_t byte5 = 0;
    uint8_t byte6 = 0;
    uint8_t byte7 = 0;
    uint8_t byte8 = 0;
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
        temp_LL.byte1 = temp % 256;
        temp >>= 8;
        temp_LL.byte2 = temp % 256;
        temp >>= 8;
        temp_LL.byte3 = temp % 256;
        temp >>= 8;
        temp_LL.byte4 = temp % 256;
        temp >>= 8;
        temp_LL.byte5 = temp % 256;
        temp >>= 8;
        temp_LL.byte6 = temp % 256;
        temp >>= 8;
        temp_LL.byte7 = temp % 256;
        temp >>= 8;
        temp_LL.byte8 = temp;
        nums.push_back(temp_LL);
    }
    vector <longLong> nums2 = nums;
    uint64_t digit[256] = {0};
    for (int64_t i= 0; i < N; ++i) {
        ++digit[nums[i].byte1];
    }
    for (uint16_t i = 1; i < 256; ++i) {
        digit[i] += digit[i - 1];
    }
    for (int64_t i = N - 1; i > -1; --i) {
        --digit[nums[i].byte1];
        nums2[digit[nums[i].byte1]] = nums[i];
    }
    nums = nums2;
    for (int16_t i = 0; i < 256; ++i) {
        digit[i] = 0;
    }
    for (int64_t i= 0; i < N; ++i) {
        ++digit[nums[i].byte2];
    }
    for (uint16_t i = 1; i < 256; ++i) {
        digit[i] += digit[i - 1];
    }
    for (int64_t i = N - 1; i > -1; --i) {
        --digit[nums[i].byte2];
        nums2[digit[nums[i].byte2]] = nums[i];
    }
    nums = nums2;
    for (int16_t i = 0; i < 256; ++i) {
        digit[i] = 0;
    }
    for (int64_t i= 0; i < N; ++i) {
        ++digit[nums[i].byte3];
    }
    for (uint16_t i = 1; i < 256; ++i) {
        digit[i] += digit[i - 1];
    }
    for (int64_t i = N - 1; i > -1; --i) {
        --digit[nums[i].byte3];
        nums2[digit[nums[i].byte3]] = nums[i];
    }
    nums = nums2;
    for (int16_t i = 0; i < 256; ++i) {
        digit[i] = 0;
    }
    for (int64_t i= 0; i < N; ++i) {
        ++digit[nums[i].byte4];
    }
    for (uint16_t i = 1; i < 256; ++i) {
        digit[i] += digit[i - 1];
    }
    for (int64_t i = N - 1; i > -1; --i) {
        --digit[nums[i].byte4];
        nums2[digit[nums[i].byte4]] = nums[i];
    }
    nums = nums2;
    for (int16_t i = 0; i < 256; ++i) {
        digit[i] = 0;
    }
    for (int64_t i= 0; i < N; ++i) {
        ++digit[nums[i].byte5];
    }
    for (uint16_t i = 1; i < 256; ++i) {
        digit[i] += digit[i - 1];
    }
    for (int64_t i = N - 1; i > -1; --i) {
        --digit[nums[i].byte5];
        nums2[digit[nums[i].byte5]] = nums[i];
    }
    nums = nums2;
    for (int16_t i = 0; i < 256; ++i) {
        digit[i] = 0;
    }
    for (int64_t i= 0; i < N; ++i) {
        ++digit[nums[i].byte6];
    }
    for (uint16_t i = 1; i < 256; ++i) {
        digit[i] += digit[i - 1];
    }
    for (int64_t i = N - 1; i > -1; --i) {
        --digit[nums[i].byte6];
        nums2[digit[nums[i].byte6]] = nums[i];
    }
    nums = nums2;
    for (int16_t i = 0; i < 256; ++i) {
        digit[i] = 0;
    }
    for (int64_t i= 0; i < N; ++i) {
        ++digit[nums[i].byte7];
    }
    for (uint16_t i = 1; i < 256; ++i) {
        digit[i] += digit[i - 1];
    }
    for (int64_t i = N - 1; i > -1; --i) {
        --digit[nums[i].byte7];
        nums2[digit[nums[i].byte7]] = nums[i];
    }
    nums = nums2;
    for (int16_t i = 0; i < 256; ++i) {
        digit[i] = 0;
    }
    for (int64_t i= 0; i < N; ++i) {
        ++digit[nums[i].byte8];
    }
    for (uint16_t i = 1; i < 256; ++i) {
        digit[i] += digit[i - 1];
    }
    for (int64_t i = N - 1; i > -1; --i) {
        --digit[nums[i].byte8];
        nums2[digit[nums[i].byte8]] = nums[i];
    }
    nums = nums2;
    for (int16_t i = 0; i < 256; ++i) {
        digit[i] = 0;
    }
    for (int64_t i = 0; i < N; ++i) {
        uint64_t tmp = 0;
        tmp += nums[i].byte8;
        tmp <<= 8;
        tmp += nums[i].byte7;
        tmp <<= 8;
        tmp += nums[i].byte6;
        tmp <<= 8;
        tmp += nums[i].byte5;
        tmp <<= 8;
        tmp += nums[i].byte4;
        tmp <<= 8;
        tmp += nums[i].byte3;
        tmp <<= 8;
        tmp += nums[i].byte2;
        tmp <<= 8;
        tmp += nums[i].byte1;
        cout << tmp << " ";
    }
    cout << '\n';
    return 0;
}
