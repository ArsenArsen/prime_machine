import java.io.File

/**
 * A crude check that verifies that a text file of integers separated by newlines are all prime. The prime check is not optimized.
 * @author chrislo27
 */
fun main(args: Array<String>) {
    val file = File(args.first())
    val allPrime = file
            .readLines()
            .map(String::toInt)
            .all { num ->
                if (num == 2) {
                    true
                } else {
                    (3 until num step 2).none { num % it == 0 }
                }
            }
    println("All prime?: $allPrime")
}
