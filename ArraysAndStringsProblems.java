import java.util.HashSet;
import java.util.Arrays;

public class ArraysAndStringsProblems {
	
	public static void main(String[] args) {

		// 1.1
		// implement an algorithm to determine if a string has all unique characters. What if you cannot use additional data structures?

		System.out.println("1.1:");

		String input1 = "";
		String input2 = "abc";
		String input3 = "abca";

		System.out.println("'' is " + areCharsUniqueWithDataStructs(input1));
		System.out.println("'abc' is " + areCharsUniqueWithDataStructs(input2));
		System.out.println("'abca' is " + areCharsUniqueWithDataStructs(input3));

		System.out.println("'' is " + areCharsUniqueWithoutDataStructs(input1));
		System.out.println("'abc' is " + areCharsUniqueWithoutDataStructs(input2));
		System.out.println("'abca' is " + areCharsUniqueWithoutDataStructs(input3));

		System.out.println("\n");

		// 1.2
		// Write code to reverse a C-Style String (C-String means that “abcd” is represented as five characters, including the null character )

		System.out.println("1.2");

		char[] cStyleString1 = {'A','B','C'};
		char[] cStyleString2 = {};
		char[] cStyleString3 = {'B','C','A','D','E','H'};

		System.out.println("'ABC' becomes " + reverseCStyleStringNoNull(cStyleString1));
		System.out.println("'' becomes " + reverseCStyleStringNoNull(cStyleString2));
		System.out.println("'BCADEH' becomes " + reverseCStyleStringNoNull(cStyleString3));

		Character[] cStyleStringNull1 = {'A','B','C',null};
		Character[] cStyleStringNull2 = {null};
		Character[] cStyleStringNull3 = {'B','C','A','D','E','H',null};

		System.out.println("'ABC' becomes " + reverseCStyleStringWithNull(cStyleStringNull1));
		System.out.println("'' becomes " + reverseCStyleStringWithNull(cStyleStringNull2));
		System.out.println("'BCADEH' becomes " + reverseCStyleStringWithNull(cStyleStringNull3));

		System.out.println("\n");

		// 1.3
		// Design an algorithm and write code to remove the duplicate characters in a string without using any additional buffer 
		//		NOTE: One or two additional variables are fine - An extra copy of the array is not
		// FOLLOW UP
		// 		Write the test cases for this method

		System.out.println("1.3");

		String dup1 = "tessssst";
		String dup2 = "aabbccdd";
		String dup3 = "";
		String dup4 = "abcbcaddffffghaabbcj";

		System.out.println("'tessssst' becomes " + removeDuplicateChars(dup1));
		System.out.println("'aabbccdd' becomes " + removeDuplicateChars(dup2));
		System.out.println("'' becomes " + removeDuplicateChars(dup3));
		System.out.println("'abcbcaddffffghaabbcj' becomes " + removeDuplicateChars(dup4));

		System.out.println("\n");

		// 1.4
		// Write a method to decide if two strings are anagrams or not

		System.out.println("1.4");

		String ana1 = "abcba";
		String ana2 = "ab";
		String ana3 = "";
		String ana4 = "abba";
		String ana5 = "asdfdsasdfdsa";
		String ana6 = "asdffdsaasdf";

		System.out.println("'abcba' is " + checkAnagram(ana1));
		System.out.println("'ab' is " + checkAnagram(ana2));
		System.out.println("'' is " + checkAnagram(ana3));
		System.out.println("'abba' is " + checkAnagram(ana4));
		System.out.println("'asdfdsasdfdsa' is " + checkAnagram(ana5));
		System.out.println("'asdffdsaasdf' is " + checkAnagram(ana6));

		System.out.println("\n");

		// 1.5
		// Write a method to replace all spaces in a string with ‘%20’

		System.out.println("1.5");

		String replace1 = "This is a string";
		String replace2 = "";

		System.out.println("'This is a string' replaced with " + replaceSpaces(replace1));
		System.out.println("'' replaced with " + replaceSpaces(replace2));

		System.out.println("\n");

		// 1.6
		// Given an image represented by an NxN matrix, where each pixel in the image is 4 bytes, 
		// write a method to rotate the image by 90 degrees Can you do this in place?

		System.out.println("1.6");

		int[][] matrixImage1 = new int[][] { { 1,2,3,4 },
											 { 1,2,3,4 },
											 { 1,2,3,4 },
											 { 1,2,3,4 } };

		int[][] resultingMatrixImage1 = rotateArrayNinetyDegrees(matrixImage1);
		System.out.println("Original Matrix:");
		prettyPrintMatrix(matrixImage1);
		System.out.println("\nRotated Matrix:");
		prettyPrintMatrix(resultingMatrixImage1);

		System.out.println("\n");

		// 1.7
		// Write an algorithm such that if an element in an MxN matrix is 0, its entire row and column is set to 0

		System.out.println("1.7");

		int[][] matrixZeros1 = new int[][] { { 1,0,3,4 },
											 { 1,2,0,4 },
											 { 1,2,3,4 },
											 { 1,2,3,4 } };

		int[][] resultingMatrixZeros1 = setRowAndColumnToZero(matrixZeros1);
		System.out.println("Original Matrix 1:");
		prettyPrintMatrix(matrixZeros1);
		System.out.println("\nZero Replaced Matrix 1:");
		prettyPrintMatrix(resultingMatrixZeros1);

		System.out.println("");

		int[][] matrixZeros2 = new int[][] { { 1,0,3,4 },
											 { 1,2,3,4 },
											 { 1,2,3,0 } };
		int[][] resultingMatrixZeros2 = setRowAndColumnToZero(matrixZeros2);
		System.out.println("Original Matrix 2:");
		prettyPrintMatrix(matrixZeros2);
		System.out.println("\nZero Replaced Matrix 2:");
		prettyPrintMatrix(resultingMatrixZeros2);

		System.out.println("\n");

		// 1.8
		// Assume you have a method isSubstring which checks if one word is a substring of another 
		// Given two strings, s1 and s2, write code to check if s2 is a rotation of s1 using only one call 
		// to isSubstring (i e , “waterbottle” is a rotation of “erbottlewat”)

		String rotationString1 = "waterbottle";
		String rotationString2 = "erbottlewat";

		System.out.println("Input: 'waterbottle' and 'erbottlewat'");
		System.out.println("Output: " + isRotation(rotationString1, rotationString2));

		String rotationString3 = "waterbottless";
		String rotationString4 = "erbottlewatss";

		System.out.println("Input: 'waterbottless' and 'erbottlewatss'");
		System.out.println("Output: " + isRotation(rotationString3, rotationString4));


	}

	// ------------------------ 1.1 ------------------------ //

	public static boolean areCharsUniqueWithDataStructs(String input) {

		HashSet<Character> chars = new HashSet<Character>();

		for (int i = 0; i < input.length(); i++) {
			if (!(chars.add(input.charAt(i)))) {
				return false;
			}
		}
		return true;
	}

	public static boolean areCharsUniqueWithoutDataStructs(String input) {

		for (int i = 0; i < input.length(); i++) {
			for (int s = 0; s < input.length(); s++) {
				if (s != i && input.charAt(i) == input.charAt(s)) {
					return false;
				}
			}
		}
		return true;
	}

	// ------------------------ 1.2 ------------------------ //

	public static String reverseCStyleStringNoNull(char[] input) {

		char[] result = new char[input.length];
		for (int i = input.length-1; i > -1; i--) {
			result[input.length - 1 - i] = input[i];
		}
		String resultString = new String(result);
		return resultString;
	}

	public static String reverseCStyleStringWithNull(Character[] input) {
		
		char[] result = new char[input.length-1];
		int i = 0;
		while (input[i] != null) {
			result[input.length - 2 - i] = input[i].charValue();
			i++;
		}
		String resultString = new String(result);
		return resultString;
	}

	// ------------------------ 1.3 ------------------------ //
	// Note that this returns the LAST char found - eg 'abcda' will return 'bcda'
	public static String removeDuplicateChars(String input) {
		
		String result = "";
		for (int i = 0; i < input.length(); i++) {
			int count = 1;
			//System.out.println(result.length());
			char ch = input.charAt(i);
			for (int s = i+1; s < input.length(); s++) {
				//System.out.println(result.charAt(j));
				//System.out.println(input.charAt(s));
				if (ch == input.charAt(s)) {
					count++;
				}
			}		
			if (count == 1) {
				result += input.charAt(i);
			}
		}
		return result;
	}

	// ------------------------ 1.4 ------------------------ //
	public static boolean checkAnagram(String input) {

		for (int i = 0, s = input.length()-1; i != s && s > i; i++, s--) {
			if (input.charAt(i) != input.charAt(s)) {
				return false;
			}
		}
		return true;
	}

	// ------------------------ 1.5 ------------------------ //	
	public static String replaceSpaces(String input) {

		return input.replace(" ", "%20");
	}

	// ------------------------ 1.6 ------------------------ //	
	public static int[][] rotateArrayNinetyDegrees(int[][] matrix) {

		int[][] newMatrix = copy_matrix(matrix);
		for (int i = 0; i < newMatrix.length/2; i++) {
			int first = i;
			int last = newMatrix.length - 1 - i;
			for (int s = first; s < last; s++) {
				int offset = s - first;
				int top = newMatrix[first][s];
				newMatrix[first][s] = newMatrix[last-offset][first];
				newMatrix[last-offset][first] = newMatrix[last][last-offset];
				newMatrix[last][last - offset] = newMatrix[s][last];
				newMatrix[s][last] = top;
			}
		}
		return newMatrix;
	}

	public static int[][] copy_matrix(int[][] input) {

	    int[][] target = new int[input.length][];
	    for (int i=0; i <input.length; i++) {
	        target[i] = Arrays.copyOf(input[i], input[i].length);
	    }
	    return target;
	}

	public static void prettyPrintMatrix(int[][] matrix) {

		for (int i = 0; i < matrix.length; i++) {
			for (int s = 0; s < matrix[i].length; s++) {
				System.out.printf("%d",matrix[i][s]);
				//System.out.println(matrix[i][s]);
			}
			System.out.println("");
		}
	}

	// ------------------------ 1.7 ------------------------ //	
	// Note that this solution is not optimal - a better way to do it would be to
	// use make two passes over the matrix - but in the first pass the only thing you
	// need to do is keep track of which rows have a 0 and which columns have a 0. Then
	// in the second pass you can just set those rows and columns to 0.

	public static int[][] setRowAndColumnToZero(int[][] matrix) {

		int[][] newMatrix = copy_matrix(matrix);
		for (int i = 0; i < matrix.length; i++) {
			for (int s = 0; s < matrix[i].length; s++) {
				if (matrix[i][s] == 0) {
					int row = i;
					int col = s;
					newMatrix = replaceWithZeros(newMatrix, i, s);
				}
			}
		}
		return newMatrix;
	}

	public static int[][] replaceWithZeros(int[][] matrix, int row, int col) {
		
		// first do the row
		for (int i = 0; i < matrix[row].length; i++) {
			matrix[row][i] = 0;
		}
		// now the column
		for (int i = 0; i < matrix.length; i++) {
			for (int s = 0; s < matrix[i].length; s++) {
				if (s == col) {
					matrix[i][s] = 0;
				}
			}
		}
		return matrix;
	}

	// ------------------------ 1.8 ------------------------ //	
	public static boolean isRotation(String input1, String input2) {

		if (input1.length() != input2.length()) {
			return false;
		}
		else {
			String checker = input2 + input2;
			if (checker.indexOf(input1) != -1) {
				return true;
			}
			else {
				return false;
			}
		}
	}

}