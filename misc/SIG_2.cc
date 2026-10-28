/**
 * SIG 2 Implement a simplified version of a crypto broker platform. Initially,
 * there is an array of users, with each user depositing only cash. The array
 * deposits[i] represents the amount of cash the (i + 1)th user has deposited.
 *
 * Assume the platform contains just a single stock, and all operations are done
 * with this stock only. All operations are in the same currency, and currency
 * exchange is not supported.
 *
 * The platform should support the following three types of operations:
 *
 * "deposit" - deposits money to the specified user account. "buy" - the
 * specified user buys the specified amount of crypto at the specified price.
 * The platform should ensure the user has enough money in their account to
 * process the operation. "sell" - the specified user sells the specified amount
 * of crypto at the specified price. The platform should ensure the user has
 * enough cryptos in their account to process the operation. Your task is to
 * return an integer array representing the total amount of money in the
 * specified user's account after each operation.
 *
 * Example:
 * For deposits = [9, 7, 12] and operations = ["buy 1 3 2", "sell 1 4 10",
 * "deposit 2 12", "buy 2 10 2", "buy 2 6 3"], the output should be
 * cryptoTrading(deposits, operations) = [3, 3, 19, 19, 1].
 *
 * Explanation of operations:
 *
 * The user with user_id = 1 wants to buy 3 shares of the stock at price = 2.
 * The required amount of money is needed_money = 3 * 2 = 6. The user has 9 ≥ 6
 * units of money in their account, so this operation is processed successfully.
 * After this operation, the user has 3 units of money remaining. The user with
 * user_id = 1 wants to sell 4 shares of the stock at price = 10. This operation
 * is not processed successfully because the user does not have 4 shares of the
 * stock. The user still has 3 units of money remaining. The user with user_id =
 * 2 deposits 12 units of money into their account. After this operation, the
 * user has 19 units of money. The user with user_id = 2 wants to buy 10 shares
 * of the stock at price = 2. The required amount of money is needed_money = 10
 * * 2 = 20. The user has 19 < 20 units of money in their account, so this
 * operation is not processed successfully. The user still has 19 units of money
 * remaining. The user with user_id = 2 wants to buy 6 shares of the stock at
 * price = 3. The required amount of money is needed_money = 6 * 3 = 18. The
 * user has 19 ≥ 18 units of money, so this operation is processed successfully.
 * After this operation, the user has 1 unit of money remaining. So, the output
 * is [3, 3, 19, 19, 1].
 *
 * Input/Output:
 *
 * [input] array.integer deposits: An array of integers representing the amount
 * of money (in cash) that users deposit to their accounts. Guaranteed
 * constraints: 1 ≤ deposits.length ≤ 10^4, 1 ≤ deposits[i] ≤ 10^5. [input]
 * array.string operations: An array of strings representing the operations
 * described above. Specifically, it's guaranteed that: In buy and sell
 * operations - amount and price are integers. In all operations - user_id will
 * be integers between 1 to deposits.length. After each operation, the total
 * amount of money in each user's account will be an integer. Guaranteed
 * constraints: 1 ≤ operations.length ≤ 10^4. [output] array.integer: An array
 * of integers where the ith element of the array represents the total amount of
 * money in the specified user's account after the ith operation.
 */
