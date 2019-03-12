#pragma once

#include <memory>

// Here is the signature for cutRodNaive. The int& means that the
// parameter is being called by reference. So to increment
// callcount you will do the following:
//      callcount++;
int cutRodNaive(int *p, int n, int &callCount) {
    callCount++;
    if (n == 0) return 0;
    int q = std::numeric_limits<int>::min();

    for (int i = 1; i <= n; i++) {
        q = std::max(q, p[i] + cutRodNaive(p, n - i, callCount));
    }
    return q;
}

// Here is the signature for cutRodMemoImpl, which is the
// implementation function for cut rod using memoization.
// Recall that arrays can be passed as a pointer to an int.
int cutRodMemoImpl(const int *p, int n, int *memos, int &callCount) {
    callCount++;
    if (memos[n] >= 0) {
        return memos[n];
    }
    int q;
    if (n == 0) {
        q = 0;
    } else {
        q = std::numeric_limits<int>::min();
        for (int i = 1; i <= n; i++) {
            q = std::max(q, p[i] + cutRodMemoImpl(p, n - i, memos, callCount));
        }
    }
    memos[n] = q;
    return q;
}

// Here is the signature for cutRodMemo.
int cutRodMemo(const int *p, int n, int &callCount) {
    std::unique_ptr<int[]> memos{new int[n + 1]};
    std::fill(memos.get(), memos.get() + n + 1, std::numeric_limits<int>::min());
    return cutRodMemoImpl(p, n, memos.get(), callCount);
}

int fibNaive(int index, int &callCount) {
    callCount++;
    if (index == 0 || index == 1) {
        return 1;
    }
    return fibNaive(index - 1, callCount) + fibNaive(index - 2, callCount);
}

int fibMemoImpl(int index, int *memo, int &callCount) {
    callCount++;
    if (memo[index] >= 0) {
        return memo[index];
    }
    int result;
    if (index == 0 || index == 1) {
        result = 1;
    } else {
        result = fibMemoImpl(index - 1, memo, callCount) + fibMemoImpl(index - 2, memo, callCount);
    }
    memo[index] = result;
    return result;
}

int fibMemo(int index, int &callCount) {
    std::unique_ptr<int[]> memo { new int[index + 1] };
    std::fill(memo.get(), memo.get() + index + 1, -1);
    return fibMemoImpl(index, memo.get(), callCount);
}