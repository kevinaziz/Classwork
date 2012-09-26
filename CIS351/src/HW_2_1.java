import java.util.Scanner;
public class HW_2_1 {
	public static Scanner scan = new Scanner(System.in);
	public static void main(String args[]){
	
		// Samples for Segment 126
		System.out.println("\n\nSegment 126:");
		System.out.println("Ratio for inputs 80, 55: "+segment126(80,55));
		System.out.println("Ratio for inputs 30, 55: "+segment126(30,55));
		System.out.println("Ratio for inputs 55.5, 55: "+segment126(55.5,55));
		System.out.println("Ratio for inputs 40.2, 52.1: "+segment126(40.2,52.1));
		
		// Samples for Segment 401 (True: male, False: female)
		System.out.println("\n\nSegment 401:");
		segment401(61,1.72, true);
		segment401(67,1.72, true);
		segment401(69,1.72, true);
		segment401(68,1.72, false);
		segment401(66,1.72, false);
		
		// Samples for Segment 436  (Returning -1 means invalid input)
		segment436();
		// Samples for Segment 459  (Returning -1 means invalid input)
		System.out.println("\n\nSegment 459: ");
		
		
		// Samples for Segment 469
		System.out.println("\n\nSegment 469: ");
		System.out.println("Input: 2000, 2");
		segment469(2000,2);
		System.out.println("Input: 1900, 2");
		segment469(1900,2);
		System.out.println("Input: 1992, 2");
		segment469(1992,2);
		System.out.println("Input: 1993, 3");
		segment469(1993,3);
		System.out.println("Input: 2012, 9");
		segment469(2012,9);
		System.out.println("Input: 2099, 7");
		segment469(2012,9);
		System.out.println("Input: 2013, 2");
		segment469(2013,2);
	}
	
	//Segment 126 - Find the ratio of energies of a car moving at two specified velocities
	public static double segment126(double v1,double v2){
			return square(v1)/square(v2);
		}
	
	public static double square(double n){
		return n*n;
	}
	
	public static void segment401(double weight, double height, boolean gender){ 
		//Gender Codes: I used a boolean for gender -- True is Male, False is female
		System.out.println("\nInput: segment401("+weight+","+height+","+gender+");\nOutput:"); 
		
		double ideal;//, diff;
		int diff;
		
		if(gender){
			ideal = 56.2 + 55.5*(height-1.524);
		}
		else {
			ideal = 53.1 +53.5*(height-1.524);	
		}
		
		diff = (int)(weight-ideal);
		if(diff==0) System.out.println("\tThis person is the correct weight");
		else if(diff>0){
			if(diff==1)System.out.println("\tThis person is 1 kilogram overweight");
			else System.out.println("\tThis person is "+diff+" kilograms overweight");
		}
		else{
			if(diff==-1)System.out.println("\tThis person is 1 kilogram underweight");
			else System.out.println("\tThis person is "+(0-diff)+" kilograms underweight");
		
		}
		
	}
	
	public static void segment436(){
		int n=-1;
		while(n<0){
			System.out.print("Compute n! (iterative). Enter n:");
			n = scan.nextInt();
			if (n<0) System.out.println("Input can't be negative");
		}

		int factorial = 1;
		//Iterate with a for loop
		for(int i=n; i>1; i--){
			factorial *= i;
		}
		System.out.println("\n n! is "+factorial);
		
	}

	public static void segment459(){

		int n=-1;
		while(n<0){
			System.out.print("Compute n! (recursive). Enter n:");
			n = scan.nextInt();
			if (n<0) System.out.println("Input can't be negative");
		}
		System.out.println(recursiveFactorial(n));
	}
	public static int recursiveFactorial(int n){
		if (n==1 || n==0)	return 1;
		return n*recursiveFactorial(n-1);
	}
	
	public static void segment469(){

		int n=-1, y=-1;
		while(n<0 && y<0){
			System.out.print("How many days in the month?\nMonth: ");
			n = scan.nextInt();
			if (n<0 || n>12) { 
				System.out.println("Invalid Month");
				break;
			}
			System.out.println("Year: ");
			y = scan.nextInt();
			if(y<0){
				System.out.println("Invalid Year");
				break;
			}
			
		}
		int month = n;
		int year = y;
		int days;
		switch(month){
			case 1: 
				days = 31;
				break;
			case 2: 
				if(year%400==0) days = 29;
				else if(year%100==0) days = 28;
				else if(year%4==0) days = 29;
				else days = 28;
				break;
			case 3: 
				days = 31; 
				break;
			case 4: 
				days = 30; 
				break;
			case 5: 
				days = 31; 
				break;
			case 6: 
				days = 30; 
				break;
			case 7: days = 31; 
			break;
			case 8: 
				days = 31; 
				break;
			case 9: 
				days = 30; 
				break;
			case 10: 
				days = 31; 
				break;
			case 11: 
				days = 30; 
				break;
			case 12: 
				days = 31;
				break;
			default: System.out.println("Invalid month"); return;
		}
		System.out.println("That month has "+days+" days.");
	}
}
