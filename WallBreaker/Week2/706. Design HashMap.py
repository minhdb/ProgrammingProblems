class MyHashMap:

    def __init__(self):
        """Initialize your data structure here.

        Naive approach: Have the index as key and a list as values.
        put() - O(n) time - O(n) space
        get() - O(1) time
        remove() - O(1) time
        Issue: Wasted memory if we have n elements and remove all of them.
        This can be improved by reducing the size of the list.
        """
        self.values = [None]


    def put(self, key: int, value: int) -> None:
        """value will always be non-negative.

        O(n) worst time complexity due to copying.
        """
        if key >= len(self.values):
            self.values.extend([None] * (key - len(self.values) + 1))
        self.values[key] = value


    def get(self, key: int) -> int:
        """Returns the value to which the specified key is mapped, or -1 if
        this map contains no mapping for the key

        O(1) time complexity
        """
        if key < len(self.values) and self.values[key] != None:
            return self.values[key]
        else:
            return -1

    def remove(self, key: int) -> None:
        """Removes the mapping of the specified value key if this map contains
        a mapping for the key

        O(1) time complexity
        """
        if key < len(self.values):
            if self.values[key] != None:
                self.values[key] = None


# Your MyHashMap object will be instantiated and called as such:
# obj = MyHashMap()
# obj.put(key,value)
# param_2 = obj.get(key)
# obj.remove(key)
