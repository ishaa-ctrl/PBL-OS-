# Test Cases: Interactive Deadlock Simulation System

## Test 1: Banker's Algorithm - Safe State

**Input:**
- Number of processes: 5
- Number of resource types: 3
- Available vector: `3 3 2`

### Allocation Matrix

```text
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
```

### Maximum Matrix

```text
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
```

### Expected Results

- Banker's Algorithm reports a SAFE state.
- A safe sequence is found: `P1 → P3 → P4 → P0 → P2`.
- The Need Matrix is calculated correctly.

**Actual Result:** SAFE state and safe sequence displayed in the GUI.

---

## Test 2: Banker's Algorithm - Unsafe State

**Input:**
- Number of processes: 5
- Number of resource types: 3
- Available vector: `0 0 0`

Use the same Allocation and Maximum matrices as Test 1.

### Expected Results

- Banker's Algorithm reports an UNSAFE state.
- No safe sequence is found.

**Actual Result:** Record the result shown by the GUI.

---

## Test 3: Deadlock Detection

**Input:**
- Use the resource allocation data entered into the simulation.

### Expected Results

- The detection algorithm checks the current resource allocation.
- If no deadlock exists, the GUI reports that no deadlocked processes were found.
- If a deadlock exists, the GUI identifies the affected processes.

**Actual Result:** The GUI displayed the deadlock detection result.

---

## Test 4: Resource Request

**Input:**
- Select the Request 1 Unit button.
- Request one unit of resource R0 for process P0.

### Expected Results

- The request is granted only if resources are available and the resulting state is safe.
- Otherwise, the request is rejected.
- The system state is updated if the request is granted.

**Actual Result:** The GUI displayed the resource request result.

---

## Test 5: Deadlock Recovery

**Input:**
- Click the Recover P0 button.

### Expected Results

- The recovery operation attempts to recover process P0.
- Allocated resources are released according to the recovery implementation.
- The system status is updated.
- Deadlock detection can be run again to check the resulting state.

**Actual Result:** The recovery result and updated matrices were displayed in the GUI. Recovery behavior should be verified against the final implementation.

---

## Test 6: Resource Allocation Graph

**Input:**
- Click the Show RAG button.

### Expected Results

- The graph displays the processes and resources.
- Allocation and request relationships are represented by arrows.

**Actual Result:** The Resource Allocation Graph was displayed.

---

## Test 7: Resource Utilization

**Input:**
- Click the Resource Utilization button.

### Expected Results

- Resource utilization is calculated from the allocated and total resource units.
- The GUI displays the utilization percentage for each resource type.

Formula:

`Utilization = (Allocated Units / Total Units) × 100`

**Actual Result:** Resource utilization percentages were displayed in the GUI.

---

## Test 8: System Status

**Input:**
- Click the System Status button.

### Expected Results

- The GUI displays the current Available vector.
- Allocation, Maximum, and Need matrices are displayed.
- The output reflects the current system state.

**Actual Result:** The system status and matrices were displayed.

---

## Test Summary

| Test | Feature | Expected Outcome |
|---|---|---|
| 1 | Safe State | SAFE result and safe sequence |
| 2 | Unsafe State | UNSAFE result |
| 3 | Deadlock Detection | Detection result displayed |
| 4 | Resource Request | Request granted or rejected |
| 5 | Deadlock Recovery | Recovery result and updated state |
| 6 | Resource Allocation Graph | Graph displayed |
| 7 | Resource Utilization | Utilization percentages displayed |
| 8 | System Status | Current matrices and available resources displayed |
