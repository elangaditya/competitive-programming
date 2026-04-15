#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

const long long INF = 1e18; // Use a large enough value for infinity

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N;

    std::vector<long long> A(N);
    std::vector<long long> B(N);

    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }
    for (int i = 0; i < N; ++i) {
        std::cin >> B[i];
    }

    if (N == 1) {
        std::cout << 0 << std::endl;
        return 0;
    }

    // pref_A_sum[k] = A[0] + ... + A[k-1]
    std::vector<long long> pref_A_sum(N + 1, 0); 
    for(int i = 0; i < N; ++i) {
        pref_A_sum[i+1] = pref_A_sum[i] + A[i];
    }

    // left_dp[i]: minimum cost to remove stones 0 to i-1,
    // assuming stone i-1 is the LAST stone removed from this prefix (cost 0).
    std::vector<long long> left_dp(N + 1);
    left_dp[0] = 0; // Cost to remove an empty set of stones is 0.
    left_dp[1] = 0; // Cost to remove stone 0, as it's the last and only one from the prefix [0], is 0.

    // current_min_expr_L stores min(left_dp[j] + B[j] - pref_A_sum[j+1]) for 0 <= j < current_i - 1
    // where j is the index of the B-stone.
    // B[j] is only valid for 0 < j < N-1.
    long long current_min_expr_L = INF; 

    // Initial consideration for current_min_expr_L for j=1 (first valid B index)
    // For i=2, j can be 0. But B[0] is not valid.
    // The first stone that can be a B-stone is stone 1 (index 1).
    // This happens when i >= 3.
    // So for left_dp[2], only option1 is valid.
    // For left_dp[3], j=1 is possible. left_dp[1] + B[1] - pref_A_sum[2].
    // Let's set it up so that current_min_expr_L is only considered when j is valid (1 <= j <= N-2).

    for (int i = 2; i <= N; ++i) { // i represents number of stones in prefix (0 to i-1)
        // Option 1: Remove stones 0 to i-2 and then remove stone i-1 using A[i-1].
        // (Stone i-1 is the last removed from this segment and costs 0 from that perspective).
        // This is where previous A costs accumulate.
        long long option1_L = left_dp[i - 1] + A[i - 1]; 
        
        // Option 2: Some stone j (0 < j < i-1) was removed using B[j], splitting the segment.
        // Cost: (left_dp[j] for stones 0 to j-1, with j-1 free) + B[j] + sum(A[k] from j+1 to i-2).
        // Sum A[k] from j+1 to i-2 = pref_A_sum[i-1] - pref_A_sum[j+1]
        // This is (left_dp[j] + B[j] - pref_A_sum[j+1]) + pref_A_sum[i-1]

        // Update current_min_expr_L *before* using it for current i,
        // so it reflects choices for j up to i-2.
        // current_i corresponds to `i` in `left_dp[i]`. So `i-1` is the current stone.
        // `j` can go up to `i-2`. So, we update `current_min_expr_L` with `j = i-2` value.
        // Check for valid B index: 0 < (i-2) < N-1.
        if (i - 2 >= 1 && i - 2 <= N - 2) { // check if (i-2) is a valid B-stone index
            long long candidate_expr = left_dp[i-1] + B[i-1] - pref_A_sum[i];
            current_min_expr_L = std::min(current_min_expr_L, candidate_expr);
        } else if (i - 2 == 0) { // Special case for j=0 (not valid B, but for starting min_expr)
             // Not applicable for B[0]
        }

        long long option2_L = INF;
        if (current_min_expr_L != INF) {
            option2_L = current_min_expr_L + pref_A_sum[i-1];
        }
        
        left_dp[i] = std::min(option1_L, option2_L);
    }

    // Symmetrically for right_dp
    // right_dp[i]: minimum cost to remove stones i to N-1,
    // assuming stone i is the LAST stone removed from this suffix (cost 0).
    std::vector<long long> right_dp(N + 1);
    right_dp[N] = 0; // Cost to remove empty set of stones is 0.
    right_dp[N - 1] = 0; // Cost to remove stone N-1, as it's the last and only one from suffix [N-1], is 0.

    // suff_A_sum[k] = A[k] + ... + A[N-1]
    std::vector<long long> suff_A_sum(N + 1, 0); 
    for(int i = N - 1; i >= 0; --i) {
        suff_A_sum[i] = suff_A_sum[i + 1] + A[i];
    }

    // current_min_expr_R stores min(right_dp[j] + B[j] - suff_A_sum[j]) for current_i < j <= N-1
    // where j is the index of the B-stone.
    long long current_min_expr_R = INF;

    // For j=N-2 (first valid B index from right side)
    // Initial update for current_min_expr_R for j=N-2:
    // right_dp[N-1] is for N-1 free. So cost for N-1..N-1.
    // j here would be stone N-2. right_dp[N-2+1] + B[N-2] - suff_A_sum[N-2]
    // which is right_dp[N-1] + B[N-2] - suff_A_sum[N-2]
    if (N - 2 >= 1 && N - 2 <= N - 2) { // Check if N-2 is a valid B index
         current_min_expr_R = right_dp[N-1] + B[N-2] - suff_A_sum[N-2];
    }


    for (int i = N - 2; i >= 0; --i) { // i represents starting stone of suffix
        // Option 1: Remove stone i, with cost A[i], then remove the rest from i+1 to N-1.
        long long option1_R = right_dp[i + 1] + A[i];

        // Option 2: Some stone j (i < j < N-1) was removed using B[j], splitting the segment.
        // Cost: (right_dp[j] for stones j to N-1, with j free) + B[j] + sum(A[k] from i+1 to j-1)
        // Sum A[k] from i+1 to j-1 = suff_A_sum[i+1] - suff_A_sum[j]
        // This is (right_dp[j] + B[j] - suff_A_sum[j]) + suff_A_sum[i+1]
        
        // Update current_min_expr_R *before* using it for current i,
        // so it reflects choices for j from i+1 up to N-1.
        // Here, current_j for the update is i+1.
        // Check for valid B index: 0 < (i+1) < N-1.
        if (i + 1 >= 1 && i + 1 <= N - 2) { 
            long long candidate_expr = right_dp[i+1] + B[i+1] - suff_A_sum[i+1];
            current_min_expr_R = std::min(current_min_expr_R, candidate_expr);
        }

        long long option2_R = INF;
        if (current_min_expr_R != INF) {
            option2_R = current_min_expr_R + suff_A_sum[i+1];
        }
        
        right_dp[i] = std::min(option1_R, option2_R);
    }

    long long min_total_cost = INF;

    for (int k = 0; k < N; ++k) { // k is the stone removed for free
        long long current_total_cost = left_dp[k] + right_dp[k + 1];
        min_total_cost = std::min(min_total_cost, current_total_cost);
    }

    std::cout << min_total_cost << std::endl;

    return 0;
}
