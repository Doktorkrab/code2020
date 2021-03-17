fun main() {
    val n = readLn().toInt()
    println(n)
    for (i in 1..n)
        println(readLn())
}

private fun readLn() = readLine()!!
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readLongs() = readStrings().map { it.toLong() }