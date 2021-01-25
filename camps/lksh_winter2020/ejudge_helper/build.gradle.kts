import org.jetbrains.kotlin.gradle.tasks.KotlinCompile

plugins {
    kotlin("jvm") version "1.4.20"
    application
}

group = "me.doktorkrab"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
    maven("https://jitpack.io")
}

dependencies {
    testImplementation(kotlin("test-junit"))
//    implementation("io.github.kotlin-telegram-bot.kotlin-telegram-bot:telegram:6.0.1")
//    implementation("com.github.elbekD:kt-telegram-bot:1.3.7")
//    implementation(group = "com.github.kittinunf.fuel", name = "fuel", version = "-SNAPSHOT")
//    implementation(group = "com.github.kittinunf.fuel", name = "fuel-json", version = "-SNAPSHOT")
//    implementation(group = "com.github.kittinunf.fuel", name = "fuel-coroutines", version = "-SNAPSHOT")
//    implementation("com.squareup.okhttp3:okhttp:4.9.0")
    implementation (platform("org.http4k:http4k-bom:4.1.1.1"))
    implementation ("org.http4k:http4k-core")
    implementation ("org.http4k:http4k-server-netty")
    implementation ("org.http4k:http4k-client-apache")
}

tasks.test {
    useJUnit()
}

tasks.withType<KotlinCompile>() {
    kotlinOptions.jvmTarget = "1.8"
}