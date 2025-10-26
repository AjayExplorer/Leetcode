/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number}
 */
var searchInsert = function(nums, target) {
    let len = nums.length;
    
    for (let i = 0; i < len; i++) {
        if (nums[i] === target) {
            return i;  
        } else if (nums[i] > target) {
            return i;  
        }
    }

    return len; 
};
