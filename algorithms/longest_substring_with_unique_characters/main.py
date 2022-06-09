def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        memo = set()
        cur_len, max_len, subs, subf = 0, 0, 0, 0 
        for c in s:
            if c not in memo:
                memo.add(c)
                cur_len += 1
            else: # matched c
                j = 0
                while s[subs] != c:
                    print(s[subs])
                    memo.remove(s[subs])
                    subs += 1
                    j += 1
                memo.remove(s[subs])
                subs += 1
                j += 1
                cur_len -= j - 1
                memo.add(c)
            if  max_len < cur_len:
                max_len = cur_len
            subf += 1
        return max_len
