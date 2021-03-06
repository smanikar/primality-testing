/* This is the main class which reads numbers from file and calls miller-rabin or AKS*/



import java.math.*;
import java.io.*;
import java.lang.String;

public class PrimeTest
{
    
    /* Limit check for Miller Rabin*/
    public static long v1 = 1373653L;
    public static long v2 = 9080191L;
    public static long v3 = 4759123141L;
    public static long v4 = 2152302898747L;
    public static long v5 = 3474749660383L;
    public static long v6 = 341550071728321L;
    
    
    //read from file
    public static void readFromFile() 
    {
        String DataLine = "";
        try {
            BufferedReader br = new BufferedReader(new InputStreamReader(
                        System.in));

            while((DataLine = br.readLine())!=null)
            {
                int strlen = DataLine.length();
                if(strlen == 0)
                    continue;
                if(strlen < 3)
                {
                    if (Integer.parseInt(DataLine) <= 1)
                    {
                        System.out.println("0");
                        continue;
                    }
                    if ((Integer.parseInt(DataLine) == 2) || (Integer.parseInt(DataLine) == 3)|| (Integer.parseInt(DataLine) == 5)||(Integer.parseInt(DataLine) == 7)||(Integer.parseInt(DataLine) == 11)||(Integer.parseInt(DataLine) == 13)||(Integer.parseInt(DataLine) == 17))
                    {
                        System.out.println("1");
                        continue;
                    }
                }
                
                BigInteger num = new BigInteger(DataLine);
                long val = 341550071728322L;
                if(strlen < 16) // limit for miller rabin
                {
                    val = num.longValue();
                }
                if(val < v6)
                {
                    MillerRabin mr = new MillerRabin();
                    boolean status;
                    if(val < v1)
                    {
                        status = mr.millerRabin(num,1);
                    }
                    else if(val < v2)
                    {
                        status = mr.millerRabin(num,2);
                    }
                    else if(val < v3)
                    {
                        status = mr.millerRabin(num,3);
                    }
                    else if(val < v4)
                    {
                        status = mr.millerRabin(num,4);
                    }
                    else if(val < v5)
                    {
                       status =  mr.millerRabin(num,5);
                    }
                    else 
                    {
                        status = mr.millerRabin(num,6);
                    }
                    if(status)
                        System.out.println("1");
                    else    
                        System.out.println("0");
                }
                else
                {
                    AKS bp = new AKS(num);
                }
            }
            br.close();
        } catch (FileNotFoundException ex) {
            System.out.println("\nFile not found");
        } catch (IOException ex) {
            System.out.println("\nError:IOExpection");
        }
    }

    //main
    public static void main(String[] args)
    {
        readFromFile();
    }
}
