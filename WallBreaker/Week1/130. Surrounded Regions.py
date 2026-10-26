class Solution:
    def solve(self, board: List[List[str]]) -> None:
        """Do not return anything, modify board in-place instead."""
        
        rows = len(board)
        if rows == 0:
            return
        cols = len(board[0])

      
        # Run DFS on O elements that are on the border and mark
        # so that we don't remove them.
        for i in range(cols):
            if board[0][i] == "O":
                self.dfs(board, 0, i, "R")
            if board[rows-1][i] == "O":
                self.dfs(board, rows-1, i, "R")
                
        for i in range(1, rows):
            if board[i][0] == "O":
                self.dfs(board, i, 0, "R")
            if board[i][cols-1] == "O":
                self.dfs(board, i, cols-1, "R")
        
        print(board)
        # The remaining "O" that are not connected to at least one "O"
        # on the border are flipped into "X".
        for i in range(rows):
            for j in range(cols):
                if board[i][j] == "O":
                    board[i][j] = "X"
                elif board[i][j] == "R":
                    board[i][j] = "O"
        return board
        
    
    def dfs(self, board, start_x, start_y, marker):
        
        rows = len(board)
        cols = len(board[0])

        stack = [start_x * cols + start_y]
        board[start_x][start_y] = marker
        while len(stack) != 0:
            cur_coord = stack.pop()
            cur_x = cur_coord // cols;
            cur_y = cur_coord - (cols*cur_x);
            
            if cur_x-1 >= 0 and board[cur_x-1][cur_y] != marker and board[cur_x-1][cur_y] == "O":
                board[cur_x-1][cur_y] = marker
                stack.append((cur_x-1)*cols + cur_y)
            if cur_x+1 < rows and board[cur_x+1][cur_y] != marker and board[cur_x+1][cur_y] == "O":
                board[cur_x+1][cur_y] = marker
                stack.append((cur_x+1)*cols + cur_y)
            if cur_y-1 >= 0 and board[cur_x][cur_y-1] != marker and board[cur_x][cur_y-1] == "O":
                board[cur_x][cur_y-1] = marker
                stack.append(cur_x*cols + cur_y-1)
            if cur_y+1 < cols and board[cur_x][cur_y+1] != marker and board[cur_x][cur_y+1] == "O":
                board[cur_x][cur_y+1] = marker
                stack.append(cur_x*cols + cur_y+1)