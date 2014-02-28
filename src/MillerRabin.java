/* Copyright (c) 2011 the authors listed at the following URL, and/or
   the authors of referenced articles or incorporated external code:
http://en.literateprograms.org/Miller-Rabin_primality_test_(Java)?action=history&offset=20080201093914

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Miller-Rabin_primality_test_(Java)?oldid=12469
 */

import java.math.BigInteger;
import java.util.Random;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;



public class MillerRabin
{
    private static final Random rnd = new Random();

    private static boolean miller_rabin_pass(BigInteger a, BigInteger n) {
        BigInteger n_minus_one = n.subtract(BigInteger.ONE);
        BigInteger d = n_minus_one;
        int s = d.getLowestSetBit();
        d = d.shiftRight(s);

        BigInteger a_to_power = a.modPow(d, n);
        if (a_to_power.equals(BigInteger.ONE)) return true;
        for (int i = 0; i < s-1; i++) {
            if (a_to_power.equals(n_minus_one)) return true;
            a_to_power = a_to_power.multiply(a_to_power).mod(n);
        }
        if (a_to_power.equals(n_minus_one)) return true;
        return false;
    }


    public static boolean miller_rabin(BigInteger n) {
        for (int repeat = 0; repeat < 20; repeat++) {
            BigInteger a;
            do {
                a = new BigInteger(n.bitLength(), rnd);
            } while (a.equals(BigInteger.ZERO));
            if (!miller_rabin_pass(a, n)) {
                return false;
            }
        }
        return true;
    }

/*
     * Reads data from a given file
     */
    public static String readFromFile(String fileName) 
    {
        String DataLine = "";
        try {
            File inFile = new File(fileName);
            BufferedReader br = new BufferedReader(new InputStreamReader(
                        new FileInputStream(inFile)));

            while((DataLine = br.readLine())!=null)
            {
                BigInteger n = new BigInteger(DataLine);
                final long startTime = System.currentTimeMillis();
                boolean ans = miller_rabin(n);
                //final long endTime = System.nanoTime();
                final long endTime = System.currentTimeMillis();
                final long duration = endTime - startTime;
                System.out.println("Number: " + DataLine);
                System.out.println(ans ? "PRIME" : "COMPOSITE");
                System.out.println("Time taken: " + duration + "ms");
            }
            br.close();
        } catch (FileNotFoundException ex) {
            return (null);
        } catch (IOException ex) {
            return (null);
        }
        return (DataLine);

    }

    public static void main(String[] args) 
    {
        String input = readFromFile(args[0]);
    }
}

