import java.io.BufferedReader
import java.io.File
import java.io.FileReader
import java.util.*
import kotlin.collections.ArrayList
import kotlin.math.abs
import kotlin.math.sqrt

data class Vector(val x: Double, val y: Double) {
    operator fun minus(V: Vector) = Vector(x - V.x, y - V.y)
    operator fun plus(V: Vector) = Vector(x + V.x, y + V.y)
    operator fun times(k: Double) = Vector(k * x, k * y)
    operator fun div(k: Double) = Vector(x / k, y / k)

    infix fun cross(v: Vector) = x * v.y - v.x * y
    infix fun dot(v: Vector) = x * v.x + y * v.y
    fun rotate90() = Vector(-y, x)
    fun len() = sqrt(x * x + y * y)
}

val EPS = 1e-9

data class Line(var a: Double, var b: Double, var c: Double) {
    constructor(p1: Vector, p2: Vector) : this(0.0, 0.0, 0.0) {
        val normal = (p2 - p1).rotate90()
        a = normal.x
        b = normal.y
        c = -(a * p1.x + b * p1.y)
    }

    fun normal() = Vector(a, b)
    fun distance(p: Vector) = abs((a * p.x + b * p.y + c) / normal().len())
    fun checkIntersect(l: Line) = abs(normal() cross l.normal()) < EPS
    fun intersect(l: Line): Vector? {
        if (checkIntersect(l))
            return null
//        println(this)
//        println(l)
//        println(normal() cross l.normal())
        return Vector((l.c * b - c * l.b) / (l.b * a - b * l.a), (c * l.a - l.c * a) / (l.b * a - b * l.a))
    }

    fun newLineFromPoint(p: Vector): Line {
        val (a1, b1) = normal().rotate90()
        val c1 = -(p.x * a1 + p.y * b1)
        return Line(a1, b1, c1)
    }
}
fun trapArea(p1: Vector, p2:Vector) = (p1.y + p2.y) * (p2.x - p1.x) / 2.0

fun getArea(arr: ArrayList<Vector>){
    val n = arr.size
    var ans = 0.0
    for (i in 0 until n){
        ans += trapArea(arr[i], arr[(i + 1) % n])
    }
    val file =File("origami.out")
    file.writeText("%.16f".format(ans))
}
fun main() {
    val (n, x, y) = readDoubles(3)
    val sw = Vector(0.0, 0.0)
    val nw = Vector(0.0, n)
    val ne = Vector(n, n)
    val se = Vector(n, 0.0)
    val l1 = Line(sw, nw)
    val l2 = Line(nw, ne)
    val l3 = Line(ne, se)
    val l4 = Line(se, sw)
//    println("HERE")
    val lMain = Line(Vector(x, y), Vector(n, n)).newLineFromPoint((Vector(x, y) + Vector(n, n)) / 2.0)
    val points = ArrayList<Vector>()

    if (n == x && n == y){
        points.add(sw)
        points.add(nw)
        points.add(ne)
        points.add(se)
        getArea(points)
        return
    }
    points.add(sw)
    val p1 = l1.intersect(lMain)
    if (p1 == null || p1.y > n)
        points.add(nw)
    else
        points.add(p1)
    if (p1 == null || p1.y > n){
        val p2 = l2.intersect(lMain)
        points.add(p2!!)
    }
    val p3 = l3.intersect(lMain)
    if (p3 != null&& p3.y >= 0 && p3.y <= n){
        points.add(p3)
    }
    if (points.last().x == n)
        points.add(se)
    val p4 =l4.intersect(lMain)
//    println(p4)
    if (p4 != null && p4.x >= 0 && p4.x <= n)
        points.add(p4)
//    println(points)
    getArea(points)

}
@JvmField val INPUT = System.`in`
@JvmField val OUTPUT = System.out

@JvmField val _reader = BufferedReader(FileReader("origami.in"))
fun readLine(): String? = _reader.readLine()
fun readLn() = _reader.readLine()!!
@JvmField var _tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
    while (_tokenizer.hasMoreTokens().not()) _tokenizer = StringTokenizer(_reader.readLine() ?: return "", " ")
    return _tokenizer.nextToken()
}
fun readInt() = read().toInt()
fun readDouble() = read().toDouble()
fun readLong() = read().toLong()
fun readStrings(n: Int) = List(n) { read() }
fun readLines(n: Int) = List(n) { readLn() }
fun readInts(n: Int) = List(n) { read().toInt() }
fun readIntArray(n: Int) = IntArray(n) { read().toInt() }
fun readDoubles(n: Int) = List(n) { read().toDouble() }
fun readDoubleArray(n: Int) = DoubleArray(n) { read().toDouble() }
fun readLongs(n: Int) = List(n) { read().toLong() }
fun readLongArray(n: Int) = LongArray(n) { read().toLong() }