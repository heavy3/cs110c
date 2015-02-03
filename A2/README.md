A2
==

This assignment further implements a partially implemented linked list.

list.hpp Specification

Spec: List<T> is an array based generic list.
    Insertion: Increases List<T> by CHUNK_SIZE in capacity if needed.
    Remove: Decreases List<T> by CHUNK_SIZE in capacity if needed.

class List<T>
    - CHUNK_SIZE: const int
    - list: List<T>
    - data: array of T
    - numItems: int
    - maxItems: int

    + List()
    + insert(pos: int, value: T): bool
    + remove(pos: int): bool
    + setEntry(pos: int, value: T): bool
    + getEntry(pos: int): T
    + clear(): void

