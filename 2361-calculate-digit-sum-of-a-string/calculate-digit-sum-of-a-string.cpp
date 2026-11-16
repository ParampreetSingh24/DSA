#include <string>
using namespace std;
class Solution {
public:
    string digitSum(string s, int k) {
        while (s.length() > k) {
            string next_s;
            next_s.reserve((s.length() + k - 1) / k * 2);
            for (int i = 0; i < s.length(); i += k) {
                int current_sum = 0;
                for (int j = i; j < i + k && j < s.length(); ++j) {
                    current_sum += s[j] - '0';
                }
                next_s += to_string(current_sum);
            }
            
            s = move(next_s);
        }return s;
    }
};