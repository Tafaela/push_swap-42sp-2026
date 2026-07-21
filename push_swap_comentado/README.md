*This project has been created as part of the 42 curriculum by bramos, <LOGIN>.*

# push_swap

## Description

**push_swap** is a sorting algorithm project from the 42 School curriculum. The goal is to sort a list of integers using two stacks (`a` and `b`) and a limited set of operations, while minimizing the total number of operations performed.

The program receives a list of integers as arguments (representing stack `a`) and outputs the optimal sequence of operations to sort them in ascending order.

### Available Operations

| Operation | Description |
|-----------|-------------|
| `sa` | Swap the top 2 elements of stack a |
| `sb` | Swap the top 2 elements of stack b |
| `ss` | `sa` and `sb` simultaneously |
| `pa` | Push top of b to top of a |
| `pb` | Push top of a to top of b |
| `ra` | Rotate stack a upward (top → bottom) |
| `rb` | Rotate stack b upward (top → bottom) |
| `rr` | `ra` and `rb` simultaneously |
| `rra` | Reverse rotate stack a (bottom → top) |
| `rrb` | Reverse rotate stack b (bottom → top) |
| `rrr` | `rra` and `rrb` simultaneously |

---

## Instructions

### Compilation

```bash
# Compile push_swap
make

# Compile the bonus checker
make bonus

# Clean object files
make clean

# Full clean (objects + binaries)
make fclean

# Recompile everything
make re
```

### Usage

```bash
# Basic usage (adaptive strategy by default)
./push_swap 4 67 3 87 23

# Force a specific strategy
./push_swap --simple   5 4 3 2 1
./push_swap --medium   5 4 3 2 1
./push_swap --complex  5 4 3 2 1
./push_swap --adaptive 5 4 3 2 1

# Enable benchmark output (stderr)
./push_swap --bench --adaptive 4 67 3 87 23

# Count operations
ARG="4 67 3 87 23"; ./push_swap --adaptive $ARG | wc -l

# Verify correctness with checker
ARG="4 67 3 87 23"; ./push_swap --complex $ARG | ./checker $ARG

# Verify with provided checker binary (Linux)
ARG="4 67 3 87 23"; ./push_swap --complex $ARG | ./checker_linux $ARG
```

### Checker Usage

```bash
# Reads operations from stdin, outputs OK or KO
printf "sa\n" | ./checker 2 1
# → OK

printf "sa\n" | ./checker 1 2
# → KO
```

### Error Handling

```bash
./push_swap 0 one 2 3       # Error: non-integer
./push_swap 3 2 3            # Error: duplicate
./push_swap 2147483648       # Error: overflow
./push_swap ""               # Error: empty string
```

---

## Algorithm Design

### Disorder Metric

Before sorting, the program computes a **disorder** value between 0 and 1:

```
disorder = (number of inverted pairs) / (total pairs)
```

- `0.0` → already sorted
- `1.0` → worst case (fully reversed)

### Four Required Strategies

#### 1. Simple — O(n²): Selection Sort Adaptation

Repeatedly finds the minimum element in stack `a`, rotates it to the top, and pushes it to `b`. After pushing all but the last element, pushes everything back from `b` to `a`.

- **Complexity**: O(n²) operations
- **Best for**: n ≤ 5, nearly sorted arrays (disorder < 0.1)

#### 2. Medium — O(n√n): Chunk-Based Sorting

Divides the index range into `√n` chunks. For each chunk, elements in that range are pushed to `b` (with partial sorting). Then elements are pulled back from `b` to `a` in descending order.

- **Complexity**: O(n√n) operations
- **Best for**: Medium-sized inputs with medium disorder

#### 3. Complex — O(n log n): Turk Sort (≤200 elements) / Radix Sort (>200 elements)

**Turk Sort** (for n ≤ 200):
- Push all elements to `b`, maintaining a descending order.
- For each push, find the cheapest element in `a` to move (combined rotation cost to align both stacks).
- Use combined `rr` / `rrr` operations to minimize moves.
- After `sort_simple` on remaining 3 in `a`, pull from `b` inserting each element at its correct sorted position in `a`.

**Radix Sort LSD** (for n > 200):
- Treat element indices as binary numbers.
- For each bit position (LSB to MSB): push elements with bit=0 to `b`, rotate elements with bit=1 in `a`. Then pull all back.
- Each pass is O(n), with O(log n) passes → O(n log n) total.

#### 4. Adaptive Strategy

Selects the algorithm based on input size and measured disorder:

| Condition | Strategy |
|-----------|----------|
| n ≤ 5 | Simple O(n²) |
| disorder < 0.2 | Simple O(n²) |
| 0.2 ≤ disorder < 0.5 | Medium O(n√n) |
| disorder ≥ 0.5 | Complex O(n log n) (Turk ≤200 / Radix >200) |

**Threshold Rationale:**
- The subject mandates fixed disorder thresholds (0.2 / 0.5) for the adaptive
  strategy's regime selection, so these exact values are used rather than
  tuned constants.
- Below 0.2 disorder, the list is close enough to sorted that the low
  overhead of the O(n²) selection-based approach outperforms the setup cost
  of chunking or partitioning.
- Between 0.2 and 0.5, chunk-based O(n√n) sorting balances overhead against
  the amount of disorder to fix.
- At 0.5 disorder or higher, the O(n log n) strategy (Turk sort for n ≤ 200,
  Radix sort for n > 200) is required to keep the operation count low on
  heavily shuffled inputs.

### Complexity Summary (Push_swap operation model)

| Algorithm | Time | Space |
|-----------|------|-------|
| Simple (Selection) | O(n²) | O(1) extra |
| Medium (Chunk) | O(n√n) | O(1) extra |
| Complex/Turk | O(n log n) avg | O(1) extra |
| Complex/Radix LSD | O(n log n) | O(1) extra |
| Adaptive | Depends on disorder | O(1) extra |

---

## Performance Results

| Input Size | Target (pass) | Target (good) | Target (excellent) | Achieved (avg, 20 runs) |
|------------|--------------|---------------|-------------------|----------------|
| 100 numbers | < 2000 | < 1500 | < 700 | ~666 |
| 500 numbers | < 12000 | < 8000 | < 5500 | ~7061 |

---

## Resources

### Documentation & References


### AI Usage

---

## Contributors

| Login | Contributions |
|-------|--------------|
| bramos | Stack operations, parsing, simple/medium algorithms, Makefile |
| <PARTNER_LOGIN> | Complex algorithms (turk + radix), adaptive strategy, checker bonus, testing |
