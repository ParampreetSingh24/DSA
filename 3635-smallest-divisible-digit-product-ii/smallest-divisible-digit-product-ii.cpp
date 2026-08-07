class Solution {
public:
    string smallestNumber(string num, long long t) {
        long long remainingFactor = t;

        for (int factor = 2; factor <= 9; factor++) {
            while (remainingFactor % factor == 0) {
                remainingFactor /= factor;
            }
        }

        if (remainingFactor > 1) return "-1";

        int len = num.length();

        vector<long long> requiredFactor(len + 1);
        requiredFactor[0] = t;

        int firstZeroIndex = len - 1;
        vector<char> digits = num.data() ? vector<char>(num.begin(), num.end()) : vector<char>();

        for (int i = 0; i < len; i++) {
            if (digits[i] == '0') {
                firstZeroIndex = i;
                break;
            }

            requiredFactor[i + 1] =
                requiredFactor[i] / gcd(requiredFactor[i], (long long)(digits[i] - '0'));
        }

        if (requiredFactor[len] == 1)
            return num;

        for (int i = firstZeroIndex; i >= 0; i--) {
            while (++digits[i] <= '9') {
                long long currentNeed =
                    requiredFactor[i] /
                    gcd(requiredFactor[i], (long long)(digits[i] - '0'));

                for (int j = len - 1; j > i; j--) {
                    int candidateDigit = 9;

                    while (currentNeed % candidateDigit != 0)
                        candidateDigit--;

                    currentNeed /= candidateDigit;
                    digits[j] = (char)('0' + candidateDigit);
                }

                if (currentNeed == 1)
                    return string(digits.begin(), digits.end());
            }
        }

        string answer;
        long long remaining = t;

        for (int digit = 9; digit >= 2; digit--) {
            while (remaining % digit == 0) {
                answer += char('0' + digit);
                remaining /= digit;
            }
        }

        int extraOnes = max(len + 1 - (int)answer.length(), 0);

        while (extraOnes--)
            answer += '1';

        reverse(answer.begin(), answer.end());

        return answer;
    }
};