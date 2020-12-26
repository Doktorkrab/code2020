import java.math.BigInteger
import kotlin.math.min

private fun solve(): Unit {
    val p = BigInteger(readLn())
    val q = readLong()
    val bq = BigInteger.valueOf(q)
    if (p % BigInteger.valueOf(q) != BigInteger.ZERO){
        println(p)
        return
    }
    val factors = primeFactorization(q)
    var ans = BigInteger.ZERO
    for (f in factors){
        var deg1 = 0
        val bF = BigInteger.valueOf(f)
        var p1 = p / bq
        while (p1 % bF == BigInteger.ZERO){
            deg1++
            p1 /= bF
        }
        var value = BigInteger.ONE
        for (i in 0 until deg1 + 1)
            value *= bF
        if (ans == BigInteger.ZERO || value < ans)
            ans = value
    }
    println(p / ans)
}

fun primeFactorization(n: Long): List<Long> {
    var n = n
    val f = MutableList<Long>(0) { 0L }
    var ff = 2L
    while (ff * ff <= n){
        if (n % ff == 0L){
            f.add(ff)
            while (n % ff == 0L)
                n /= ff
        }
        ff++
    }
    if (n > 1)
        f.add(n)
    return f
}

fun main() = solve()

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }