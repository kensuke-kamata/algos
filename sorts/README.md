# Sorting Algorithms

## Theoretical Limit of Comparison-Based Sorting

When implementing sorting algorithms, it's important to understand the fundamental limitations of comparison-based sorting. Despite various approaches and optimizations, no comparison-based sorting algorithm can outperform the theoretical lower bound of $O(n \log n)$ in the average or worst case. This document provides an explanation for this limitation.

### Decision Tree Model

A decision tree is a binary tree representing the sequence of comparisons made by a sorting algorithm to sort an array. Each node represents a comparison, and each leaf represents a possible order of the array. For an array with $n$ distinct elements, there are $n!$ possible permutations.

```
A < B?
├─ Yes: A < C?
│       ├─ Yes: B < C?
│       │       ├─ Yes: [A, B, C]
│       │       └─ No: [A, C, B]
│       └─ No: [C, A, B]
└─ No: B < C?
        ├─ Yes: A < C?
        │       ├─ Yes: [B, A, C]
        │       └─ No: [B, C, A]
        └─ No: [C, B, A]

```

The decision tree for a sorting algorithm must have at least one leaf for each permutation to sort correctly, leading to a tree with at least $n!$ leaves. As a full binary tree with $h$ levels can have at most $2^h$ leaves, the height of the tree (representing the minimum number of comparisons) must satisfy the inequality $2^h \geq n!$.

### Introducing Stirling's Approximation

Stirling's approximation provides a way to estimate the logarithm of a factorial, which is useful in analyzing the complexity of sorting algorithms. The approximation is given by:

$$
n! \approx \sqrt{2 \pi n} \left(\frac{n}{e}\right)^n
$$

Taking the logarithm of both sides gives us:

$$
\log(n!) \approx \frac{1}{2} \log(2 \pi n) + n \log(n) - n \log(e)
$$

When $n$ is large, $\log(2\pi n)$ is negligibly small compared to $n\log(n)$, often simplified as follows:

$$
\log(n!) \approx n \log(n) - n
$$

### Applying Stirling's Approximation

When taking the logarithm base 2 of both sides of the decision tree leaf count inequality, we get:

$$
h \geq \log_2(n!)
$$

Using Stirling's approximation, the inequality becomes:

$$
h \geq n \log_2(n) - n \log_2(e)
$$

Here, $\log_2(e)$ is the constant factor converting the natural logarithm to base 2 logarithm. The resulting inequality illustrates that the minimum height $h$, and thus the minimum number of comparisons required by any comparison-based sorting algorithm, is proportional to $n \log n$. Consequently, this establishes $O(n \log n)$ as the lower bound for the average and worst-case performance of these algorithms.
