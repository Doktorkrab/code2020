import kotlin.math.abs
import kotlin.math.min
import kotlin.math.sqrt


data class Vector(var x: Long, var y: Long) {
    operator fun plus(other: Vector): Vector {
        return Vector(x + other.x, y + other.y)
    }

    operator fun minus(other: Vector) = Vector(x - other.x, y - other.y)

    operator fun times(k: Long) = Vector(x * k, y * k)

    operator fun unaryMinus() = Vector(-x, -y)

    infix fun cross(other: Vector): Long {
        return x * other.y - y * other.x
    }

    infix fun dot(other: Vector): Long {
        return x * other.x + y * other.y
    }

    fun rotate90(): Vector {
        return Vector(-y, x)
    }

    fun len(): Double {
        return sqrt((x * x + y * y).toDouble())
    }
}

data class Line(var a: Long, var b: Long, var c: Long) {
    constructor(p1: Vector, p2: Vector) : this(0, 0, 0) {
        val normal = (p2 - p1).rotate90()
        a = normal.x
        b = normal.y
        c = -(a * p1.x + b * p1.y)
    }

    fun normal() = Vector(a, b)
    fun distance(p: Vector) = abs((a * p.x + b * p.y + c) / normal().len())
}

data class Segment(val end1: Vector, val end2: Vector) {
    fun vector() = end2 - end1
    fun line() = Line(end1, end2)
    fun distance(p: Vector): Double {
        if ((p - end1) dot vector() < 0 || (p - end2) dot -vector() < 0)
            return min((p - end1).len(), (p - end2).len())
        return line().distance(p)
    }
}

fun main() {
    val polygons =
    val coords = readInts().map { it.toLong() }
    val p = Vector(coords[0], coords[1])
    val segment = Segment(end1 = Vector(coords[2], coords[3]), end2 = Vector(coords[4], coords[5]))
    println("%.20f".format(segment.distance(p)))
}

private fun readLn() = readLine()!!
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }