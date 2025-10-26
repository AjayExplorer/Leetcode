/**
 * @param {number} x
 * @return {number}
 */
var reverse = function(x) {
    // Handle negative numbers by storing the sign and working with the absolute value
    const isNegative = x < 0;
    let numStr = Math.abs(x).toString();

    // Reverse the string representation
    let reversedStr = numStr.split('').reverse().join('');

    // Convert back to a number
    let result = parseInt(reversedStr, 10);

    // Apply the original sign
    if (isNegative) {
        result = -result;
    }

    // Handle 32-bit signed integer overflow
    const MAX_INT = 2147483647; // 2^31 - 1
    const MIN_INT = -2147483648; // -2^31

    if (result > MAX_INT || result < MIN_INT) {
        return 0; // Return 0 for overflow
    }

    return result;
};