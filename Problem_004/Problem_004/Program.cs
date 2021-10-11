using System;

namespace Problem_004
{
    class Program
    {
        // Possible values of coins
        static int[] Coins = new int[6] {50, 25, 20, 10, 5, 1};

        /// <summary>
        /// Recursive function that calculates to number of ways to compose a given amount
        /// </summary>
        /// <param name="i">Index of the current coin to be used</param>
        /// <param name="target">Target value</param>
        /// <param name="currentSum">Current sum</param>
        /// <returns>Number of ways to compose a given amount</returns>
        static int getNumberOfCombinations(int i, int target, int currentSum)
        {
            if (target == currentSum)
            {
                return 1;
            }

            if (Coins.Length == i)
            {
                return 0;
            }
            
            int p = 0;
            if (Coins[i] > target)
            {
                p += getNumberOfCombinations(i + 1, target, currentSum);
            }
            else if (Coins[i] == target)
            {
                
                p++;
                p += getNumberOfCombinations(i + 1, target, currentSum);
            }
            else
            {
                for (int a = 1; a <= (target - currentSum) / Coins[i]; a++)
                {
                    p += getNumberOfCombinations(i + 1, target, (a * Coins[i]) + currentSum);
                }
                p += getNumberOfCombinations(i + 1, target, 0);
            }
            return p;
        }

        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                Console.WriteLine("Use one numeric parameters.");
            }
            else
            {
                Console.WriteLine(getNumberOfCombinations(0, int.Parse(args[0]), 0));
            }
        }
    }
}
