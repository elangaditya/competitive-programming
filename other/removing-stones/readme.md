# Problem Statement

- N stones laid in a line with two costs A and B.
- A[i] is the cost to remove stone[i] when stone[i - 1] or stone[i + 1] is not removed
- B[i] is the cost to remove stone[i] when stone[i - 1] and stone[i + 1] is not removed
- If there are no stones beside stone[i] cost to remove is 0
- Given N amount of stones and A[N] and B[N] calculate minimum cost to remove all stones

## Workings:

- dp[i][j]: cost to remove stone from range i - j
  - i : left boundary 0 <= i <= j
  - j : right boundary i <= j < N
