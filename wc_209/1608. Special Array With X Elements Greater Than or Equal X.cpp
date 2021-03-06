// naive brute force O(N^2)
bool check(int num, vector<int> &nums) { 
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] >= num) 
            return (nums.size() - i) == num;                
    }
    return false;
}
int specialArray(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    for (int i = 0; i <= nums.size() ; i++) { // O(N)
        if (check(i, nums)) return i; // O(N)
    }
    return -1;
}

// just for fun short version  O(N^2)  O(NlogN + O(N) * (O(LogN) + O(N)))
int specialArray(vector<int>& nums) {
    multiset<int> s(nums.begin(), nums.end()); // O(NlogN)
    for (int i = 1; i <= nums.size(); i++) { // O(N)
        auto itr = s.lower_bound(i); // O(LogN) it's sorted 
        if (distance(itr, s.end()) == i) return i // O(N)
        // well multiset seems to be a rb tree which makes itr not a random-access iterator and therefore the time complexity for distance is linear 
    }
    return -1;
}
 
// improved version, O(NlogN) (O(NLogN) + O(NLogN))
int specialArray(vector<int>& nums) {
    sort(nums.begin(), nums.end()); // O(NlogN)
    for (int i = 1; i <= nums.size(); i++) { // O(N)
        auto itr = lower_bound(nums.begin(), nums.end(), i); // O(LogN)
        if (distance(itr, nums.end()) == i) return i; // O(1)
    }
    return -1;
}

// improved version pro max O(NlogN)  (O(NLogN) + (O(LogN) * O(LogN)) )
int specialArray(vector<int>& nums) {
    sort(nums.begin(), nums.end()); // O(NlogN)
    int l = 1, r = nums.size();
    while (l <= r) {
        int m = l + (r - l) / 2;
        auto itr = lower_bound(nums.begin(), nums.end(), m); // O(logN)
        int c = distance(itr, nums.end()); // O(1)
        if (c == m) return m;
        else if (c > m) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

// my friend's solution O(NLogN) (NlogN + OLogN)
int specialArray(vector<int>& nums) {
    sort(nums.begin(), nums.end());  // O(NlogN)
    const int N = nums.size();
    if (nums[0] >= N) return N;
    int l = 1, r = N - 1;
    while (l <= r) { // O(LogN) * O(1)
        int m = l + (r - l) / 2;
        if (nums[m] >= (N - m) && nums[m - 1] < (N - m)) return (N - m);
        else if (nums[m] >= (N - m)) r = m - 1;
        else l = m + 1;
    }
    return -1;

// counting sort, O(N) 2 pass
int specialArray(vector<int>& nums) {
    int count[102] = { 0 }, N = nums.size();
    for (int n : nums) count[min(n, N)]++;
    for (int i = N; i >= 0; i--) {
        count[i] = count[i + 1] + count[i];
        if (count[i] == i) return i;
    }
    return -1;
}
