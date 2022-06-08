def longestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        largest_pal_start = 0
        dif = 1
        memo = [[0 for i in range(len(s))] for j in range(len(s))]
        
        #for lenght 1
        for i in range(len(s)):
            memo[i][i] = 1
        
        
        #for lenght 2
        for i in range(len(s)-1):
            if s[i] == s[i+1]:
                memo[i][i+1] = 1
                largest_pal_start = i
                dif = 2
                
        # for len 3+
        for differ in range(3, len(s) + 1):
            for i in range(len(s) - differ + 1):
                j = i + differ - 1
                if memo[i+1][j-1] == 1 and s[i] == s[j]:
                    memo[i][j] = 1
                    if dif < differ:
                        largest_pal_start = i
                        dif = differ

        return s[largest_pal_start:largest_pal_start + dif]
