//Matthew O'Rourke Bourke

import java.util.Scanner;
import java.lang.Math;
public class ProjectMOB
{
	public static void additionMethod()
	{
		Scanner scan = new Scanner (System.in);
		
		int arrVector1[] = new int[2];
		int arrVector2[] = new int[2];
		int addition[] = new int[2];
		
		System.out.println("Please enter x value for vector 1");
		arrVector1[0] = scan.nextInt();
		
		System.out.println("Please enter y value for vector 1");
		arrVector1[1] = scan.nextInt();
		
		System.out.println("Please enter x value for vector 2");
		arrVector2[0] = scan.nextInt();
		
		System.out.println("Please enter y value for vector 2");
		arrVector2[1] = scan.nextInt();
		
		//1. Vector addition
		for(int i = 0; i < arrVector1.length; i++)
		{
			addition[i] = arrVector1[i] + arrVector2[i];
		}
		
		System.out.println("Addition = " + addition[0] + "i,"  + addition[1] + "j");
	}
	
	public static void multiplicationMethod()
	{
		Scanner scan = new Scanner (System.in);
		
		int arrMultiplication[] = new int[2];
		int multiplication;
		int arrVector3[] = new int[2];
		int arrVector4[] = new int[2];
		
		System.out.println("Please enter x value for vector 1");
		arrVector3[0] = scan.nextInt();
		
		System.out.println("Please enter y value for vector 1");
		arrVector3[1] = scan.nextInt();
		
		//2. Vector multiplication
		System.out.println("Please enter number you want to multiply vector 1 by");
		multiplication = scan.nextInt();
		
		for(int i = 0; i < arrVector3.length; i++)
		{
			arrMultiplication[i] = multiplication * arrVector3[i];
		}
		
		System.out.println("Multiplication = " + arrMultiplication[0] + "i," + arrMultiplication[1] + "j");
	}
	
	public static void dotProduct()
	{
		Scanner scan = new Scanner (System.in);
		
		int arrVector1[] = new int[2];
		int arrVector2[] = new int[2];
		int i;
		int j;
		int dotProduct;
		
		System.out.println("Please enter x value for vector 1");
		arrVector1[0] = scan.nextInt();
		
		System.out.println("Please enter y value for vector 1");
		arrVector1[1] = scan.nextInt();
		
		System.out.println("Please enter x value for vector 2");
		arrVector2[0] = scan.nextInt();
		
		System.out.println("Please enter y value for vector 2");
		arrVector2[1] = scan.nextInt();
		
		i = arrVector1[0] * arrVector2[0];
		j = arrVector1[1] * arrVector2[1];
		
		dotProduct = i + j;
		
		System.out.println("Dot product = " + dotProduct);
	}
	
	public static void magnitudeMethod()
	{
		Scanner scan = new Scanner (System.in);
		
		int arrVector1[] = new int[2];
		int squared;
		double squareRoot;
		
		System.out.println("Please enter x value for vector 1");
		arrVector1[0] = scan.nextInt();
		
		System.out.println("Please enter y value for vector 1");
		arrVector1[1] = scan.nextInt();
		
		//magnitude calculations
		squared = arrVector1[0] * arrVector1[0] + arrVector1[1] * arrVector1[1];
		
		squareRoot = Math.sqrt(squared);
		
		System.out.println("Magnitude = " + squareRoot);
	}
	
	public static void angle()
	{
		Scanner scan = new Scanner (System.in);
		
		double arrVector1[] = new double[2];
		double arrVector2[] = new double[2];
		double squared;
		double squareRoot;
		double squareRoot1;
		double i;
		double j;
		double dotProduct;
		
		System.out.println("Please enter x value for vector 1");
		arrVector1[0] = scan.nextDouble();
		
		System.out.println("Please enter y value for vector 1");
		arrVector1[1] = scan.nextDouble();
		
		System.out.println("Please enter x value for vector 2");
		arrVector2[0] = scan.nextDouble();
		
		System.out.println("Please enter y value for vector 2");
		arrVector2[1] = scan.nextDouble();
		
		//magnitude calculations
		squared = arrVector1[0] * arrVector1[0] + arrVector1[1] * arrVector1[1];
		
		squareRoot = Math.sqrt(squared);
		
		System.out.println("Magnitude of 1st vector = " + squareRoot);
		
		squared = arrVector2[0] * arrVector2[0] + arrVector2[1] * arrVector2[1];
		
		squareRoot1 = Math.sqrt(squared);
		
		System.out.println("Magnitude of 2nd vector = " + squareRoot1);
		
		i = arrVector1[0] * arrVector2[0];
		j = arrVector1[1] * arrVector2[1];
		
		dotProduct = i + j;
		
		System.out.println("Dot product = " + dotProduct);
		
		//angle calculations
		double magnitudeMul = squareRoot * squareRoot1;
		
		double T = Math.acos(dotProduct / magnitudeMul) * (180/Math.PI);
		
		System.out.println("Angle between 2 vectors: " + T);
	}
	
	public static void conjugate()
	{
		Scanner scan = new Scanner (System.in);
		
		int arrComplex[] = new int[2];
		
		System.out.println("Please enter x value for real number");
		arrComplex[0] = scan.nextInt();
		
		System.out.println("Please enter y value for imaginary number");
		arrComplex[1] = scan.nextInt();
		
		if(arrComplex[1] < 0)
		{
		arrComplex[1] = arrComplex[1] * -1;
		}
		
		else if(arrComplex[1] > 0)
		{
		arrComplex[1] = arrComplex[1] * -1;
		}
		
		System.out.println("Conjugate = " + arrComplex[0] + ", " + arrComplex[1] + "i");
	}
	
	public static void reciprocal()
	{
		Scanner scan = new Scanner(System.in);

		double arrComplex[] = new double[2];
		double calcReal;
		double calcImaginary;

		System.out.println("Please enter x value for real number");
		arrComplex[0] = scan.nextInt();

		System.out.println("Please enter y value for imaginary number");
		arrComplex[1] = scan.nextInt();

		//reciprocal calculations
		double calc = arrComplex[0] * arrComplex[0] + arrComplex[1] * arrComplex[1];
		
		calcReal = arrComplex[0] / calc;
		calcImaginary = -arrComplex[1] / calc;

		System.out.println("Reciprocal = " + calcReal + ", " + calcImaginary + "i");
	}
	
	public static void complexMul()
	{
		Scanner scan = new Scanner(System.in);

		double arrComplex[] = new double[2];
		double arrComplex2[] = new double[2];
		double realMul;
		double imagMul;

		System.out.println("Please enter x value for real number");
		arrComplex[0] = scan.nextInt();

		System.out.println("Please enter y value for imaginary number");
		arrComplex[1] = scan.nextInt();
		
		System.out.println("Please enter x value for real number 2");
		arrComplex2[0] = scan.nextInt();

		System.out.println("Please enter y value for imaginary number 2");
		arrComplex2[1] = scan.nextInt();
		
		//multiplication calculations
		realMul = arrComplex[0] * arrComplex2[0] - arrComplex[1] * arrComplex2[1];
		imagMul = arrComplex[0] * arrComplex2[1] + arrComplex[1] * arrComplex2[0];
		
		System.out.println("Multiplication of complex nums = " + realMul + ", " + imagMul + "i");
	}
	
	public static void main(String[]args)
	{
		Scanner scan = new Scanner (System.in);
		
		//variables
		int input = 0;
		int arrQuadrant1[] = new int[2];
		int arrQuadrant2[] = new int[2];
		
		while(input != 9)
		{
			System.out.println("*****************MENU*******************");
			System.out.println("1. Vector addition");
			System.out.println("2. Vector Multiplication");
			System.out.println("3. Dot Product");
			System.out.println("4. Magnitude");
			System.out.println("5. Angle between 2 vectors");
			System.out.println("6. Conjugate of a complex number");
			System.out.println("7. Reciprocal of a complex number");
			System.out.println("8. Multiply 2 complex numbers");
			System.out.println("9. Exit");
			System.out.println("****************************************");
			input = scan.nextInt();
			
			switch(input)
			{
				case 1: additionMethod();
				break;
				case 2: multiplicationMethod();
				break;
				case 3: dotProduct();
				break;
				case 4: magnitudeMethod();
				break;
				case 5: angle();
				break;
				case 6: conjugate();
				break;
				case 7: reciprocal();
				break;
				case 8: complexMul();
				break;
				case 9: System.out.println("Exitting");
				break;
				default: System.out.println("Invalid choice");
			}
		}
	}
}