class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        """O(n^2) time solution.

        A better solution would be sorting the string: O(nlogn).
        """
        sTable = dict()
        for c in s:
            if c not in sTable:
                sTable[c] = 1
            else:
                sTable[c] += 1

        tTable = dict()
        for c in t:
            if c not in tTable:
                tTable[c] = 1
            else:
                tTable[c] += 1

        for c in s:
            if c not in tTable:
                return False
            else:
                if sTable[c] != tTable[c]:
                    return False

        for c in t:
            if c not in sTable:
                return False
            else:
                if sTable[c] != tTable[c]:
                    return False
        return True
