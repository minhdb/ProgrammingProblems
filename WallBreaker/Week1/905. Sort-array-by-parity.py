class Solution:
    def sortArrayByParity(self, A: List[int]) -> List[int]:
        """Time: O(n)

        Space: O(n) due to having 2 lists
        """
        
        evenList = []
        oddList = []
        for el in A:
            if (el % 2 == 0):
                evenList.append(el)
            else:
                oddList.append(el)
        evenList.extend(oddList)                
        return evenList
            
        