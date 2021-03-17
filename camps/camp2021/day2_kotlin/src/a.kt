import kotlin.math.abs

fun _mod(a: Long, b: Long) = (a % b + a) % b
fun _div(a: Long, b: Long) = (a - _mod(a, b)) / b
fun gcd(a: Long, b: Long): Long {
    if (b == 0L)
        return a
    return gcd(b, a % b)
}

data class XWithCoeffient(var coeffX: Long = 0L, var coeff: Long = 0L) {
    operator fun plus(oth: XWithCoeffient) = XWithCoeffient(coeffX + oth.coeffX, coeff + oth.coeff)
    operator fun minus(oth: XWithCoeffient) = XWithCoeffient(coeffX - oth.coeffX, coeff - oth.coeff)
    operator fun times(oth: XWithCoeffient) = XWithCoeffient(
        coeffX = coeffX * oth.coeff + oth.coeffX * coeff,
        coeff = coeff * oth.coeff
    )

    operator fun div(k: Long) = XWithCoeffient(coeffX / k, coeff / k)
    fun GCD() = gcd(abs(coeffX), abs(coeff))
}

data class Fraction(
    var p: XWithCoeffient = XWithCoeffient(0, 0),
    var q: XWithCoeffient = XWithCoeffient(0, 1)
) {
    fun rebalance(): Fraction {
        val g = gcd(p.GCD(), q.GCD())
        return Fraction(p / g, q / g)
    }

    operator fun plus(oth: Fraction) = Fraction(p * oth.q + oth.p * q, q * oth.q).rebalance()
    operator fun minus(oth: Fraction) = Fraction(p * oth.q - oth.p * q, oth.q * q).rebalance()
    operator fun times(oth: Fraction) = Fraction(p * oth.p, q * oth.q).rebalance()
    operator fun div(oth: Fraction) = (this * Fraction(oth.q, oth.p)).rebalance()
}


fun main() {
    val tokens = readLn().split(' ')
    val stack = mutableListOf<Fraction>()
    val parseDigit = { it: String ->
        Fraction(XWithCoeffient(0, it.toLong()), XWithCoeffient(0, 1))
    }
    val parseX = {
        Fraction(XWithCoeffient(1, 0), XWithCoeffient(0, 1))
    }
    val parsePlus = {
        val a = stack.removeLast()
        val b = stack.removeLast()
        a + b
    }
    val parseMinus = {
        val a = stack.removeLast()
        val b = stack.removeLast()
        b - a
    }
    val parseTimes = {
        val a = stack.removeLast()
        val b = stack.removeLast()
        a * b
    }
    val parseDiv = {
        val a = stack.removeLast()
        val b = stack.removeLast()
        b / a
    }
    for (token in tokens) {
        val now: Fraction = when {
            token[0].isDigit() -> parseDigit(token)
            token == "+" -> parsePlus()
            token == "-" -> parseMinus()
            token == "*" -> parseTimes()
            token == "/" -> parseDiv()
            token == "X" -> parseX()
            else -> Fraction(XWithCoeffient(0, 0), XWithCoeffient(0, 1))
        }
        stack.add(now)
    }
    val res = stack[0]
    if (res.p.coeffX == 0L) {
        println(if (res.p.coeff == 0L) "MULTIPLE" else "NONE")
        return
    }
    val res1 = Fraction(XWithCoeffient(0, -res.p.coeff), XWithCoeffient(0, res.p.coeffX)).rebalance()
    if (res1.q.coeff < 0) {
        res1.p.coeff *= -1
        res1.q.coeff *= -1
    }
    if (res.q.coeffX != 0L) {
        val res2 = Fraction(XWithCoeffient(0, -res.q.coeff), XWithCoeffient(0, res.q.coeffX)).rebalance()
        if (res2.q.coeff < 0) {
            res2.p.coeff *= -1
            res2.q.coeff *= -1
        }
        if (res1 == res2) {
            println("NONE")
            return

        }
    }
    val parseX1 = {
        res1
    }
    for (token in tokens) {
        val now: Fraction = when {
            token[0].isDigit() -> parseDigit(token)
            token == "+" -> parsePlus()
            token == "-" -> parseMinus()
            token == "*" -> parseTimes()
            token == "/" -> parseDiv()
            token == "X" -> parseX1()
            else -> Fraction(XWithCoeffient(0, 0), XWithCoeffient(0, 1))
        }
        if (now.q.coeffX == 0L && now.q.coeff == 0L){
            println("NONE")
            return
        }
        stack.add(now)
    }
    println("X = ${res1.p.coeff}/${res1.q.coeff}")
}

private fun readLn() = readLine()!!
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readLongs() = readStrings().map { it.toLong() }