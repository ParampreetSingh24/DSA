class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        set<int> s;
        for(int i=0;i<nums.size();i++){
            s.insert(nums[i]);

        }
        int i=1; int ki=k;
        while(s.count(ki)!=0){
            i++;
            ki=k*i; 
        }
        return ki;
    }
};