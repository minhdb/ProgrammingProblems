class Solution:
    def hammingDistance(self, x: int, y: int) -> int:
        """Note that x, y are unsigned."""

        if x > y:
            larger = x
            smaller = y
        else:
            larger = y
            smaller = x

        hdist = 0
        while larger > 0:
            if larger & 1 != smaller & 1:
                hdist += 1
            larger = larger >> 1
            smaller = smaller >> 1

        return hdist
