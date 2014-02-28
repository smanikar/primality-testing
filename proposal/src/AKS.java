import java.math.*;
import java.io.*;
/***************************************************************************
 * Team 
 **************
 * Arijit Banerjee
 * Suchit Maindola
 * Srikanth Manikarnike
 *
 **************
 * This is am implementation of Agrawal–Kayal–Saxena primality test in java. 
 *
 **************
 * The algorithm is -
 * 1. l <- log n
 * 2. for i<-2 to l
 *      a. if an is a power fo l
 *              return COMPOSITE
 * 3. r <- 2
 * 4. while r < n
 *      a. if gcd( r, n) != 1
 *              return COMPSITE
 *      b. if sieve marked n as PRIME
 *              q <- largest factor (r-1)
 *              o < - r-1 / q
 *              k <- 4*sqrt(r) * l
 *              if q > k and n <= r 
 *                      return PRIME
 *      c. x = 2
 *      d. for a <- 1 to k 
 *              if (x + a) ^n !=  x^n + mod (x^r - 1, n) 
 *                      return COMPOSITE
 *      e. return PRIME
 */

public class AKS
{
    private int log;
    private boolean sieveArray[];
    private int SIEVE_ERATOS_SIZE = 100000000;

    /* aks constructor */
    public AKS(BigInteger input)
    {
        sieveEratos();

        boolean result = checkIsPrime(input);

        if( result) 
        {
            System.out.println("1");
        }
        else 
        {
            System.out.println("0");
        }
    }
    
    /* function to check if a given number is prime or not */
    public boolean checkIsPrime(BigInteger n)
    {
        BigInteger lowR, powOf, x, leftH, rightH, fm, aBigNum;
        int totR, quot, tm, aCounter, aLimit, divisor;
        log = (int) logBigNum(n);
        if( findPower(n,log) )
        {
            return false;
        }
        lowR = new BigInteger("2");
        x = lowR;
        totR = lowR.intValue();
        for( lowR = new BigInteger("2"); 
                lowR.compareTo(n) < 0; 
                lowR = lowR.add(BigInteger.ONE))
        {
            if( (lowR.gcd(n)).compareTo(BigInteger.ONE) != 0 )
            {
                return false;
            }
            totR = lowR.intValue();
            if( checkIsSievePrime(totR) )
            {
                quot = largestFactor(totR - 1);
                divisor = (int) (totR - 1) / quot;
                tm = (int) (4 * (Math.sqrt(totR)) * log);
                powOf = mPower(n, new BigInteger("" + divisor), lowR);
                if( quot >= tm && (powOf.compareTo(BigInteger.ONE)) != 0 ) 
                {
                    break;
                }
            }
        }
        fm = (mPower(x, lowR, n)).subtract(BigInteger.ONE);
        aLimit = (int) (2 * Math.sqrt(totR) * log);
        for(aCounter = 1; aCounter < aLimit; aCounter++)
        {
            aBigNum = new BigInteger("" + aCounter);
            leftH = (mPower(x.subtract(aBigNum), n, n)).mod(n);
            rightH = (mPower(x, n, n).subtract(aBigNum)).mod(n);
            if(leftH.compareTo(rightH) != 0) return false;
        }
        return true;
    }
    /* function that computes the log of a big number*/
    public double logBigNum(BigInteger bNum)
    {
        String str;
        int len;
        double num1, num2;
        str = "." + bNum.toString();
        len = str.length() - 1;
       num1 = Double.parseDouble(str);
        num2 = Math.log10(num1) + len;
        return num2;
    }
    
    /*function that computes the log of a big number input in string format*/
    public double logBigNum(String str)
    {
        String s;
        int len;
        double num1, num2;
        len = str.length();
        s = "." + str;
        num1 = Double.parseDouble(s);
        num2 = Math.log10(num1) + len;
        return num2;
    }

    /* function to compute the largest factor of a number */
    public int largestFactor(int num)
    {
        int i;
        i = num;
        if(i == 1) return i;
        while(i > 1)
        {
            while( sieveArray[i] == true )
            { 
               i--;
            }
            if(num % i == 0) 
            {
                return i;
            }
            i--;
        }
        return num;
    }


    /*function given a and b, computes if a is power of b */
    public boolean findPowerOf(BigInteger bNum, int val)
    {
        int l;
        double len;
        BigInteger low, high, mid, res;
        low = new BigInteger("10");
        high = new BigInteger("10");
        len = (bNum.toString().length()) / val;
        l = (int) Math.ceil(len);
        low = low.pow(l - 1);
        high = high.pow(l).subtract(BigInteger.ONE);
        while(low.compareTo(high) <= 0)
        {
            mid = low.add(high);
            mid = mid.divide(new BigInteger("2"));
            res = mid.pow(val);
            if(res.compareTo(bNum) < 0)
            {
                low = mid.add(BigInteger.ONE);
            }
            else if(res.compareTo(bNum) > 0)
            {
                high = mid.subtract(BigInteger.ONE);
            }
            else if(res.compareTo(bNum) == 0)
            {
                return true;
            }
        }
        return false;
    }

    /* creates a sieve array that maintains a table for COMPOSITE-ness 
     * or possibly PRIME state for all values less than SIEVE_ERATOS_SIZE
     */
    public boolean checkIsSievePrime(int val)
    {
        if(sieveArray[val] == false)
        {
           return true;
        }
        else 
        {
           return false;
        }
    }

    long mPower(long x, long y, long n)
    {
        long m, p, z;
        m = y;
        p = 1;
        z = x;
        while(m > 0)
        {
            while(m % 2 == 0)
            {
                m = (long) m / 2;
                z = (z * z) % n;
            }
            m = m - 1;
            p = (p * z) % n;
        }
        return p;
    }

    /* function, given a and b computes if a is a power of b */
    boolean findPower(BigInteger n, int l)
    {
        int i;
        for(i = 2; i < l; i++)
        {
            if(findPowerOf(n, i))
            {
                return true;
            }
        }
        return false;
    }

    BigInteger mPower(BigInteger x, BigInteger y, BigInteger n)
    {
        BigInteger m, p, z, two;
        m = y;
        p = BigInteger.ONE;
        z = x;
        two = new BigInteger("2");
        while(m.compareTo(BigInteger.ZERO) > 0)
        {
            while( ( (m.mod(two)).compareTo(BigInteger.ZERO) ) == 0)
            {
                m = m.divide(two);
                z = (z.multiply(z)).mod(n);
            }
            m = m.subtract(BigInteger.ONE);
            p = (p.multiply(z)).mod(n);
        }
        return p;
    }

    /* array to populate sieve array
     * the sieve array looks like this
     *  
     *  y index -> 0 1 2 3 4 5 6 ... n
     *  x index    1  
     *     |       2   T - T - T ...
     *     \/      3     T - - T ...
     *             4       T - - ...
     *             .         T - ...
     *             .           T ...
     *             n
     *             
     *
     *
     *
     */ 
    public void sieveEratos()
    {
        int i, j;
        sieveArray = new boolean[SIEVE_ERATOS_SIZE+1];
        sieveArray[1] = true;
        for(i = 2; i * i <= SIEVE_ERATOS_SIZE; i++)
        {
            if(sieveArray[i] != true)
            {
                for(j = i * i; j <= SIEVE_ERATOS_SIZE; j += i)
                {
                    sieveArray[j] = true;
                }
            }
        }
    }

}









