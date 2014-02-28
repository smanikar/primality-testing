/* Contains class for Miller Rabin Implementation*/
/***************************************************************************
 * Team 
 **************
 * Arijit Banerjee
 * Suchit Maindola
 * Srikanth Manikarnike
 *
 **************/

import java.math.BigInteger;

public class MillerRabin
{
    /* a's to check with for deterministic answer*/
    
    private int[] a1 = {2,3}; 
    private int[] a2 = {31,73}; 
    private int[] a3 = {2,7,61}; 
    private int[] a4 = {2,3,5,7,11}; 
    private int[] a5 = {2,3,5,7,11,13}; 
    private int[] a6 = {2,3,5,7,11,13,17}; 

    /* main pass */
    private  boolean testMillerRabin(BigInteger a,BigInteger num) 
    {
        BigInteger decrementedNum = num.subtract(BigInteger.ONE);
        BigInteger dnum = decrementedNum;
        
        
        int lsbit = dnum.getLowestSetBit();
        dnum = dnum.shiftRight(lsbit);
        int lim = lsbit -1;
        int i = 0;

        BigInteger modPowOfA = a.modPow(dnum, num);
        if (modPowOfA.equals(BigInteger.ONE)) 
        {
            return true;
        }
        
        while( i < lim)
        {
            if (modPowOfA.equals(decrementedNum)) 
            {
                return true;
            }
            modPowOfA = modPowOfA.multiply(modPowOfA).mod(num);
            i++;
        }
        if (modPowOfA.equals(decrementedNum))
        {
            return true;
        }
        return false;
    }


    public boolean millerRabin(BigInteger num,int whichCase) 
    {
        BigInteger a;
        switch(whichCase)
        {
            case 1:
                for(int i=0;i<a1.length;i++)
                {
                    a =  new BigInteger(Integer.toString(a1[i]));
                    if (!testMillerRabin(a, num)) 
                    {
                        return false;
                    }
                }
                break;

            case 2:
                for(int i=0;i<a2.length;i++)
                {
                    a =  new BigInteger(Integer.toString(a2[i]));
                    if (!testMillerRabin(a, num)) 
                    {
                        return false;
                    }
                }
                break;
            case 3:
                for(int i=0;i<a3.length;i++)
                {
                    a =  new BigInteger(Integer.toString(a3[i]));
                    if (!testMillerRabin(a, num)) 
                    {
                        return false;
                    }
                }
                break;
            case 4:
                for(int i=0;i<a4.length;i++)
                {
                    a =  new BigInteger(Integer.toString(a4[i]));
                    if (!testMillerRabin(a, num)) 
                    {
                        return false;
                    }
                }
                break;
            case 5:
                for(int i=0;i<a5.length;i++)
                {
                    a =  new BigInteger(Integer.toString(a5[i]));
                    if (!testMillerRabin(a, num)) 
                    {
                        return false;
                    }
                }
                break;
            case 6:
                for(int i=0;i<a6.length;i++)
                {
                    a =  new BigInteger(Integer.toString(a6[i]));
                    if (!testMillerRabin(a, num)) 
                    {
                        return false;
                    }
                }
                break;
            default:
                break;

        }
        return true;
    }

}

