class Solution:
    def selfDividingNumbers(self, left: int, right: int) -> List[int]:
        """Brute force solution"""
        solList = []
        for i in range(left, right+1):
            if (self.isSelfDividingNumber(i)):
                solList.append(i)
        return solList
        
    def isSelfDividingNumber(self, n):
        nToString = str(n)
        for c in nToString:
            if (c == '0' or n % int(c) != 0):
                return False
        return True
        