/**
 * CS 2110 Spring 2021 HW1
 * Part 2 - Coding with bases
 *
 * @author YOUR NAME HERE
 *
 * Global rules for this file:
 * - You may not use more than 2 conditionals per method. Conditionals are
 *   if-statements, if-else statements, or ternary expressions. The else block
 *   associated with an if-statement does not count toward this sum.
 * - You may not use more than 2 looping constructs per method. Looping
 *   constructs include for loops, while loops and do-while loops.
 * - You may not use nested loops.
 * - You may not declare any file-level variables.
 * - You may not use switch statements.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any method from this or
 *   another file to implement any method. Recursive solutions are not
 *   permitted.
 * - The only Java API methods you are allowed to invoke are:
 *     String.length()
 *     String.charAt()
 * - You may not invoke the above methods from string literals.
 *     Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 *   is a single digit.
 *
 * Method-specific rules for this file:
 * - You may not use multiplication, division or modulus in any method, EXCEPT
 *   decimalStringToInt, where multiplication is allowed
 * - You may declare exactly one String variable each in intToOctalString and
 *   and hexStringToBinaryString.
 */
public class Bases
{
    /**
     * Convert a string containing ASCII characters (in binary) to an int.
     *
     * You do not need to handle negative numbers. The Strings we will pass in
     * will be valid binary numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: binaryStringToInt("111"); // => 7
     */
    public static int binaryStringToInt(String binary)
    {
        int fin = 0;
        int count = 0;
        int length = binary.length();
        int bit = 0;

        for (int i = length - 1; i >= 0; i--) {
            bit = binary.charAt(i) - '0';
            if (bit == 1) {
                fin += 0x1 << count;
            }
            count++;
        }

        return fin;
    }

    /**
     * Convert a string containing ASCII characters (in decimal) to an int.
     *
     * You do not need to handle negative numbers. The Strings we will pass in
     * will be valid decimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: decimalStringToInt("46"); // => 46
     *
     * You may use multiplication (the * operator) in this method.
     */
    public static int decimalStringToInt(String decimal)
    {
        int fin = 0;
        int length = decimal.length();
        for (int i = 0; i < length; i++) {
            fin = fin * 10;
            fin += decimal.charAt(i) - '0';
        }
        return fin;
    }

    /**
     * Convert a string containing ASCII characters (in hex) to an int.
     *
     * You do not need to handle negative numbers. The Strings we will pass in
     * will be valid hex numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: hexStringToInt("2B"); // => 43
     */
    public static int hexStringToInt(String hex)
    {
        int fin = 0;
        int power = 0;
        for (int i = hex.length() - 1; i >= 0; i--) {
            fin += (hex.charAt(i) > '9' ? hex.charAt(i) - '0' - 7: hex.charAt(i) - '0') << power;
            power += 4;
        }
        return fin;
    }

    /**
     * Convert a int into a String containing ASCII characters (in octal).
     *
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters
     * necessary to represent the number that was passed in.
     *
     * Example: intToOctalString(166); // => "246"
     *
     * You may declare one String variable in this method.
     */
    public static String intToOctalString(int octal)
    {
        String fin = "";
        int complement = ~0x0;
        fin = ((octal & 0x7) + fin);
        octal = octal >> 3;
        while (octal != 0 && octal != complement) {
            fin = ((octal & 0x7) + fin);
            octal = octal >> 3;
        }
        return fin;
    }

    /**
     * Convert a String containing ASCII characters representing a number in
     * hex into a String containing ASCII characters that represent that same
     * value in binary.
     *
     * The output string should only contain numbers.
     * You do not need to handle negative numbers.
     * The length of all the hex strings passed in will be of size 8.
     * The binary string returned should contain 32 characters.
     *
     * Example: hexStringToBinaryString("06A1E4C0"); // => 00000110101000011110010011000000
     *
     * You may declare one String variable in this method.
     */
    public static String hexStringToBinaryString(String hex)
    {
        return "";
    }
}
