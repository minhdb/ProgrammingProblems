/**
 * AC C++ Dev P3
 *
 * You are competing in an advanced archery tournament. To win the match, you
 * need to score an exact total of \(n\) points. You have \(a\) arrows remaining
 * in your quiver and \(k\) different bows available to choose from. For each
 * arrow you shoot, you can choose any of the \(k\) available bows. Each bow has
 * a unique performance profile, represented by a probability distribution. For
 * the \(i\)-th bow (where \(0 \le i < k\)), you are given an array of
 * probabilities \(p[i]\) of length \(5\), where \(p[i][j-1]\) is the
 * probability of scoring exactly \(j\) points (for \(1 \le j \le 5\)) when
 * shooting an arrow with that bow. Additionally, for any arrow, you may choose
 * to strategically drop the arrow, which costs 1 arrow but guarantees a score
 * of 0 with a probability of 1.0. Return the maximum probability that you can
 * score exactly \(n\) points using at most \(a\) arrows. If it is
 * mathematically impossible to achieve a total score of exactly \(n\), return
 * 0.0.
 *
 *
 * Input Format
 *
 * • An integer n: The exact target score needed to win. • An integer a: The
 * number of arrows you have left. • An integer k: The number of available bows.
 * • A 2D floating-point array p of size k x 5: Where p[i][j] represents the
 * probability of scoring j + 1 points using bow i.
 *
 * Output Format
 *
 * • Return a double/float representing the maximum probability of getting a
 * total score of exactly n. Your answer will be accepted if it falls within a
 * small margin of error (e.g., \(10^{-6}\)).
 *
 * Constraints
 *
 * • \(1 \le n \le 500\) • \(1 \le a \le 100\) • \(1 \le k \le 10\) • \(0.0 \le
 * p[i][j] \le 1.0\), and the sum of probabilities for a single bow
 * \(\sum_{j=0}^{4} p[i][j] \le 1.0\). (Note: If the sum is less than 1.0, the
 * remaining probability represents missing the target entirely and scoring 0).
 *
 * Sample Test Case
 *
 * n = 5 a = 2 k = 2 p = [
 *   [0.1, 0.2, 0.4, 0.2, 0.1],  # Bow 0 probabilities for scores [1, 2, 3, 4, 5]
 *   [0.0, 0.0, 0.1, 0.1, 0.8]   # Bow 1 probabilities for scores [1, 2, 3, 4, 5]
 * ]
 *
 * Output
 *
 * 0.180000
 *
 *
 * Explanation
 *
 * You need exactly 5 points with 2 arrows. There are a few ways to achieve
 * this:
 * 1. Shoot Arrow 1 with Bow 0 (score 2) AND Arrow 2 with Bow 0 (score 3):
 * • Probability: \(0.2 \times 0.4 = 0.08\)
 * 2. Shoot Arrow 1 with Bow 0 (score 3) AND Arrow 2 with Bow 0 (score 2):
 * • Probability: \(0.4 \times 0.2 = 0.08\)
 * 3. Shoot Arrow 1 with Bow 1 (score 5) AND Drop Arrow 2 (score 0):
 * • Probability: \(0.8 \times 1.0 = 0.80\) • Wait! If you just drop the second
 * arrow after hitting a 5, your path is perfectly valid. But what if you swap
 * the order?
 * 4. Drop Arrow 1 (score 0) AND Shoot Arrow 2 with Bow 1 (score 5):
 */
