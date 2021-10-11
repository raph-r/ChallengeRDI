using System;
using System.Collections.Generic;

namespace Problem_003
{
    class Program
    {
        // Sum of the remainders by the module of two, using n of occurencies from each letter - (key=letter | value=n of occurencies)
        static int sumRemaindersByModuleTwo(Dictionary<char, int> occurencies)
        {
            int remainder, sum = 0;
            foreach (var i in occurencies)
            {
                remainder = i.Value % 2;
                if (remainder != 0)
                {
                    sum += remainder;
                }
            }
            return sum;
        }

        static string isPalindromePermutation(string word)
        {
            // Counts the amount of occurrencies for each letter - (key=letter | value=n of occurencies)
            Dictionary<char, int> occurencies = new Dictionary<char, int>();
            foreach (char c in word)
            {
                if (!occurencies.ContainsKey(c))
                {
                    occurencies.Add(c, 0);
                }
                occurencies[c]++;
            }
            /* 
             * if word.Length is even, the sum of remainders by the module of two needs to be zero.
             * if word.Length is odd, the sum of remainders by the module of two needs to be one.
             */
            return (sumRemaindersByModuleTwo(occurencies) == word.Length % 2) ? "Yes" : "No";
        }

        static void Main(string[] args)
        {
                if (args.Length != 1)
                {
                    Console.WriteLine("Use one parameters that contains the string desired to be checked. If a sequence made of number is passed as argument, it will be also checked as a string.");
                }
                else
                {
                    Console.WriteLine(isPalindromePermutation(args[0]));
                }
        }
    }
}
