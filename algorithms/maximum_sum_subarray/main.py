def maxSubArray(self, nums):
    maxsum = -(10**4) -1
    tempsum = 0
    for n in nums:
        tempsum += n
            if tempsum > maxsum:
                maxsum = tempsum
            if tempsum < 0:
                tempsum = 0
                
        return maxsum
